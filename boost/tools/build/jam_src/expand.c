/*
 * Copyright 1993-2002 Christopher Seiwald and Perforce Software, Inc.
 *
 * This file is part of Jam - see jam.c for Copyright information.
 */
/*  This file is ALSO:
 *  (C) Copyright David Abrahams 2001. Permission to copy, use,
 *  modify, sell and distribute this software is granted provided this
 *  copyright notice appears in all copies. This software is provided
 *  "as is" without express or implied warranty, and with no claim as
 *  to its suitability for any purpose.
 */

# include "jam.h"
# include "lists.h"
# include "variable.h"
# include "expand.h"
# include "pathsys.h"
# include "newstr.h"
# include "strings.h"

# include <assert.h>
# include <string.h>
/*
 * expand.c - expand a buffer, given variable values
 *
 * External routines:
 *
 *     var_expand() - variable-expand input string into list of strings
 *
 * Internal routines:
 *
 *	var_edit_parse() - parse : modifiers into PATHNAME structure
 *	var_edit_file() - copy input target name to output, modifying filename
 *	var_edit_shift() - do upshift/downshift mods
 *
 * 01/25/94 (seiwald) - $(X)$(UNDEF) was expanding like plain $(X)
 * 04/13/94 (seiwald) - added shorthand L0 for null list pointer
 * 01/11/01 (seiwald) - added support for :E=emptyvalue, :J=joinval
 */

typedef struct {
	PATHNAME	f;		/* :GDBSMR -- pieces */
	char		parent;		/* :P -- go to parent directory */
	char		filemods;	/* one of the above applied */
	char	downshift;	/* :L -- downshift result */
	char	upshift;	/* :U -- upshift result */
<<<<<<< variant A
	char	parent;		/* :P -- go to parent directory */
        char    to_slashes;     /* :T -- convert "\" to "/" */
} VAR_ACTS ;
>>>>>>> variant B
	PATHPART	empty;		/* :E -- default for empties */
	PATHPART	join;		/* :J -- join list with char */
} VAR_EDITS ;
####### Ancestor
	char	parent;		/* :P -- go to parent directory */
} VAR_ACTS ;
======= end

<<<<<<< variant A
static void var_edit( char *in, char *mods, string *out );
static void var_mods( char *mods, FILENAME *f, VAR_ACTS *acts );
>>>>>>> variant B
static void var_edit_parse( char *mods, VAR_EDITS *edits );
static void var_edit_file( char *in, char *out, VAR_EDITS *edits );
static void var_edit_shift( char *out, VAR_EDITS *edits );
####### Ancestor
static void var_edit( char *in, char *mods, char *out );
static void var_mods( char *mods, FILENAME *f, VAR_ACTS *acts );
======= end

static int adjust_index( int index, int length );

# define MAGIC_COLON	'\001'
# define MAGIC_LEFT	'\002'
# define MAGIC_RIGHT	'\003'

/*
 * var_expand() - variable-expand input string into list of strings
 *
 * Would just copy input to output, performing variable expansion, 
 * except that since variables can contain multiple values the result
 * of variable expansion may contain multiple values (a list).  Properly
 * performs "product" operations that occur in "$(var1)xxx$(var2)" or
 * even "$($(var2))".
 *
 * Returns a newly created list.
 */

