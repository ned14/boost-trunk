/*
 * Copyright 1993, 2000 Christopher Seiwald.
 *
 * This file is part of Jam - see jam.c for Copyright information.
 */

/*  This file is ALSO:
 *  Copyright 2001-2004 David Abrahams.
 *  Distributed under the Boost Software License, Version 1.0.
 *  (See accompanying file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 */

# include "jam.h"
# include "lists.h"
# include "parse.h"
# include "variable.h"
# include "expand.h"
# include "hash.h"
# include "filesys.h"
# include "newstr.h"
# include "strings.h"
# include <stdlib.h>

/*
 * variable.c - handle jam multi-element variables
 *
 * External routines:
 *
 *	var_defines() - load a bunch of variable=value settings
 *	var_string() - expand a string with variables in it
 *	var_get() - get value of a user defined symbol
 *	var_set() - set a variable in jam's user defined symbol table
 *	var_swap() - swap a variable's value with the given one
 *	var_done() - free variable tables
 *
 * Internal routines:
 *
 *	var_enter() - make new var symbol table entry, returning var ptr
 *	var_dump() - dump a variable to stdout
 *
 * 04/13/94 (seiwald) - added shorthand L0 for null list pointer
 * 08/23/94 (seiwald) - Support for '+=' (append to variable)
 * 01/22/95 (seiwald) - split environment variables at blanks or :'s
 * 05/10/95 (seiwald) - split path variables at SPLITPATH (not :)
 * 09/11/00 (seiwald) - defunct var_list() removed
 */

static struct hash *varhash = 0;

/*
 * VARIABLE - a user defined multi-value variable
 */

typedef struct _variable VARIABLE ;

struct _variable {
	char	*symbol;
	LIST	*value;
} ;

static VARIABLE *var_enter( char *symbol );
static void var_dump( char *symbol, LIST *value, char *what );



/*
 * var_hash_swap() - swap all variable settings with those passed
 *
 * Used to implement separate settings spaces for modules
 */
void var_hash_swap( struct hash** new_vars )
{
    struct hash* old = varhash;
    varhash = *new_vars;
    *new_vars = old;
}

/*
 * var_defines() - load a bunch of variable=value settings
 *
 * If preprocess is false, take the value verbatim.
 *
 * Otherwise, if the variable value is enclosed in quotes, strip the
 * quotes.
 *
 * Otherwise, if variable name ends in PATH, split value at :'s.
 *
 * Otherwise, split the value at blanks.
 */

void
var_defines( char *const* e, int preprocess )
{
    string buf[1];

    string_new( buf );

	for( ; *e; e++ )
	{
	    char *val;

# ifdef OS_MAC
	    /* On the mac (MPW), the var=val is actually var\0val */
	    /* Think different. */
	
	    if( ( val = strchr( *e, '=' ) ) || ( val = *e + strlen( *e ) ) )
# else
	    if( val = strchr( *e, '=' ) )
# endif
	    {
		LIST *l = L0;
		char *pp, *p;
# ifdef OPT_NO_EXTERNAL_VARIABLE_SPLIT
                char split = '\0';
# else
# ifdef OS_MAC
		char split = ',';
# else
		char split = ' ';
# endif
# endif
                size_t len = strlen(val + 1);

                int quoted = val[1] == '"' && val[len] == '"';
                
                if ( quoted && preprocess )
                {
                    string_append_range( buf, val + 2, val + len );
                    l = list_new( l, newstr( buf->value ) );
                    string_truncate( buf, 0 );
                }
                else
                {
                    /* Split *PATH at :'s, not spaces */

                    if( val - 4 >= *e )
                    {
                        if( !strncmp( val - 4, "PATH", 4 ) ||
                            !strncmp( val - 4, "Path", 4 ) ||
                            !strncmp( val - 4, "path", 4 ) )
			    split = SPLITPATH;
                    }

                    /* Do the split */

                    for(
                        pp = val + 1;
                        preprocess && (p = strchr( pp, split )) != 0;
                        pp = p + 1 )
                    {
                        string_append_range( buf, pp, p );
                        l = list_new( l, newstr( buf->value ) );
                        string_truncate( buf, 0 );
                    }

                    l = list_new( l, newstr( pp ) );
                }

		/* Get name */
                string_append_range( buf, *e, val );
		var_set( buf->value, l, VAR_SET );
                string_truncate( buf, 0 );
	    }
	}
        string_free( buf );
}

