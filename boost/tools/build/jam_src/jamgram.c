/* A Bison parser, made from jamgram.y
   by GNU bison 1.33.  */

#define YYBISON 1  /* Identify Bison output.  */

# define	_BANG	257
# define	_BANG_EQUALS	258
# define	_AMPER	259
# define	_AMPERAMPER	260
# define	_LPAREN	261
# define	_RPAREN	262
# define	_PLUS_EQUALS	263
# define	_COLON	264
# define	_SEMIC	265
# define	_LANGLE	266
# define	_LANGLE_EQUALS	267
# define	_EQUALS	268
# define	_RANGLE	269
# define	_RANGLE_EQUALS	270
# define	_QUESTION_EQUALS	271
# define	_LBRACKET	272
# define	_RBRACKET	273
# define	ACTIONS	274
# define	BIND	275
# define	CASE	276
# define	DEFAULT	277
# define	ELSE	278
# define	EXISTING	279
# define	FOR	280
# define	IF	281
# define	IGNORE	282
# define	IN	283
# define	INCLUDE	284
# define	LOCAL	285
# define	MODULE	286
# define	ON	287
# define	PIECEMEAL	288
# define	QUIETLY	289
# define	RETURN	290
# define	RULE	291
# define	SWITCH	292
# define	TOGETHER	293
# define	UPDATED	294
# define	WHILE	295
# define	_LBRACE	296
# define	_BAR	297
# define	_BARBAR	298
# define	_RBRACE	299
# define	ARG	300
# define	STRING	301

#line 98 "jamgram.y"

#include "jam.h"

#include "lists.h"
#include "parse.h"
#include "scan.h"
#include "compile.h"
#include "newstr.h"

# define F0 (LIST *(*)(PARSE *, FRAME *))0
# define P0 (PARSE *)0
# define S0 (char *)0

# define pappend( l,r )    	parse_make( compile_append,l,r,P0,S0,S0,0 )
# define peval( c,l,r )	parse_make( compile_eval,l,r,P0,S0,S0,c )
# define pfor( s,l,r,x )    	parse_make( compile_foreach,l,r,P0,s,S0,x )
# define pif( l,r,t )	  	parse_make( compile_if,l,r,t,S0,S0,0 )
# define pwhile( l,r )	  	parse_make( compile_while,l,r,P0,S0,S0,0 )
# define pincl( l )       	parse_make( compile_include,l,P0,P0,S0,S0,0 )
# define plist( s )	  	parse_make( compile_list,P0,P0,P0,s,S0,0 )
# define plocal( l,r,t )  	parse_make( compile_local,l,r,t,S0,S0,0 )
# define pmodule( l,r )	  	parse_make( compile_module,l,r,P0,S0,S0,0 )
# define pnull()	  	parse_make( compile_null,P0,P0,P0,S0,S0,0 )
# define pon( l,r )	  	parse_make( compile_on,l,r,P0,S0,S0,0 )
# define prule( s,p )     	parse_make( compile_rule,p,P0,P0,s,S0,0 )
# define prules( l,r )	  	parse_make( compile_rules,l,r,P0,S0,S0,0 )
# define pset( l,r,a )          parse_make( compile_set,l,r,P0,S0,S0,a )
# define psetmodule( l,r,a ) 	parse_make( compile_set_module,l,r,P0,S0,S0,a )
# define pset1( l,r,t,a )	parse_make( compile_settings,l,r,t,S0,S0,a )
# define psetc( s,p,a,l )     	parse_make( compile_setcomp,p,a,P0,s,S0,l )
# define psete( s,l,s1,f ) 	parse_make( compile_setexec,l,P0,P0,s,s1,f )
# define pswitch( l,r )   	parse_make( compile_switch,l,r,P0,S0,S0,0 )