LIST *
var_expand( 
	LIST	*l,
	char	*in,
	char	*end,
	LOL	*lol,
	int	cancopyin )
{
        string buf[1];
        size_t prefix_length;
	char *out;
	char *inp = in;
	char *ov;		/* for temp copy of variable in outbuf */
	int depth;

	if( DEBUG_VAREXP )
	    printf( "expand '%.*s'\n", end - in, in );

	/* This gets alot of cases: $(<) and $(>) */

	if( in[0] == '$' && in[1] == '(' && in[3] == ')' && !in[4] )
	{
	    switch( in[2] )
	    {
	    case '1':
	    case '<':
		return list_copy( l, lol_get( lol, 0 ) );

	    case '2':
	    case '>':
		return list_copy( l, lol_get( lol, 1 ) );
	    }
	}

	/* See if we can use a simple copy of in to out. */

	while ( in < end )
	    if ( *in++ == '$' && *in == '(' )
		goto expand;

	/* No variables expanded - just add copy of input string to list. */

	/* Cancopyin is an optimization: if the input was already a list */
	/* item, we can use the copystr() to put it on the new list. */
	/* Otherwise, we use the slower newstr(). */

	if ( cancopyin )
        {
	    return list_new( l, copystr( inp ) );
        }
	else
        {
            LIST* r;
            string_new( buf );
            string_append_range( buf, inp, in );
            
	    r = list_new( l, newstr( buf->value ) );
            string_free( buf );
            return r;
        }

    expand:
        string_new( buf );
        string_append_range( buf, inp, in - 1 ); /* copy in initial stuff */
	/*
         * Input so far (ignore blanks):
         *
         *      stuff-in-outbuf $(variable) remainder
         *                       ^                   ^
         *                       in                  end
         * Output so far:
         *
         *      stuff-in-outbuf $
         *      ^                ^
         *      out_buf          out
         *
         *
         * We just copied the $ of $(...), so back up one on the output.
         * We now find the matching close paren, copying the variable and
         * modifiers between the $( and ) temporarily into out_buf, so that
         * we can replace :'s with MAGIC_COLON.  This is necessary to avoid
         * being confused by modifier values that are variables containing
         * :'s.  Ugly.
         */

	depth = 1;
	inp = ++in; /* skip over the '(' */

	while( in < end && depth )
	{
	    switch( *in++ )
	    {
	    case '(': depth++; break;
	    case ')': depth--; break;
	    }
	}

	/*
	 * Input so far (ignore blanks):
	 *
	 *	stuff-in-outbuf $(variable) remainder
	 *			  ^	   ^         ^
	 *			  inp      in        end
         */
        prefix_length = buf->size;
        string_append_range( buf, inp, in - 1 );

        out = buf->value + prefix_length;
	for ( ov = out; ov < buf->value + buf->size; ++ov )
	{
	    switch( *ov )
	    {
	    case ':': *ov = MAGIC_COLON; break;
	    case '[': *ov = MAGIC_LEFT; break;
	    case ']': *ov = MAGIC_RIGHT; break;
	    }
	}

	/*
	 * Input so far (ignore blanks):
	 *
	 *	stuff-in-outbuf $(variable) remainder
	 *			            ^        ^
	 *			            in       end
	 * Output so far:
	 *
	 *	stuff-in-outbuf variable
	 *	^	        ^       ^
	 *	out_buf         out	ov
	 *
	 * Later we will overwrite 'variable' in out_buf, but we'll be
	 * done with it by then.  'variable' may be a multi-element list, 
	 * so may each value for '$(variable element)', and so may 'remainder'.
	 * Thus we produce a product of three lists.
	 */

	{
	    LIST *variables = 0;
	    LIST *remainder = 0;
	    LIST *vars;

	    /* Recursively expand variable name & rest of input */

	    if( out < ov )
		variables = var_expand( L0, out, ov, lol, 0 );
	    if( in < end )
		remainder = var_expand( L0, in, end, lol, 0 );

	    /* Now produce the result chain */

	    /* For each variable name */

	    for( vars = variables; vars; vars = list_next( vars ) )
	    {
		LIST *value, *evalue = 0;
		char *colon;
		char *bracket;
<<<<<<< variant A
		int i, sub1, sub2;
		string variable;
                char *varname;
>>>>>>> variant B
		char varname[ MAXSYM ];
		int sub1 = 0, sub2 = -1;
		VAR_EDITS edits;
####### Ancestor
		char varname[ MAXSYM ];
		int i, sub1, sub2;
======= end

		/* Look for a : modifier in the variable name */
		/* Must copy into varname so we can modify it */
                
                string_copy( &variable, vars->string );
                varname = variable.value;

		if( colon = strchr( varname, MAGIC_COLON ) )
<<<<<<< variant A
                {
		    string_truncate( &variable, colon - varname );
                }
>>>>>>> variant B
		{
		    *colon = '\0';
		    var_edit_parse( colon + 1, &edits );
		}

		/* Look for [x-y] subscripting */
		/* sub1 is x (0 default) */
		/* sub2 is length (-1 means forever) */
####### Ancestor
		    *colon = '\0';
======= end

		if( bracket = strchr( varname, MAGIC_LEFT ) )
		{
		    char *dash = 0;

<<<<<<< variant A
		    if( bracket[1] && ( dash = strchr( bracket + 2, '-' ) ) )
		    {
                        if( dash == bracket + 2 && *( bracket + 1 ) == '-')
                            --dash;
			string_truncate( &variable, dash - varname );
			sub1 = atoi( bracket + 1 );
			sub2 = atoi( dash + 1 );
		    }
		    else
		    {
			sub1 = sub2 = atoi( bracket + 1 );
		    }
>>>>>>> variant B
		    if( dash = strchr( bracket + 1, '-' ) )
			*dash = '\0';

		    sub1 = atoi( bracket + 1 ) - 1;

		    if( !dash )		sub2 = 1;
		    else if( !dash[1] )	sub2 = -1;
		    else 		sub2 = atoi( dash + 1 ) - sub1;
####### Ancestor
		    if( dash = strchr( bracket + 1, '-' ) )
		    {
			*dash = '\0';
			sub1 = atoi( bracket + 1 );
			sub2 = atoi( dash + 1 );
		    }
		    else
		    {
			sub1 = sub2 = atoi( bracket + 1 );
		    }
======= end

                    string_truncate( &variable, bracket - varname );
		}

		/* Get variable value, specially handling $(<), $(>), $(n) */
		
		if( varname[0] == '<' && !varname[1] )
		    value = lol_get( lol, 0 );
		else if( varname[0] == '>' && !varname[1] )
		    value = lol_get( lol, 1 );
		else if( varname[0] >= '1' && varname[0] <= '9' && !varname[1] )
		    value = lol_get( lol, varname[0] - '1' );
		else 
		    value = var_get( varname );
                
		/* The fast path: $(x) - just copy the variable value. */
		/* This is only an optimization */

		if( out == buf->value && !bracket && !colon && in == end )
		{
                    string_free( &variable );
		    l = list_copy( l, value );
		    continue;
		}

<<<<<<< variant A
                /* Adjust negative indices */
                if ( sub1 < 0 || sub2 < 0 )
                {
                    int length = list_length( value );
                    sub1 = adjust_index( sub1, length );
                    sub2 = adjust_index( sub2, length );
                }

>>>>>>> variant B
		/* Handle start subscript */

		while( sub1 > 0 && value )
		    --sub1, value = list_next( value );

		/* Empty w/ :E=default? */

		if( !value && colon && edits.empty.ptr )
		    evalue = value = list_new( L0, newstr( edits.empty.ptr ) );

####### Ancestor
======= end
		/* For each variable value */
<<<<<<< variant A
		for( i = 1; value; i++, value = list_next( value ) )
>>>>>>> variant B

		for( ; value; value = list_next( value ) )
####### Ancestor

		for( i = 1; value; i++, value = list_next( value ) )
======= end
		{
		    LIST *rem;
                    size_t postfix_start;

		    /* Handle end subscript (length actually) */

		    if( sub2 >= 0 && --sub2 < 0 )
			break;

                    string_truncate( buf, prefix_length );

		    /* Apply : mods, if present */

<<<<<<< variant A
		    if( colon )
			var_edit( value->string, colon + 1, buf );
>>>>>>> variant B
		    if( colon && edits.filemods )
			var_edit_file( value->string, out, &edits );
####### Ancestor
		    if( colon )
			var_edit( value->string, colon + 1, out );
======= end
		    else
                        string_append( buf, value->string );

		    if( colon && ( edits.upshift || edits.downshift ) )
			var_edit_shift( out, &edits );

		    /* Handle :J=joinval */
		    /* If we have more values for this var, just */
		    /* keep appending them (with the join value) */
		    /* rather than creating separate LIST elements. */

		    if( colon && edits.join.ptr && 
		      ( list_next( value ) || list_next( vars ) ) )
		    {
			out += strlen( out );
			strcpy( out, edits.join.ptr );
			out += strlen( out );
			continue;
		    }

		    /* If no remainder, append result to output chain. */

		    if( in == end )
		    {
			l = list_new( l, newstr( buf->value ) );
			continue;
		    }

		    /* For each remainder, append the complete string */
		    /* to the output chain. */
		    /* Remember the end of the variable expansion so */
		    /* we can just tack on each instance of 'remainder' */

		    postfix_start = buf->size;

		    for( rem = remainder; rem; rem = list_next( rem ) )
		    {
                        string_truncate( buf, postfix_start );
                        string_append( buf, rem->string );
			l = list_new( l, newstr( buf->value ) );
		    }
		}
<<<<<<< variant A
                string_free( &variable );
>>>>>>> variant B

		/* Toss used empty */

		if( evalue )
		    list_free( evalue );
####### Ancestor
======= end
	    }

	    /* variables & remainder were gifts from var_expand */
	    /* and must be freed */

	    if( variables )
		list_free( variables );
	    if( remainder)
		list_free( remainder );

	    if( DEBUG_VAREXP )
	    {
		printf( "expanded to " );
		list_print( l );
		printf( "\n" );
	    }

            string_free( buf );
	    return l;
	}
}

