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

#ifndef COMPILE_DWA20011022_H
# define COMPILE_DWA20011022_H

# include "frames.h"
# include "parse.h"
# include "regexp.h"

/*
 * compile.h - compile parsed jam statements
 */

LIST *compile_append( PARSE *parse, FRAME *args );
LIST *compile_foreach( PARSE *parse, FRAME *args );
LIST *compile_if( PARSE *parse, FRAME *args );
LIST *compile_include( PARSE *parse, FRAME *args );
LIST *compile_list( PARSE *parse, FRAME *args );
LIST *compile_local( PARSE *parse, FRAME *args );
LIST *compile_module( PARSE *parse, FRAME *args );
LIST *compile_null( PARSE *parse, FRAME *args );
LIST *compile_on( PARSE *parse, FRAME *args );
LIST *compile_rule( PARSE *parse, FRAME *args );
LIST *compile_rules( PARSE *parse, FRAME *args );
LIST *compile_set( PARSE *parse,FRAME *args );
LIST *compile_set_module( PARSE *parse, FRAME *args );
LIST *compile_setcomp( PARSE *parse, FRAME *args );
LIST *compile_setexec( PARSE *parse, FRAME *args );
LIST *compile_settings( PARSE *parse,FRAME *args );
LIST *compile_switch( PARSE *parse, FRAME *args );
LIST *compile_while( PARSE *parse, FRAME *args );

LIST *evaluate_rule( char *rulename, FRAME *args );

regexp* regex_compile( const char* pattern );

void profile_dump();

/* Flags for compile_set(), etc */

# define ASSIGN_SET	0x00	/* = assign variable */
# define ASSIGN_APPEND	0x01	/* += append variable */
# define ASSIGN_DEFAULT	0x02	/* set only if unset */

/* Flags for compile_setexec() */

# define EXEC_UPDATED	0x01	/* executes updated */
# define EXEC_TOGETHER	0x02	/* executes together */
# define EXEC_IGNORE	0x04	/* executes ignore */
# define EXEC_QUIETLY	0x08	/* executes quietly */
# define EXEC_PIECEMEAL	0x10	/* executes piecemeal */
# define EXEC_EXISTING	0x20	/* executes existing */

/* Conditions for compile_if() */

# define EXPR_NOT	0	/* ! cond */
# define EXPR_AND	1	/* cond && cond */
# define EXPR_OR	2	/* cond || cond */

# define EXPR_EXISTS	3	/* arg */
# define EXPR_EQUALS	4	/* arg = arg */
# define EXPR_NOTEQ	5	/* arg != arg */
# define EXPR_LESS	6	/* arg < arg  */
# define EXPR_LESSEQ	7	/* arg <= arg */
# define EXPR_MORE	8	/* arg > arg  */
# define EXPR_MOREEQ	9	/* arg >= arg */
# define EXPR_IN	10	/* arg in arg */

#endif // COMPILE_DWA20011022_H