# define pnode( l,r )    	parse_make( F0,l,r,P0,S0,S0,0 )
# define psnode( s,l )     	parse_make( F0,l,P0,P0,s,S0,0 )

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		150
#define	YYFLAG		-32768
#define	YYNTBASE	48

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 301 ? yytranslate[x] : 69)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     1,     3,     5,     7,     9,    12,    18,    19,
      22,    24,    28,    29,    31,    32,    36,    40,    44,    49,
      55,    62,    66,    75,    81,    87,    93,    99,   107,   113,
     117,   118,   119,   129,   131,   133,   135,   138,   140,   144,
     148,   152,   156,   160,   164,   168,   172,   176,   180,   184,
     187,   191,   192,   195,   200,   202,   206,   208,   209,   212,
     214,   219,   220,   223,   225,   227,   229,   231,   233,   235,
     236
};
static const short yyrhs[] =
{
      -1,    50,     0,    51,     0,    50,     0,    55,     0,    55,
      50,     0,    31,    63,    52,    11,    49,     0,     0,    14,
      63,     0,    51,     0,     7,    62,     8,     0,     0,    31,
       0,     0,    42,    49,    45,     0,    30,    63,    11,     0,
      46,    62,    11,     0,    65,    58,    63,    11,     0,    32,
      31,    63,    52,    11,     0,    65,    33,    63,    58,    63,
      11,     0,    36,    63,    11,     0,    26,    54,    46,    29,
      63,    42,    49,    45,     0,    38,    63,    42,    60,    45,
       0,    27,    59,    42,    49,    45,     0,    32,    63,    42,
      49,    45,     0,    41,    59,    42,    49,    45,     0,    27,
      59,    42,    49,    45,    24,    55,     0,    54,    37,    46,
      53,    55,     0,    33,    65,    55,     0,     0,     0,    20,
      66,    46,    68,    42,    56,    47,    57,    45,     0,    14,
       0,     9,     0,    17,     0,    23,    14,     0,    65,     0,
      65,    14,    65,     0,    65,     4,    65,     0,    65,    12,
      65,     0,    65,    13,    65,     0,    65,    15,    65,     0,
      65,    16,    65,     0,    59,     5,    59,     0,    59,     6,
      59,     0,    59,    43,    59,     0,    59,    44,    59,     0,
      65,    29,    63,     0,     3,    59,     0,     7,    59,     8,
       0,     0,    61,    60,     0,    22,    46,    10,    49,     0,
      63,     0,    63,    10,    62,     0,    64,     0,     0,    64,
      65,     0,    46,     0,    18,    46,    62,    19,     0,     0,
      66,    67,     0,    40,     0,    39,     0,    28,     0,    35,
       0,    34,     0,    25,     0,     0,    21,    63,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   138,   140,   151,   153,   157,   159,   161,   165,   169,
     171,   175,   177,   181,   183,   187,   189,   191,   193,   195,
     197,   199,   201,   203,   205,   207,   209,   211,   213,   215,
     217,   217,   217,   229,   231,   233,   235,   242,   244,   246,
     248,   250,   252,   254,   256,   258,   260,   262,   264,   266,
     268,   279,   281,   285,   294,   296,   306,   310,   312,   316,
     318,   328,   330,   334,   336,   338,   340,   342,   344,   353,
     355
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "_BANG", "_BANG_EQUALS", "_AMPER", 
  "_AMPERAMPER", "_LPAREN", "_RPAREN", "_PLUS_EQUALS", "_COLON", "_SEMIC", 
  "_LANGLE", "_LANGLE_EQUALS", "_EQUALS", "_RANGLE", "_RANGLE_EQUALS", 
  "_QUESTION_EQUALS", "_LBRACKET", "_RBRACKET", "ACTIONS", "BIND", "CASE", 
  "DEFAULT", "ELSE", "EXISTING", "FOR", "IF", "IGNORE", "IN", "INCLUDE", 
  "LOCAL", "MODULE", "ON", "PIECEMEAL", "QUIETLY", "RETURN", "RULE", 
  "SWITCH", "TOGETHER", "UPDATED", "WHILE", "_LBRACE", "_BAR", "_BARBAR", 
  "_RBRACE", "ARG", "STRING", "run", "block", "rules", "null", 
  "assign_list_opt", "arglist_opt", "local_opt", "rule", "@1", "@2", 
  "assign", "expr", "cases", "case", "lol", "list", "listp", "arg", 
  "eflags", "eflag", "bindlist", NULL
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    48,    48,    49,    49,    50,    50,    50,    51,    52,
      52,    53,    53,    54,    54,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      56,    57,    55,    58,    58,    58,    58,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    60,    60,    61,    62,    62,    63,    64,    64,    65,
      65,    66,    66,    67,    67,    67,    67,    67,    67,    68,
      68
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     0,     1,     1,     1,     1,     2,     5,     0,     2,
       1,     3,     0,     1,     0,     3,     3,     3,     4,     5,
       6,     3,     8,     5,     5,     5,     5,     7,     5,     3,
       0,     0,     9,     1,     1,     1,     2,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       3,     0,     2,     4,     1,     3,     1,     0,     2,     1,
       4,     0,     2,     1,     1,     1,     1,     1,     1,     0,
       2
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       1,     0,    61,    14,     0,    57,    57,    57,     0,    57,
      57,     0,     8,    59,     2,     0,     5,     0,    57,     0,
      13,     0,     0,     0,    59,     0,    37,     0,    56,     8,
      57,     0,    14,     0,     0,     0,     0,     4,     3,     0,
      54,     0,     6,    34,    33,    35,     0,    57,    57,     0,
      68,    65,    67,    66,    64,    63,    69,    62,     0,    49,
       0,     0,     0,     8,     0,     0,     0,     0,     0,     0,
       0,     0,    57,    16,    58,    57,    10,     0,     8,     8,
      29,    21,    51,     8,    15,    17,    57,    12,    36,     0,
       0,    60,    57,     0,    57,    50,    44,    45,     0,    46,
      47,    39,    40,    41,    38,    42,    43,    48,     9,     8,
       0,     0,     0,     0,    51,     0,    55,    57,    14,    57,
      18,    70,    30,     0,    24,     7,    19,    25,     0,    23,
      52,    26,     0,    28,     0,     0,     8,    14,     8,    11,
      20,    31,     0,    27,    53,     0,    22,    32,     0,     0,
       0
};