/*
<<<<<<< variant A
 * var_edit() - copy input target name to output, performing : modifiers
 */
	
static void
var_edit( 
	char	*in,
	char	*mods,
	string	*out)
{
	FILENAME oldf, newf;
	VAR_ACTS acts;

	/* Parse apart original filename, putting parts into "oldf" */

	file_parse( in, &oldf );

	/* Parse apart modifiers, putting them into "newf" */

	var_mods( mods, &newf, &acts );

	/* Replace any oldf with newf */

	if( newf.f_grist.ptr )
	    oldf.f_grist = newf.f_grist;

	if( newf.f_root.ptr )
	    oldf.f_root = newf.f_root;

	if( newf.f_dir.ptr )
	    oldf.f_dir = newf.f_dir;

	if( newf.f_base.ptr )
	    oldf.f_base = newf.f_base;

	if( newf.f_suffix.ptr )
	    oldf.f_suffix = newf.f_suffix;

	if( newf.f_member.ptr )
	    oldf.f_member = newf.f_member;

	/* If requested, modify oldf to point to parent */

	if( acts.parent )
	    file_parent( &oldf );

	/* Put filename back together */

	file_build( &oldf, out, 0 );

	/* Handle upshifting, downshifting now */
        /* Handle conversion of "\" to "/" */
        {
            char* p;
            for ( p = out->value; *p; ++p)
            {
                if( acts.upshift )
                {
                    *p = toupper( *p );
                }
                else if( acts.downshift )
                {
                    *p = tolower( *p );
                }
                if ( acts.to_slashes )
                {
                    if ( *p == '\\' )
                        *p = '/';
                }
            }
            out->size = p - out->value;
        }
}


