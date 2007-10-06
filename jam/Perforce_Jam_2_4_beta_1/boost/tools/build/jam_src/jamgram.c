#ifndef lint
static char const 
yyrcsid[] = "$FreeBSD: src/usr.bin/yacc/skeleton.c,v 1.28 2000/01/17 02:04:06 bde Exp $";
#endif
#include <stdlib.h>
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYLEX yylex()
#define YYEMPTY -1
#define yyclearin (yychar=(YYEMPTY))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING() (yyerrflag!=0)
static int yygrowstack();
#define YYPREFIX "yy"
#line 89 "jamgram.y"
#include "jam.h"

#include "lists.h"
#include "parse.h"
#include "scan.h"
#include "compile.h"
#include "newstr.h"

# define F0 (LIST *(*)(PARSE *, LOL *))0
# define P0 (PARSE *)0
# define S0 (char *)0

# define pappend( l,r )    	parse_make( compile_append,l,r,P0,S0,S0,0 )
# define peval( c,l,r )		parse_make( compile_eval,l,r,P0,S0,S0,c )
# define pfor( s,l,r )    	parse_make( compile_foreach,l,r,P0,s,S0,0 )
# define pif( l,r,t )	  	parse_make( compile_if,l,r,t,S0,S0,0 )
# define pincl( l )       	parse_make( compile_include,l,P0,P0,S0,S0,0 )
# define plist( s )	  	parse_make( compile_list,P0,P0,P0,s,S0,0 )
# define plocal( l,r,t )  	parse_make( compile_local,l,r,t,S0,S0,0 )
# define pnull()	  	parse_make( compile_null,P0,P0,P0,S0,S0,0 )
# define pon( l,r )	  	parse_make( compile_on,l,r,P0,S0,S0,0 )
# define prule( s,p )     	parse_make( compile_rule,p,P0,P0,s,S0,0 )
# define prules( l,r )	  	parse_make( compile_rules,l,r,P0,S0,S0,0 )
# define pset( l,r,a ) 	  	parse_make( compile_set,l,r,P0,S0,S0,a )
# define pset1( l,r,t,a )	parse_make( compile_settings,l,r,t,S0,S0,a )
# define psetc( s,p )     	parse_make( compile_setcomp,p,P0,P0,s,S0,0 )
# define psete( s,l,s1,f ) 	parse_make( compile_setexec,l,P0,P0,s,s1,f )
# define pswitch( l,r )   	parse_make( compile_switch,l,r,P0,S0,S0,0 )
# define pwhile( l,r )   	parse_make( compile_while,l,r,P0,S0,S0,0 )

# define pnode( l,r )    	parse_make( F0,l,r,P0,S0,S0,0 )
# define psnode( s,l )     	parse_make( F0,l,P0,P0,s,S0,0 )