static const short yydefgoto[] =
{
     148,    36,    37,    38,    77,   118,    15,    16,   135,   145,
      48,    25,   113,   114,    39,    40,    28,    17,    19,    57,
      93
};

static const short yypact[] =
{
      89,   -34,-32768,   -16,    10,-32768,   -19,    -7,    -2,-32768,
  -32768,    10,    89,    94,-32768,   -11,    89,   136,-32768,   143,
  -32768,   -17,    10,    10,-32768,     4,   151,    20,    -2,    18,
  -32768,    -8,   116,    34,     7,    30,     5,-32768,-32768,    43,
      45,    17,-32768,-32768,-32768,-32768,    50,-32768,-32768,    46,
  -32768,-32768,-32768,-32768,-32768,-32768,    47,-32768,    37,-32768,
      33,    10,    10,    89,    10,    10,    -2,    -2,    -2,    -2,
      -2,    -2,-32768,-32768,-32768,-32768,-32768,    58,    18,    89,
  -32768,-32768,    53,    89,-32768,-32768,-32768,    71,-32768,   115,
      68,-32768,-32768,    39,-32768,-32768,-32768,-32768,    38,    16,
      16,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    89,
      73,    40,    42,    41,    53,    56,-32768,-32768,   116,-32768,
  -32768,-32768,-32768,    61,    82,-32768,-32768,-32768,    98,-32768,
  -32768,-32768,   102,-32768,   106,    66,    89,   116,    89,-32768,
  -32768,-32768,    78,-32768,-32768,    83,-32768,-32768,   118,   133,
  -32768
};

static const short yypgoto[] =
{
  -32768,   -56,    14,   -18,    59,-32768,   138,   -26,-32768,-32768,
      55,    -3,    25,-32768,   -15,    -5,-32768,    29,-32768,-32768,
  -32768
};