/*
 * var_mods() - parse : modifiers into FILENAME structure
>>>>>>> variant B
 * var_edit_parse() - parse : modifiers into PATHNAME structure
####### Ancestor
 * var_edit() - copy input target name to output, performing : modifiers
 */
	
static void
var_edit( 
	char	*in,
	char	*mods,
	char	*out )
{
	FILENAME oldf, newf;
	VAR_ACTS acts;

	/* Parse apart original filename, putting parts into "oldf" */

	file_parse( in, &oldf );

	/* Parse apart modifiers, putting them into "newf" */

	var_mods( mods, &newf, &acts );

	/* Replace any oldf with newf */

	if( newf.f_grist.ptr )
	    oldf.f_grist = newf.f_grist;

	if( newf.f_root.ptr )
	    oldf.f_root = newf.f_root;

	if( newf.f_dir.ptr )
	    oldf.f_dir = newf.f_dir;

	if( newf.f_base.ptr )
	    oldf.f_base = newf.f_base;

	if( newf.f_suffix.ptr )
	    oldf.f_suffix = newf.f_suffix;

	if( newf.f_member.ptr )
	    oldf.f_member = newf.f_member;

	/* If requested, modify oldf to point to parent */

	if( acts.parent )
	    file_parent( &oldf );

	/* Put filename back together */

	file_build( &oldf, out, 0 );

	/* Handle upshifting, downshifting now */

	if( acts.upshift )
	{
	    for( ; *out; ++out )
		*out = toupper( *out );
	}
	else if( acts.downshift )
	{
	    for( ; *out; ++out )
		*out = tolower( *out );
	}
}