#line 51 "y.tab.c"
#define YYERRCODE 256
#define _BANG 257
#define _BANG_EQUALS 258
#define _AMPER 259
#define _AMPERAMPER 260
#define _LPAREN 261
#define _RPAREN 262
#define _PLUS_EQUALS 263
#define _COLON 264
#define _SEMIC 265
#define _LANGLE 266
#define _LANGLE_EQUALS 267
#define _EQUALS 268
#define _RANGLE 269
#define _RANGLE_EQUALS 270
#define _QUESTION_EQUALS 271
#define _LBRACKET 272
#define _RBRACKET 273
#define ACTIONS 274
#define BIND 275
#define CASE 276
#define DEFAULT 277
#define ELSE 278
#define EXISTING 279
#define FOR 280
#define IF 281
#define IGNORE 282
#define IN 283
#define INCLUDE 284
#define LOCAL 285
#define ON 286
#define PIECEMEAL 287
#define QUIETLY 288
#define RETURN 289
#define RULE 290
#define SWITCH 291
#define TOGETHER 292
#define UPDATED 293
#define WHILE 294
#define _LBRACE 295
#define _BAR 296
#define _BARBAR 297
#define _RBRACE 298
#define ARG 299
#define STRING 300
const short yylhs[] = {                                        -1,
    0,    0,    2,    2,    1,    1,    1,    1,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,   12,   13,    3,    7,    7,    7,    7,    9,    9,
    9,    9,    9,    9,    9,    9,    9,    9,    9,    9,
    9,    9,    8,    8,   14,    5,    5,    4,   15,   15,
    6,   17,    6,   16,   16,   16,   10,   10,   18,   18,
   18,   18,   18,   18,   11,   11,
};
const short yylen[] = {                                         2,
    0,    1,    0,    1,    1,    2,    4,    6,    3,    3,
    3,    4,    6,    3,    7,    5,    5,    7,    5,    3,
    3,    0,    0,    9,    1,    1,    1,    2,    1,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    2,    3,    0,    2,    4,    1,    3,    1,    0,    2,
    1,    0,    4,    2,    4,    4,    0,    2,    1,    1,
    1,    1,    1,    1,    0,    2,
};
const short yydefred[] = {                                      0,
   52,   57,    0,    0,   49,   49,    0,   49,    0,   49,
    0,    0,    0,    0,    2,    0,    0,    0,    0,    0,
    0,    0,   51,   29,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    4,    0,    0,    0,    6,   26,   25,
   27,    0,   49,   49,    0,   49,    0,   64,   61,   63,
   62,   60,   59,    0,   58,   49,   41,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   10,   50,    0,   49,   21,   14,   20,    0,    0,    9,
   49,   11,   28,    0,    0,    0,   54,   53,   49,    0,
    0,   42,    0,    0,    0,   32,   33,    0,   34,   35,
    0,    0,    0,    0,    7,    0,    0,    0,    0,    0,
   47,   49,   12,   49,   49,   66,   22,    0,    0,    0,
    0,   16,   44,   19,    0,   56,   55,    0,    0,    0,
    8,    0,   13,   23,   15,   18,   45,    0,   24,
};
const short yydgoto[] = {                                      14,
   34,   35,   16,   36,   37,   24,   44,  108,   25,   19,
   90,  128,  138,  109,   27,   47,   18,   55,
};
const short yysindex[] = {                                     31,
    0,    0, -283, -236,    0,    0, -248,    0, -272,    0,
 -236,   31,    0,    0,    0,   31,  -71, -249,  -31, -255,
 -236, -236,    0,    0, -159, -212, -248, -194,   55, -211,
   55, -235, -119,    0, -239, -192, -174,    0,    0,    0,
    0, -195,    0,    0, -248,    0, -177,    0,    0,    0,
    0,    0,    0, -178,    0,    0,    0, -101, -236, -236,
 -236, -236, -236, -236, -236, -236, -236,   31, -236, -236,
    0,    0,   31,    0,    0,    0,    0, -172,   31,    0,
    0,    0,    0, -225, -167, -231,    0,    0,    0, -193,
 -190,    0, -114, -140, -140,    0,    0, -114,    0,    0,
 -114, -186,   93,   93,    0, -149, -176, -173, -172, -165,
    0,    0,    0,    0,    0,    0,    0,   31, -157,   31,
 -133,    0,    0,    0, -130,    0,    0, -158, -154,   55,
    0,   31,    0,    0,    0,    0,    0, -153,    0,
};
const short yyrindex[] = {                                    146,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -144,  -36,    0,    0,    3,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  -19,    0,    0,    0,
    0,    0,    0,    0,    0, -170,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -135,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, -144,    0,    0,
    0,    0,    4,    0,    0,    0,    0, -136, -144,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  -79, -240, -182,    0,    0,  -74,    0,    0,
  -57,    0, -256, -230,    0,    0,    0,    0, -136,    0,
    0,    0,    0,    0,    0,    0,    0, -144,    1,    4,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -268,    0,    0,    0,    0,    0,    0,    0,
};
const short yygindex[] = {                                      0,
   26,  -56,  -24,    5,  -46,    2,   79,   61,   23,    0,
    0,    0,    0,    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 376
const short yytable[] = {                                      87,
   17,   17,    5,    3,   75,   38,   77,    3,   29,   26,
   28,  102,   30,   17,   32,   20,  105,   17,   36,   36,
   21,   36,  110,    1,   22,   15,   31,   56,   72,    3,
   17,   39,   17,   33,  111,    1,   45,   39,   38,   38,
   38,   38,   40,   57,   58,   41,   86,   84,   85,   46,
   23,   42,   71,   76,   36,   36,   36,  114,   80,   78,
   91,  129,   23,  131,   39,   39,   39,  115,  127,   17,
   73,   81,   83,   74,   17,  137,   37,   37,  106,   37,
   17,   93,   94,   95,   96,   97,   98,   99,  100,  101,
   82,  103,  104,  116,   46,   88,   89,  113,   59,   60,
   61,  117,   46,  107,  118,  136,   62,   63,   64,   65,
   66,  119,   37,   37,   37,  120,  125,   59,  126,   17,
  130,   17,  121,   67,  122,   62,   63,   64,   65,   66,
  132,   17,  124,   17,  133,   68,   69,   70,   59,   60,
   61,  134,   67,  135,  139,    1,   62,   63,   64,   65,
   66,   62,   63,    3,   65,   66,   59,   60,   61,   65,
   92,   43,  112,   67,   62,   63,   64,   65,   66,  123,
    0,    0,    0,    0,    0,   79,   69,   70,   31,   31,
   31,   67,   31,   30,   30,   30,    0,   30,   31,    0,
    0,   39,    0,   30,   69,   70,   40,    0,    0,   41,
   40,   40,   40,   31,   40,   42,    0,    0,   30,    0,
   40,    0,    0,    0,   43,   31,   31,   31,    0,    0,
   30,   30,   30,    0,    0,   40,   51,   49,   49,    0,
    0,   51,    0,    0,   51,   49,    0,   40,   40,   40,
   51,    0,    0,   48,   48,   48,    0,   48,   48,   51,
   49,   48,    0,   48,    0,   50,   51,   48,    0,    0,
   52,   53,   49,    0,    0,    0,    0,   54,    0,    0,
    0,    0,   17,    0,   17,   48,   17,    0,    5,    3,
   17,   17,    0,    0,   17,   17,   17,    0,    0,   17,
   17,   17,    0,    0,   17,   17,    0,    0,   17,   17,
    5,    3,    1,    0,    2,    0,    0,    0,    0,    0,
    3,    4,    0,    0,    5,    6,    7,    0,    0,    8,
    9,   10,    0,    0,   11,   12,    1,    0,    2,   13,
    0,    0,    0,    0,    3,    4,    0,    0,    5,    0,
    7,    0,    0,    8,    9,   10,    0,    0,   11,   12,
   59,   60,   61,   13,    0,    0,    0,    0,   62,   63,
   64,   65,   66,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   67,
};
const short yycheck[] = {                                      46,
    0,    0,    0,    0,   29,  262,   31,  276,    7,    5,
    6,   68,    8,   12,   10,  299,   73,   16,  259,  260,
  257,  262,   79,  272,  261,    0,  299,  283,   27,  298,
   29,  262,   31,   11,   81,  272,  286,  263,  295,  296,
  297,   16,  268,   21,   22,  271,   45,   43,   44,  299,
  299,  277,  265,  265,  295,  296,  297,  289,  298,  295,
   56,  118,  299,  120,  295,  296,  297,  299,  115,   68,
  265,  264,  268,  268,   73,  132,  259,  260,   74,  262,
   79,   59,   60,   61,   62,   63,   64,   65,   66,   67,
  265,   69,   70,   89,  265,  273,  275,  265,  258,  259,
  260,  295,  273,  276,  295,  130,  266,  267,  268,  269,
  270,  298,  295,  296,  297,  265,  112,  258,  114,  118,
  278,  120,  299,  283,  298,  266,  267,  268,  269,  270,
  264,  130,  298,  132,  265,  295,  296,  297,  258,  259,
  260,  300,  283,  298,  298,    0,  266,  267,  268,  269,
  270,  266,  267,  298,  269,  270,  258,  259,  260,  295,
  262,  298,   84,  283,  266,  267,  268,  269,  270,  109,
   -1,   -1,   -1,   -1,   -1,  295,  296,  297,  258,  259,
  260,  283,  262,  258,  259,  260,   -1,  262,  268,   -1,
   -1,  263,   -1,  268,  296,  297,  268,   -1,   -1,  271,
  258,  259,  260,  283,  262,  277,   -1,   -1,  283,   -1,
  268,   -1,   -1,   -1,  286,  295,  296,  297,   -1,   -1,
  295,  296,  297,   -1,   -1,  283,  263,  264,  265,   -1,
   -1,  268,   -1,   -1,  271,  272,   -1,  295,  296,  297,
  277,   -1,   -1,  263,  264,  265,   -1,  279,  268,  286,
  282,  271,   -1,  273,   -1,  287,  288,  277,   -1,   -1,
  292,  293,  299,   -1,   -1,   -1,   -1,  299,   -1,   -1,
   -1,   -1,  272,   -1,  274,  295,  276,   -1,  276,  276,
  280,  281,   -1,   -1,  284,  285,  286,   -1,   -1,  289,
  290,  291,   -1,   -1,  294,  295,   -1,   -1,  298,  299,
  298,  298,  272,   -1,  274,   -1,   -1,   -1,   -1,   -1,
  280,  281,   -1,   -1,  284,  285,  286,   -1,   -1,  289,
  290,  291,   -1,   -1,  294,  295,  272,   -1,  274,  299,
   -1,   -1,   -1,   -1,  280,  281,   -1,   -1,  284,   -1,
  286,   -1,   -1,  289,  290,  291,   -1,   -1,  294,  295,
  258,  259,  260,  299,   -1,   -1,   -1,   -1,  266,  267,
  268,  269,  270,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  283,
};
#define YYFINAL 14
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 300
#if YYDEBUG
const char * const yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"_BANG","_BANG_EQUALS","_AMPER",
"_AMPERAMPER","_LPAREN","_RPAREN","_PLUS_EQUALS","_COLON","_SEMIC","_LANGLE",
"_LANGLE_EQUALS","_EQUALS","_RANGLE","_RANGLE_EQUALS","_QUESTION_EQUALS",
"_LBRACKET","_RBRACKET","ACTIONS","BIND","CASE","DEFAULT","ELSE","EXISTING",
"FOR","IF","IGNORE","IN","INCLUDE","LOCAL","ON","PIECEMEAL","QUIETLY","RETURN",
"RULE","SWITCH","TOGETHER","UPDATED","WHILE","_LBRACE","_BAR","_BARBAR",
"_RBRACE","ARG","STRING",
};
const char * const yyrule[] = {
"$accept : run",
"run :",
"run : rules",
"block :",
"block : rules",
"rules : rule",
"rules : rule rules",
"rules : LOCAL list _SEMIC block",
"rules : LOCAL list _EQUALS list _SEMIC block",
"rule : _LBRACE block _RBRACE",
"rule : INCLUDE list _SEMIC",
"rule : ARG lol _SEMIC",
"rule : arg assign list _SEMIC",
"rule : arg ON list assign list _SEMIC",
"rule : RETURN list _SEMIC",
"rule : FOR ARG IN list _LBRACE block _RBRACE",
"rule : SWITCH list _LBRACE cases _RBRACE",
"rule : IF expr _LBRACE block _RBRACE",
"rule : IF expr _LBRACE block _RBRACE ELSE rule",
"rule : WHILE expr _LBRACE block _RBRACE",
"rule : RULE ARG rule",
"rule : ON arg rule",
"$$1 :",
"$$2 :",
"rule : ACTIONS eflags ARG bindlist _LBRACE $$1 STRING $$2 _RBRACE",
"assign : _EQUALS",
"assign : _PLUS_EQUALS",
"assign : _QUESTION_EQUALS",
"assign : DEFAULT _EQUALS",
"expr : arg",
"expr : expr _EQUALS expr",
"expr : expr _BANG_EQUALS expr",
"expr : expr _LANGLE expr",
"expr : expr _LANGLE_EQUALS expr",
"expr : expr _RANGLE expr",
"expr : expr _RANGLE_EQUALS expr",
"expr : expr _AMPER expr",
"expr : expr _AMPERAMPER expr",
"expr : expr _BAR expr",
"expr : expr _BARBAR expr",
"expr : expr IN expr",
"expr : _BANG expr",
"expr : _LPAREN expr _RPAREN",
"cases :",
"cases : case cases",
"case : CASE ARG _COLON block",
"lol : list",
"lol : list _COLON lol",
"list : listp",
"listp :",
"listp : listp arg",
"arg : ARG",
"$$3 :",
"arg : _LBRACKET $$3 func _RBRACKET",
"func : ARG lol",
"func : ON arg ARG lol",
"func : ON arg RETURN list",
"eflags :",
"eflags : eflags eflag",
"eflag : UPDATED",
"eflag : TOGETHER",
"eflag : IGNORE",
"eflag : QUIETLY",
"eflag : PIECEMEAL",
"eflag : EXISTING",
"bindlist :",
"bindlist : BIND list",
};
#endif
#ifndef YYSTYPE
typedef int YYSTYPE;
#endif
#if YYDEBUG
#include <stdio.h>
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH 10000
#endif
#endif
#define YYINITSTACKSIZE 200
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short *yyss;
short *yysslim;
YYSTYPE *yyvs;
int yystacksize;
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack()
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;
    i = yyssp - yyss;
    newss = yyss ? (short *)realloc(yyss, newsize * sizeof *newss) :
      (short *)malloc(newsize * sizeof *newss);
    if (newss == NULL)
        return -1;
    yyss = newss;
    yyssp = newss + i;
    newvs = yyvs ? (YYSTYPE *)realloc(yyvs, newsize * sizeof *newvs) :
      (YYSTYPE *)malloc(newsize * sizeof *newvs);
    if (newvs == NULL)
        return -1;
    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab

#ifndef YYPARSE_PARAM
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG void
#define YYPARSE_PARAM_DECL
#else	/* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif	/* ANSI-C/C++ */
#else	/* YYPARSE_PARAM */
#ifndef YYPARSE_PARAM_TYPE
#define YYPARSE_PARAM_TYPE void *
#endif
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG YYPARSE_PARAM_TYPE YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else	/* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL YYPARSE_PARAM_TYPE YYPARSE_PARAM;
#endif	/* ANSI-C/C++ */
#endif	/* ! YYPARSE_PARAM */

int
yyparse (YYPARSE_PARAM_ARG)
    YYPARSE_PARAM_DECL
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register const char *yys;

    if ((yys = getenv("YYDEBUG")))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate])) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#if defined(lint) || defined(__GNUC__)
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#if defined(lint) || defined(__GNUC__)
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 2:
#line 129 "jamgram.y"
{ parse_save( yyvsp[0].parse ); }
break;
case 3:
#line 140 "jamgram.y"
{ yyval.parse = pnull(); }
break;
case 4:
#line 142 "jamgram.y"
{ yyval.parse = yyvsp[0].parse; }
break;
case 5:
#line 146 "jamgram.y"
{ yyval.parse = yyvsp[0].parse; }
break;
case 6:
#line 148 "jamgram.y"
{ yyval.parse = prules( yyvsp[-1].parse, yyvsp[0].parse ); }
break;
case 7:
#line 150 "jamgram.y"
{ yyval.parse = plocal( yyvsp[-2].parse, pnull(), yyvsp[0].parse ); }
break;
case 8:
#line 152 "jamgram.y"
{ yyval.parse = plocal( yyvsp[-4].parse, yyvsp[-2].parse, yyvsp[0].parse ); }
break;
case 9:
#line 156 "jamgram.y"
{ yyval.parse = yyvsp[-1].parse; }
break;
case 10:
#line 158 "jamgram.y"
{ yyval.parse = pincl( yyvsp[-1].parse ); }
break;
case 11:
#line 160 "jamgram.y"
{ yyval.parse = prule( yyvsp[-2].string, yyvsp[-1].parse ); }
break;
case 12:
#line 162 "jamgram.y"
{ yyval.parse = pset( yyvsp[-3].parse, yyvsp[-1].parse, yyvsp[-2].number ); }
break;
case 13:
#line 164 "jamgram.y"
{ yyval.parse = pset1( yyvsp[-5].parse, yyvsp[-3].parse, yyvsp[-1].parse, yyvsp[-2].number ); }
break;
case 14:
#line 166 "jamgram.y"
{ yyval.parse = yyvsp[-1].parse; }
break;
case 15:
#line 168 "jamgram.y"
{ yyval.parse = pfor( yyvsp[-5].string, yyvsp[-3].parse, yyvsp[-1].parse ); }
break;
case 16:
#line 170 "jamgram.y"
{ yyval.parse = pswitch( yyvsp[-3].parse, yyvsp[-1].parse ); }
break;
case 17:
#line 172 "jamgram.y"
{ yyval.parse = pif( yyvsp[-3].parse, yyvsp[-1].parse, pnull() ); }
break;
case 18:
#line 174 "jamgram.y"
{ yyval.parse = pif( yyvsp[-5].parse, yyvsp[-3].parse, yyvsp[0].parse ); }
break;
case 19:
#line 176 "jamgram.y"
{ yyval.parse = pwhile( yyvsp[-3].parse, yyvsp[-1].parse ); }
break;
case 20:
#line 178 "jamgram.y"
{ yyval.parse = psetc( yyvsp[-1].string, yyvsp[0].parse ); }
break;
case 21:
#line 180 "jamgram.y"
{ yyval.parse = pon( yyvsp[-1].parse, yyvsp[0].parse ); }
break;
case 22:
#line 182 "jamgram.y"
{ yymode( SCAN_STRING ); }
break;
case 23:
#line 184 "jamgram.y"
{ yymode( SCAN_NORMAL ); }
break;
case 24:
#line 186 "jamgram.y"
{ yyval.parse = psete( yyvsp[-6].string,yyvsp[-5].parse,yyvsp[-2].string,yyvsp[-7].number ); }
break;
case 25:
#line 194 "jamgram.y"
{ yyval.number = ASSIGN_SET; }
break;
case 26:
#line 196 "jamgram.y"
{ yyval.number = ASSIGN_APPEND; }
break;
case 27:
#line 198 "jamgram.y"
{ yyval.number = ASSIGN_DEFAULT; }
break;
case 28:
#line 200 "jamgram.y"
{ yyval.number = ASSIGN_DEFAULT; }
break;
case 29:
#line 208 "jamgram.y"
{ yyval.parse = peval( EXPR_EXISTS, yyvsp[0].parse, pnull() ); }
break;
case 30:
#line 210 "jamgram.y"
{ yyval.parse = peval( EXPR_EQUALS, yyvsp[-2].parse, yyvsp[0].parse ); }
break;
case 31:
#line 212 "jamgram.y"
{ yyval.parse = peval( EXPR_NOTEQ, yyvsp[-2].parse, yyvsp[0].parse ); }
break;
case 32:
#line 214 "jamgram.y"
{ yyval.parse = peval( EXPR_LESS, yyvsp[-2].parse, yyvsp[0].parse ); }
break;
case 33:
#line 216 "jamgram.y"
{ yyval.parse = peval( EXPR_LESSEQ, yyvsp[-2].parse, yyvsp[0].parse ); }
break;
case 34:
#line 218 "jamgram.y"
{ yyval.parse = peval( EXPR_MORE, yyvsp[-2].parse, yyvsp[0].parse ); }
break;
case 35:
#line 220 "jamgram.y"
{ yyval.parse = peval( EXPR_MOREEQ, yyvsp[-2].parse, yyvsp[0].parse ); }
break;
case 36:
#line 222 "jamgram.y"
{ yyval.parse = peval( EXPR_AND, yyvsp[-2].parse, yyvsp[0].parse ); }
break;
case 37:
#line 224 "jamgram.y"
{ yyval.parse = peval( EXPR_AND, yyvsp[-2].parse, yyvsp[0].parse ); }
break;
case 38:
#line 226 "jamgram.y"
{ yyval.parse = peval( EXPR_OR, yyvsp[-2].parse, yyvsp[0].parse ); }
break;
case 39:
#line 228 "jamgram.y"
{ yyval.parse = peval( EXPR_OR, yyvsp[-2].parse, yyvsp[0].parse ); }
break;
case 40:
#line 230 "jamgram.y"
{ yyval.parse = peval( EXPR_IN, yyvsp[-2].parse, yyvsp[0].parse ); }
break;
case 41:
#line 232 "jamgram.y"
{ yyval.parse = peval( EXPR_NOT, yyvsp[0].parse, pnull() ); }
break;
case 42:
#line 234 "jamgram.y"
{ yyval.parse = yyvsp[-1].parse; }
break;
case 43:
#line 244 "jamgram.y"
{ yyval.parse = P0; }
break;
case 44:
#line 246 "jamgram.y"
{ yyval.parse = pnode( yyvsp[-1].parse, yyvsp[0].parse ); }
break;
case 45:
#line 250 "jamgram.y"
{ yyval.parse = psnode( yyvsp[-2].string, yyvsp[0].parse ); }
break;
case 46:
#line 259 "jamgram.y"
{ yyval.parse = pnode( P0, yyvsp[0].parse ); }
break;
case 47:
#line 261 "jamgram.y"
{ yyval.parse = pnode( yyvsp[0].parse, yyvsp[-2].parse ); }
break;
case 48:
#line 271 "jamgram.y"
{ yyval.parse = yyvsp[0].parse; yymode( SCAN_NORMAL ); }
break;
case 49:
#line 275 "jamgram.y"
{ yyval.parse = pnull(); yymode( SCAN_PUNCT ); }
break;
case 50:
#line 277 "jamgram.y"
{ yyval.parse = pappend( yyvsp[-1].parse, yyvsp[0].parse ); }
break;
case 51:
#line 281 "jamgram.y"
{ yyval.parse = plist( yyvsp[0].string ); }
break;
case 52:
#line 282 "jamgram.y"
{ yymode( SCAN_NORMAL ); }
break;
case 53:
#line 283 "jamgram.y"
{ yyval.parse = yyvsp[-1].parse; }
break;
case 54:
#line 292 "jamgram.y"
{ yyval.parse = prule( yyvsp[-1].string, yyvsp[0].parse ); }
break;
case 55:
#line 294 "jamgram.y"
{ yyval.parse = pon( yyvsp[-2].parse, prule( yyvsp[-1].string, yyvsp[0].parse ) ); }
break;
case 56:
#line 296 "jamgram.y"
{ yyval.parse = pon( yyvsp[-2].parse, yyvsp[0].parse ); }
break;
case 57:
#line 305 "jamgram.y"
{ yyval.number = 0; }
break;
case 58:
#line 307 "jamgram.y"
{ yyval.number = yyvsp[-1].number | yyvsp[0].number; }
break;
case 59:
#line 311 "jamgram.y"
{ yyval.number = EXEC_UPDATED; }
break;
case 60:
#line 313 "jamgram.y"
{ yyval.number = EXEC_TOGETHER; }
break;
case 61:
#line 315 "jamgram.y"
{ yyval.number = EXEC_IGNORE; }
break;
case 62:
#line 317 "jamgram.y"
{ yyval.number = EXEC_QUIETLY; }
break;
case 63:
#line 319 "jamgram.y"
{ yyval.number = EXEC_PIECEMEAL; }
break;
case 64:
#line 321 "jamgram.y"
{ yyval.number = EXEC_EXISTING; }
break;
case 65:
#line 330 "jamgram.y"
{ yyval.parse = pnull(); }
break;
case 66:
#line 332 "jamgram.y"
{ yyval.parse = yyvsp[0].parse; }
break;
#line 827 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