#define	YYLAST		189


static const short yytable[] =
{
      27,    29,    31,    49,    33,    34,    80,    98,    35,    61,
      62,    76,    18,    22,    14,    20,     1,    23,   -13,    59,
      60,    61,    62,   111,    30,    78,    41,   115,     1,    58,
      42,    73,    75,    26,    79,    61,    62,    32,    61,    62,
      26,    95,    89,    90,    24,    81,    63,    64,    65,    82,
      84,    26,    26,   125,    85,    86,    24,    74,    96,    97,
      76,    99,   100,    87,    88,    91,    94,   107,    92,   109,
     108,   116,    83,    64,    65,   112,    64,    65,   117,   120,
     142,   122,   144,   124,   126,   127,   129,   121,   128,   123,
      26,    26,   133,    26,    26,   101,   102,   103,   104,   105,
     106,   131,   132,   136,   -57,   -57,   137,     1,   138,     2,
     139,   143,   -57,   141,   134,     3,     4,   140,   149,     5,
       6,     7,     8,   146,    43,     9,   -14,    10,   147,    44,
      11,    12,    45,   150,     1,    13,     2,   110,    46,   130,
     -57,    21,     3,     4,   119,    43,     5,    20,     7,     8,
      44,     0,     9,    45,    10,    66,     0,    11,    12,    46,
       0,     0,    13,    67,    68,    69,    70,    71,    50,    47,
       0,    51,     0,     0,     0,     0,     0,    52,    53,     0,
      72,     0,    54,    55,     0,     0,     0,     0,     0,    56
};

static const short yycheck[] =
{
       5,     6,     7,    18,     9,    10,    32,    63,    11,     5,
       6,    29,    46,     3,     0,    31,    18,     7,    37,    22,
      23,     5,     6,    79,    31,    30,    37,    83,    18,    46,
      16,    11,    14,     4,    42,     5,     6,     8,     5,     6,
      11,     8,    47,    48,    46,    11,    42,    43,    44,    42,
      45,    22,    23,   109,    11,    10,    46,    28,    61,    62,
      78,    64,    65,    46,    14,    19,    29,    72,    21,    11,
      75,    86,    42,    43,    44,    22,    43,    44,     7,    11,
     136,    42,   138,    45,    11,    45,    45,    92,    46,    94,
      61,    62,   118,    64,    65,    66,    67,    68,    69,    70,
      71,    45,   117,    42,    10,    11,    24,    18,    10,    20,
       8,   137,    18,    47,   119,    26,    27,    11,     0,    30,
      31,    32,    33,    45,     9,    36,    37,    38,    45,    14,
      41,    42,    17,     0,    18,    46,    20,    78,    23,   114,
      46,     3,    26,    27,    89,     9,    30,    31,    32,    33,
      14,    -1,    36,    17,    38,     4,    -1,    41,    42,    23,
      -1,    -1,    46,    12,    13,    14,    15,    16,    25,    33,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    34,    35,    -1,
      29,    -1,    39,    40,    -1,    -1,    -1,    -1,    -1,    46
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison/bison.simple"

/* Skeleton output parser for bison,

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software
   Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser when
   the %semantic_parser declaration is not specified in the grammar.
   It was written by Richard Stallman by simplifying the hairy parser
   used when %semantic_parser is specified.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

#ifdef __cplusplus
# define YYSTD(x) std::x
#else
# define YYSTD(x) x
#endif

#if ! defined (yyoverflow) || defined (YYERROR_VERBOSE)

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  ifdef __cplusplus
#   include <cstdlib> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T std::size_t
#  else
#   ifdef __STDC__
#    include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#    define YYSIZE_T size_t
#   endif
#  endif
#  define YYSTACK_ALLOC YYSTD (malloc)
#  define YYSTACK_FREE YYSTD (free)
# endif

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
# if YYLSP_NEEDED
  YYLTYPE yyls;
# endif
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# if YYLSP_NEEDED
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAX)
# else
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)
# endif

/* Relocate the TYPE STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Type, Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	yymemcpy ((char *) yyptr, (char *) (Stack),			\
		  yysize * (YYSIZE_T) sizeof (Type));			\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (Type) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif /* ! defined (yyoverflow) || defined (YYERROR_VERBOSE) */


#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# ifdef __cplusplus
#  include <cstddef> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T std::size_t
# else
#  ifdef __STDC__
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");			\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).

   When YYLLOC_DEFAULT is run, CURRENT is set the location of the
   first token.  By default, to implement support for ranges, extend
   its range to the last symbol.  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)       	\
   Current.last_line   = Rhs[N].last_line;	\
   Current.last_column = Rhs[N].last_column;
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#if YYPURE
# if YYLSP_NEEDED
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, &yylloc, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval, &yylloc)
#  endif
# else /* !YYLSP_NEEDED */
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval)
#  endif
# endif /* !YYLSP_NEEDED */
#else /* !YYPURE */
# define YYLEX			yylex ()
#endif /* !YYPURE */


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  ifdef __cplusplus
#   include <cstdio>  /* INFRINGES ON USER NAME SPACE */
#  else
#   include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYFPRINTF YYSTD (fprintf)
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)
/* Nonzero means print parse trace. [The following comment makes no
   sense to me.  Could someone clarify it?  --akim] Since this is
   uninitialized, it does not stop multiple parsers from coexisting.
   */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