/*
 * var_mods() - parse : modifiers into FILENAME structure
======= end
 *
 * The : modifiers in a $(varname:modifier) currently support replacing
 * or omitting elements of a filename, and so they are parsed into a 
 * PATHNAME structure (which contains pointers into the original string).
 *
 * Modifiers of the form "X=value" replace the component X with
 * the given value.  Modifiers without the "=value" cause everything 
 * but the component X to be omitted.  X is one of:
 *
 *	G <grist>
 *	D directory name
 *	B base name
 *	S .suffix
 *	M (member)
 *	R root directory - prepended to whole path
 *
 * This routine sets:
 *
 *	f->f_xxx.ptr = 0
 *	f->f_xxx.len = 0
 *		-> leave the original component xxx
 *
 *	f->f_xxx.ptr = string
 *	f->f_xxx.len = strlen( string )
 *		-> replace component xxx with string
 *
 *	f->f_xxx.ptr = ""
 *	f->f_xxx.len = 0
 *		-> omit component xxx
 *
 * var_edit_file() below and path_build() obligingly follow this convention.
 */

static void
var_edit_parse(
	char		*mods,
	VAR_EDITS	*edits )
{
<<<<<<< variant A
	char *flags = "GRDBSMT";
>>>>>>> variant B
####### Ancestor
	char *flags = "GRDBSM";
======= end
	int havezeroed = 0;
	memset( (char *)edits, 0, sizeof( *edits ) );

	while( *mods )
	{
	    char *p;
	    PATHPART *fp;

	    switch( *mods++ )
	    {
	    case 'L': edits->downshift = 1; continue;
	    case 'U': edits->upshift = 1; continue;
	    case 'P': edits->parent = edits->filemods = 1; continue;
	    case 'E': fp = &edits->empty; goto strval;
	    case 'J': fp = &edits->join; goto strval;
	    case 'G': fp = &edits->f.f_grist; goto fileval;
	    case 'R': fp = &edits->f.f_root; goto fileval;
	    case 'D': fp = &edits->f.f_dir; goto fileval;
	    case 'B': fp = &edits->f.f_base; goto fileval;
	    case 'S': fp = &edits->f.f_suffix; goto fileval;
	    case 'M': fp = &edits->f.f_member; goto fileval;

	    default: return; /* should complain, but so what... */
	    }
            else if ( *mods == 'T' )
            {
              acts->to_slashes = 1;
              ++mods;
              continue;
            }

	fileval:

	    /* Handle :CHARS, where each char (without a following =) */
	    /* selects a particular file path element.  On the first such */
	    /* char, we deselect all others (by setting ptr = "", len = 0) */
	    /* and for each char we select that element (by setting ptr = 0) */

	    edits->filemods = 1;

	    if( *mods != '=' )
	    {
		int i;

		if( !havezeroed++ )
		    for( i = 0; i < 6; i++ )
		{
		    edits->f.part[ i ].len = 0;
		    edits->f.part[ i ].ptr = "";
		}

		fp->ptr = 0;
		continue;
	    }

	strval:

	    /* Handle :X=value, or :X */

	    if( *mods != '=' )
	    {
		fp->ptr = "";
		fp->len = 0;
	    }
	    else if( p = strchr( mods, MAGIC_COLON ) )
		{
		*p = 0;
		fp->ptr = ++mods;
		    fp->len = p - mods;
		    mods = p + 1;
		}
		else
		{
		fp->ptr = ++mods;
		    fp->len = strlen( mods );
		    mods += fp->len;
		}
	    }
}