/*
 * var_string() - expand a string with variables in it
 *
 * Copies in to out; doesn't modify targets & sources.
 */

int
var_string(
	char	*in,
	char	*out,
	int	outsize,
	LOL	*lol )
{
	char 	*out0 = out;
	char	*oute = out + outsize - 1;

	while( *in )
	{
	    char	*lastword;
	    int		dollar = 0;

	    /* Copy white space */

	    while( isspace( *in ) )
	    {
		if( out >= oute )
		    return -1;

		*out++ = *in++;
	    }

	    lastword = out;

	    /* Copy non-white space, watching for variables */

	    while( *in && !isspace( *in ) )
	    {
	        if( out >= oute )
		    return -1;

		if( in[0] == '$' && in[1] == '(' )
		    dollar++;

		*out++ = *in++;
	    }

        /* Add zero to 'out' so that 'lastword' is correctly zero-terminated. */
        if (out >= oute)
            return -1;
        /* Don't increment, intentionally. */
        *out= '\0';
           
	    /* If a variable encountered, expand it and and embed the */
	    /* space-separated members of the list in the output. */

	    if( dollar )
	    {
		LIST	*l;

		l = var_expand( L0, lastword, out, lol, 0 );

		out = lastword;

		for( ; l; l = list_next( l ) )
		{
		    int so = strlen( l->string );

		    if( out + so >= oute )
			return -1;

		    strcpy( out, l->string );
		    out += so;
		    *out++ = ' ';
		}

		list_free( l );
	    }
	}

	if( out >= oute )
	    return -1;

	*out++ = '\0';

	return out - out0;
}

/*
 * var_get() - get value of a user defined symbol
 *
 * Returns NULL if symbol unset.
 */

LIST *
var_get( char *symbol )
{
	VARIABLE var, *v = &var;

	v->symbol = symbol;

	if( varhash && hashcheck( varhash, (HASHDATA **)&v ) )
	{
	    if( DEBUG_VARGET )
		var_dump( v->symbol, v->value, "get" );
	    return v->value;
	}
    
	return 0;
}

/*
 * var_set() - set a variable in jam's user defined symbol table
 *
 * 'flag' controls the relationship between new and old values of
 * the variable: SET replaces the old with the new; APPEND appends
 * the new to the old; DEFAULT only uses the new if the variable
 * was previously unset.
 *
 * Copies symbol.  Takes ownership of value.
 */

void
var_set(
	char	*symbol,
	LIST	*value,
	int	flag )
{
	VARIABLE *v = var_enter( symbol );

	if( DEBUG_VARSET )
	    var_dump( symbol, value, "set" );
        
	switch( flag )
	{
	case VAR_SET:
	    /* Replace value */
	    list_free( v->value );
	    v->value = value;
	    break;

	case VAR_APPEND:
	    /* Append value */
	    v->value = list_append( v->value, value );
	    break;

	case VAR_DEFAULT:
	    /* Set only if unset */
	    if( !v->value )
		v->value = value;
	    else
		list_free( value );
	    break;
	}
}

/*
 * var_swap() - swap a variable's value with the given one
 */

LIST *
var_swap(
	char	*symbol,
	LIST	*value )
{
	VARIABLE *v = var_enter( symbol );
	LIST 	 *oldvalue = v->value;

	if( DEBUG_VARSET )
	    var_dump( symbol, value, "set" );

	v->value = value;

	return oldvalue;
}



/*
 * var_enter() - make new var symbol table entry, returning var ptr
 */

static VARIABLE *
var_enter( char	*symbol )
{
	VARIABLE var, *v = &var;

	if( !varhash )
	    varhash = hashinit( sizeof( VARIABLE ), "variables" );

	v->symbol = symbol;
	v->value = 0;

	if( hashenter( varhash, (HASHDATA **)&v ) )
	    v->symbol = newstr( symbol );	/* never freed */

	return v;
}

/*
 * var_dump() - dump a variable to stdout
 */

static void
var_dump(
	char	*symbol,
	LIST	*value,
	char	*what )
{
	printf( "%s %s = ", what, symbol );
	list_print( value );
	printf( "\n" );
}

/*
 * var_done() - free variable tables
 */
static void delete_var_( void* xvar, void* data )
{
    VARIABLE *v = (VARIABLE*)xvar;
    freestr( v->symbol );
    list_free( v-> value );
}

void
var_done()
{
    hashenumerate( varhash, delete_var_, (void*)0 );
	hashdone( varhash );
}