#if ! defined (yyoverflow) && ! defined (yymemcpy)
# if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#  define yymemcpy __builtin_memcpy
# else				/* not GNU C or C++ */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
#  if defined (__STDC__) || defined (__cplusplus)
yymemcpy (char *yyto, const char *yyfrom, YYSIZE_T yycount)
#  else
yymemcpy (yyto, yyfrom, yycount)
     char *yyto;
     const char *yyfrom;
     YYSIZE_T yycount;
#  endif
{
  register const char *yyf = yyfrom;
  register char *yyt = yyto;
  register YYSIZE_T yyi = yycount;

  while (yyi-- != 0)
    *yyt++ = *yyf++;
}
# endif
#endif

#ifdef YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif
#endif

#line 341 "/usr/share/bison/bison.simple"


/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# ifdef __cplusplus
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else /* !__cplusplus */
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif /* !__cplusplus */
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
int yyparse (void *);
# else
int yyparse (void);
# endif
#endif

/* YY_DECL_VARIABLES -- depending whether we use a pure parser,
   variables are global, or local to YYPARSE.  */

#define YY_DECL_NON_LSP_VARIABLES			\
/* The lookahead symbol.  */				\
int yychar;						\
							\
/* The semantic value of the lookahead symbol. */	\
YYSTYPE yylval;						\
							\
/* Number of parse errors so far.  */			\
int yynerrs;

#if YYLSP_NEEDED
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES			\
						\
/* Location data for the lookahead symbol.  */	\
YYLTYPE yylloc;
#else
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES
#endif


/* If nonreentrant, generate the variables here. */

#if !YYPURE
YY_DECL_VARIABLES
#endif  /* !YYPURE */

int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  /* If reentrant, generate the variables here. */
#if YYPURE
  YY_DECL_VARIABLES
#endif  /* !YYPURE */

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack. */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

#if YYLSP_NEEDED
  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
#endif

#if YYLSP_NEEDED
# define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
# define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  YYSIZE_T yystacksize = YYINITDEPTH;


  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
#if YYLSP_NEEDED
  YYLTYPE yyloc;
#endif

  /* When reducing, the number of symbols on the RHS of the reduced
     rule. */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
#if YYLSP_NEEDED
  yylsp = yyls;