/*
 * var_edit_file() - copy input target name to output, modifying filename
 */
	
static void
var_edit_file( 
	char	*in,
	char	*out,
	VAR_EDITS *edits )
{
	PATHNAME pathname;

	/* Parse apart original filename, putting parts into "pathname" */

	path_parse( in, &pathname );

	/* Replace any pathname with edits->f */

	if( edits->f.f_grist.ptr )
	    pathname.f_grist = edits->f.f_grist;

	if( edits->f.f_root.ptr )
	    pathname.f_root = edits->f.f_root;

	if( edits->f.f_dir.ptr )
	    pathname.f_dir = edits->f.f_dir;

	if( edits->f.f_base.ptr )
	    pathname.f_base = edits->f.f_base;

	if( edits->f.f_suffix.ptr )
	    pathname.f_suffix = edits->f.f_suffix;

	if( edits->f.f_member.ptr )
	    pathname.f_member = edits->f.f_member;

	/* If requested, modify pathname to point to parent */

	if( edits->parent )
	    path_parent( &pathname );

	/* Put filename back together */

	path_build( &pathname, out, 0 );
}

/*
 * var_edit_shift() - do upshift/downshift mods
 */

static void
var_edit_shift( 
	char	*out,
	VAR_EDITS *edits )
{
	/* Handle upshifting, downshifting now */

	if( edits->upshift )
	{
	    for( ; *out; ++out )
		*out = toupper( *out );
	}
	else if( edits->downshift )
	{
	    for( ; *out; ++out )
		*out = tolower( *out );
	}
}

static int adjust_index( int index, int length )
{
    if ( index < 0 )
        index = length + 1 + index;
    /** For first range index negative values are ok.
        For second return value of 0 means don't use second bound. 
        We need to make it -1 so that all elements are skipped.
    */
    if ( index == 0 )
        index = -1;
    return index;
}

#ifndef NDEBUG
void var_expand_unit_test()
{
    LOL lol[1];
    LIST* l, *l2;
    LIST *expected = list_new( list_new( L0, newstr( "axb" ) ), newstr( "ayb" ) );
    LIST *e2;
    char axyb[] = "a$(xy)b";
    char azb[] = "a$($(z))b";
    
    lol_init(lol);
    var_set("xy", list_new( list_new( L0, newstr( "x" ) ), newstr( "y" ) ), VAR_SET );
    var_set("z", list_new( L0, newstr( "xy" ) ), VAR_SET );
    
    l = var_expand( 0, axyb, axyb + sizeof(axyb) - 1, lol, 0 );
    for ( l2 = l, e2 = expected; l2 && e2; l2 = list_next(l2), e2 = list_next(e2) )
        assert( !strcmp( e2->string, l2->string ) );
    list_free(l);
    
    l = var_expand( 0, azb, azb + sizeof(azb) - 1, lol, 0 );
    for ( l2 = l, e2 = expected; l2 && e2; l2 = list_next(l2), e2 = list_next(e2) )
        assert( !strcmp( e2->string, l2->string ) );
    list_free(l);
    
    lol_free(lol);
}
#endif