#endif
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  */
# if YYLSP_NEEDED
	YYLTYPE *yyls1 = yyls;
	/* This used to be a conditional around just the two extra args,
	   but that might be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
# else
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);
# endif
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (short, yyss);
	YYSTACK_RELOCATE (YYSTYPE, yyvs);
# if YYLSP_NEEDED
	YYSTACK_RELOCATE (YYLTYPE, yyls);
# endif
# undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
#if YYLSP_NEEDED
      yylsp = yyls + yysize - 1;
#endif

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

#if YYDEBUG
     /* We have to keep this `#if YYDEBUG', since we use variables
	which are defined only if `YYDEBUG' is set.  */
      if (yydebug)
	{
	  YYFPRINTF (stderr, "Next token is %d (%s",
		     yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise
	     meaning of a token, for further debugging info.  */
# ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
# endif
	  YYFPRINTF (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to the semantic value of
     the lookahead token.  This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

#if YYLSP_NEEDED
  /* Similarly for the default location.  Let the user run additional
     commands if for instance locations are ranges.  */
  yyloc = yylsp[1-yylen];
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
#endif

#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] > 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif

  switch (yyn) {

case 2:
#line 141 "jamgram.y"
{ parse_save( yyvsp[0].parse ); }
    break;
case 3:
#line 152 "jamgram.y"
{ yyval.parse = yyvsp[0].parse; }
    break;
case 4:
#line 154 "jamgram.y"
{ yyval.parse = yyvsp[0].parse; }
    break;
case 5:
#line 158 "jamgram.y"
{ yyval.parse = yyvsp[0].parse; }
    break;
case 6:
#line 160 "jamgram.y"
{ yyval.parse = prules( yyvsp[-1].parse, yyvsp[0].parse ); }
    break;
case 7:
#line 162 "jamgram.y"
{ yyval.parse = plocal( yyvsp[-3].parse, yyvsp[-2].parse, yyvsp[0].parse ); }
    break;
case 8:
#line 166 "jamgram.y"
{ yyval.parse = pnull(); }
    break;
case 9:
#line 170 "jamgram.y"
{ yyval.parse = yyvsp[0].parse; yyval.number = ASSIGN_SET; }
    break;
case 10:
#line 172 "jamgram.y"
{ yyval.parse = yyvsp[0].parse; yyval.number = ASSIGN_APPEND; }
    break;
case 11:
#line 176 "jamgram.y"
{ yyval.parse = yyvsp[-1].parse; }
    break;
case 12:
#line 178 "jamgram.y"
{ yyval.parse = P0; }
    break;
case 13:
#line 182 "jamgram.y"
{ yyval.number = 1; }
    break;
case 14:
#line 184 "jamgram.y"
{ yyval.number = 0; }
    break;
case 15:
#line 188 "jamgram.y"
{ yyval.parse = yyvsp[-1].parse; }
    break;
case 16:
#line 190 "jamgram.y"
{ yyval.parse = pincl( yyvsp[-1].parse ); }
    break;
case 17:
#line 192 "jamgram.y"
{ yyval.parse = prule( yyvsp[-2].string, yyvsp[-1].parse ); }
    break;
case 18:
#line 194 "jamgram.y"
{ yyval.parse = pset( yyvsp[-3].parse, yyvsp[-1].parse, yyvsp[-2].number ); }
    break;
case 19:
#line 196 "jamgram.y"
{ yyval.parse = psetmodule( yyvsp[-2].parse, yyvsp[-1].parse, yyvsp[-1].number ); }
    break;
case 20:
#line 198 "jamgram.y"
{ yyval.parse = pset1( yyvsp[-5].parse, yyvsp[-3].parse, yyvsp[-1].parse, yyvsp[-2].number ); }
    break;
case 21:
#line 200 "jamgram.y"
{ yyval.parse = yyvsp[-1].parse; }
    break;
case 22:
#line 202 "jamgram.y"
{ yyval.parse = pfor( yyvsp[-5].string, yyvsp[-3].parse, yyvsp[-1].parse, yyvsp[-6].number ); }
    break;
case 23:
#line 204 "jamgram.y"
{ yyval.parse = pswitch( yyvsp[-3].parse, yyvsp[-1].parse ); }
    break;
case 24:
#line 206 "jamgram.y"
{ yyval.parse = pif( yyvsp[-3].parse, yyvsp[-1].parse, pnull() ); }
    break;
case 25:
#line 208 "jamgram.y"
{ yyval.parse = pmodule( yyvsp[-3].parse, yyvsp[-1].parse ); }
    break;
case 26:
#line 210 "jamgram.y"
{ yyval.parse = pwhile( yyvsp[-3].parse, yyvsp[-1].parse ); }
    break;
case 27:
#line 212 "jamgram.y"
{ yyval.parse = pif( yyvsp[-5].parse, yyvsp[-3].parse, yyvsp[0].parse ); }
    break;
case 28:
#line 214 "jamgram.y"
{ yyval.parse = psetc( yyvsp[-2].string, yyvsp[0].parse, yyvsp[-1].parse, yyvsp[-4].number ); }
    break;
case 29:
#line 216 "jamgram.y"
{ yyval.parse = pon( yyvsp[-1].parse, yyvsp[0].parse ); }
    break;
case 30:
#line 218 "jamgram.y"
{ yymode( SCAN_STRING ); }
    break;
case 31:
#line 220 "jamgram.y"
{ yymode( SCAN_NORMAL ); }
    break;
case 32:
#line 222 "jamgram.y"
{ yyval.parse = psete( yyvsp[-6].string,yyvsp[-5].parse,yyvsp[-2].string,yyvsp[-7].number ); }
    break;
case 33:
#line 230 "jamgram.y"
{ yyval.number = ASSIGN_SET; }
    break;
case 34:
#line 232 "jamgram.y"
{ yyval.number = ASSIGN_APPEND; }
    break;
case 35:
#line 234 "jamgram.y"
{ yyval.number = ASSIGN_DEFAULT; }
    break;
case 36:
#line 236 "jamgram.y"
{ yyval.number = ASSIGN_DEFAULT; }
    break;
case 37:
#line 243 "jamgram.y"
{ yyval.parse = peval( EXPR_EXISTS, yyvsp[0].parse, pnull() ); }
    break;
case 38:
#line 245 "jamgram.y"
{ yyval.parse = peval( EXPR_EQUALS, yyvsp[-2].parse, yyvsp[0].parse ); }
    break;
case 39:
#line 247 "jamgram.y"
{ yyval.parse = peval( EXPR_NOTEQ, yyvsp[-2].parse, yyvsp[0].parse ); }
    break;
case 40:
#line 249 "jamgram.y"
{ yyval.parse = peval( EXPR_LESS, yyvsp[-2].parse, yyvsp[0].parse ); }
    break;
case 41:
#line 251 "jamgram.y"
{ yyval.parse = peval( EXPR_LESSEQ, yyvsp[-2].parse, yyvsp[0].parse ); }
    break;
case 42:
#line 253 "jamgram.y"
{ yyval.parse = peval( EXPR_MORE, yyvsp[-2].parse, yyvsp[0].parse ); }
    break;
case 43:
#line 255 "jamgram.y"
{ yyval.parse = peval( EXPR_MOREEQ, yyvsp[-2].parse, yyvsp[0].parse ); }
    break;
case 44:
#line 257 "jamgram.y"
{ yyval.parse = peval( EXPR_AND, yyvsp[-2].parse, yyvsp[0].parse ); }
    break;
case 45:
#line 259 "jamgram.y"
{ yyval.parse = peval( EXPR_AND, yyvsp[-2].parse, yyvsp[0].parse ); }
    break;
case 46:
#line 261 "jamgram.y"
{ yyval.parse = peval( EXPR_OR, yyvsp[-2].parse, yyvsp[0].parse ); }
    break;
case 47:
#line 263 "jamgram.y"
{ yyval.parse = peval( EXPR_OR, yyvsp[-2].parse, yyvsp[0].parse ); }
    break;
case 48:
#line 265 "jamgram.y"
{ yyval.parse = peval( EXPR_IN, yyvsp[-2].parse, yyvsp[0].parse ); }
    break;
case 49:
#line 267 "jamgram.y"
{ yyval.parse = peval( EXPR_NOT, yyvsp[0].parse, pnull() ); }
    break;
case 50:
#line 269 "jamgram.y"
{ yyval.parse = yyvsp[-1].parse; }
    break;
case 51:
#line 280 "jamgram.y"
{ yyval.parse = P0; }
    break;
case 52:
#line 282 "jamgram.y"
{ yyval.parse = pnode( yyvsp[-1].parse, yyvsp[0].parse ); }
    break;
case 53:
#line 286 "jamgram.y"
{ yyval.parse = psnode( yyvsp[-2].string, yyvsp[0].parse ); }
    break;
case 54:
#line 295 "jamgram.y"
{ yyval.parse = pnode( P0, yyvsp[0].parse ); }
    break;
case 55:
#line 297 "jamgram.y"
{ yyval.parse = pnode( yyvsp[0].parse, yyvsp[-2].parse ); }
    break;
case 56:
#line 307 "jamgram.y"
{ yyval.parse = yyvsp[0].parse; yymode( SCAN_NORMAL ); }
    break;
case 57:
#line 311 "jamgram.y"
{ yyval.parse = pnull(); yymode( SCAN_PUNCT ); }
    break;
case 58:
#line 313 "jamgram.y"
{ yyval.parse = pappend( yyvsp[-1].parse, yyvsp[0].parse ); }
    break;
case 59:
#line 317 "jamgram.y"
{ yyval.parse = plist( yyvsp[0].string ); }
    break;
case 60:
#line 319 "jamgram.y"
{ yyval.parse = prule( yyvsp[-2].string, yyvsp[-1].parse ); }
    break;
case 61:
#line 329 "jamgram.y"
{ yyval.number = 0; }
    break;
case 62:
#line 331 "jamgram.y"
{ yyval.number = yyvsp[-1].number | yyvsp[0].number; }
    break;
case 63:
#line 335 "jamgram.y"
{ yyval.number = EXEC_UPDATED; }
    break;
case 64:
#line 337 "jamgram.y"
{ yyval.number = EXEC_TOGETHER; }
    break;
case 65:
#line 339 "jamgram.y"
{ yyval.number = EXEC_IGNORE; }
    break;
case 66:
#line 341 "jamgram.y"
{ yyval.number = EXEC_QUIETLY; }
    break;
case 67:
#line 343 "jamgram.y"
{ yyval.number = EXEC_PIECEMEAL; }
    break;
case 68:
#line 345 "jamgram.y"
{ yyval.number = EXEC_EXISTING; }
    break;
case 69:
#line 354 "jamgram.y"
{ yyval.parse = pnull(); }
    break;
case 70:
#line 356 "jamgram.y"
{ yyval.parse = yyvsp[0].parse; }
    break;
}

#line 727 "/usr/share/bison/bison.simple"


  yyvsp -= yylen;
  yyssp -= yylen;
#if YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;
#if YYLSP_NEEDED
  *++yylsp = yyloc;
#endif

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[YYTRANSLATE (yychar)]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[YYTRANSLATE (yychar)]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exhausted");
	}
      else
#endif /* defined (YYERROR_VERBOSE) */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*--------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action |
`--------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;
      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;


/*-------------------------------------------------------------------.
| yyerrdefault -- current state does not do anything special for the |
| error token.                                                       |
`-------------------------------------------------------------------*/
yyerrdefault:
#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */

  /* If its default is to accept any token, ok.  Otherwise pop it.  */
  yyn = yydefact[yystate];
  if (yyn)
    goto yydefault;
#endif


/*---------------------------------------------------------------.
| yyerrpop -- pop the current state because it cannot handle the |
| error token                                                    |
`---------------------------------------------------------------*/
yyerrpop:
  if (yyssp == yyss)
    YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#if YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "Error: state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

/*--------------.
| yyerrhandle.  |
`--------------*/
yyerrhandle:
  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

/*---------------------------------------------.
| yyoverflowab -- parser overflow comes here.  |
`---------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}
#line 360 "jamgram.y"
