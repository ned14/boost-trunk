/* Driver template for the LEMON parser generator.
** The author disclaims copyright to this source code.
*/
/* First off, code is include which follows the "include" declaration
** in the input file. */
#line 1 "grammar.y"

/*
Copyright 2007 Redshift Software, Inc.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
*/
#line 15 "grammar.c"
/* Next is all token values, in a form suitable for use by makeheaders.
** This section will be null unless lemon is run with the -m switch.
*/
/* 
** These constants (all generated automatically by the parser generator)
** specify the various kinds of tokens (terminals) that the parser
** understands. 
**
** Each symbol here is a terminal symbol in the grammar.
*/
/* Make sure the INTERFACE macro is defined.
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/* The next thing included is series of defines which control
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 terminals
**                       and nonterminals.  "int" is used otherwise.
**    YYNOCODE           is a number of type YYCODETYPE which corresponds
**                       to no legal terminal or nonterminal number.  This
**                       number is used to fill in empty slots of the hash 
**                       table.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       have fall-back values which should be used if the
**                       original value of the token will not parse.
**    YYACTIONTYPE       is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 rules and
**                       states combined.  "int" is used otherwise.
**    jamParseTOKENTYPE     is the data type used for minor tokens given 
**                       directly to the parser from the tokenizer.
**    YYMINORTYPE        is the data type used for all minor tokens.
**                       This is typically a union of many types, one of
**                       which is jamParseTOKENTYPE.  The entry in the union
**                       for base tokens is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    jamParseARG_SDECL     A static variable declaration for the %extra_argument
**    jamParseARG_PDECL     A parameter declaration for the %extra_argument
**    jamParseARG_STORE     Code to store %extra_argument into yypParser
**    jamParseARG_FETCH     Code to extract %extra_argument from yypParser
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
*/
#define YYCODETYPE unsigned char
#define YYNOCODE 69
#define YYACTIONTYPE unsigned char
#define jamParseTOKENTYPE void*
typedef union {
  jamParseTOKENTYPE yy0;
  int yy137;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define jamParseARG_SDECL
#define jamParseARG_PDECL
#define jamParseARG_FETCH
#define jamParseARG_STORE
#define YYNSTATE 153
#define YYNRULE 70
#define YYERRORSYMBOL 48
#define YYERRSYMDT yy137
#define YY_NO_ACTION      (YYNSTATE+YYNRULE+2)
#define YY_ACCEPT_ACTION  (YYNSTATE+YYNRULE+1)
#define YY_ERROR_ACTION   (YYNSTATE+YYNRULE)

/* Next are that tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N < YYNSTATE                  Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   YYNSTATE <= N < YYNSTATE+YYNRULE   Reduce by rule N-YYNSTATE.
**
**   N == YYNSTATE+YYNRULE              A syntax error has occurred.
**
**   N == YYNSTATE+YYNRULE+1            The parser accepts its input.
**
**   N == YYNSTATE+YYNRULE+2            No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as
**
**      yy_action[ yy_shift_ofst[S] + X ]
**
** If the index value yy_shift_ofst[S]+X is out of range or if the value
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X or if yy_shift_ofst[S]
** is equal to YY_SHIFT_USE_DFLT, it means that the action is not in the table
** and that yy_default[S] should be used instead.  
**
** The formula above is for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of
** YY_SHIFT_USE_DFLT.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
*/
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   168,   28,   30,   21,   24,   29,   22,   15,   27,   23,
 /*    10 */   120,  121,   12,  168,  128,   93,   41,  168,  168,  168,
 /*    20 */   168,  150,  168,  168,  168,  168,  168,  168,  168,  160,
 /*    30 */   168,  168,  168,  112,  224,   99,  106,  168,    9,  168,
 /*    40 */   150,  103,   56,   93,   41,   32,    8,  160,   69,   26,
 /*    50 */    47,   68,   58,   61,   17,   59,   35,   16,  157,   48,
 /*    60 */    52,   64,  142,  206,   25,  165,  160,   20,   31,  206,
 /*    70 */    33,   56,  146,  146,   13,    8,  157,   69,   26,   66,
 /*    80 */    68,   58,   61,   17,   59,   35,   16,  206,  206,   52,
 /*    90 */    64,   31,   31,   48,   56,  157,   97,   31,    8,  160,
 /*   100 */    69,   26,  107,   68,   58,   61,   17,   59,   35,   16,
 /*   110 */   133,   48,   52,   64,  141,  164,  146,   38,  160,  164,
 /*   120 */    31,  164,  164,   87,  164,  164,  164,  164,  164,  164,
 /*   130 */   164,   95,  164,  164,  164,   31,  146,   55,   56,   44,
 /*   140 */     1,  164,    8,  160,   69,   26,  153,   68,   58,   61,
 /*   150 */    17,   59,   35,   16,   45,   31,   52,   64,  121,   56,
 /*   160 */    37,   75,  110,    8,   31,   69,   26,   96,   68,   58,
 /*   170 */    61,   17,   59,   35,   16,  127,  148,   52,   64,   32,
 /*   180 */   163,   93,   41,   50,  163,   31,  163,  163,  129,  163,
 /*   190 */   163,  163,  163,  163,  163,  163,  151,  163,  163,  163,
 /*   200 */   100,   87,  150,   70,   46,    8,  163,   69,   26,   54,
 /*   210 */    68,   58,   61,   17,   59,   35,   16,   40,  165,   52,
 /*   220 */    64,   22,   15,   27,   23,  159,   11,   31,  165,   18,
 /*   230 */    19,   28,   30,   21,   24,   29,   22,   15,   27,   23,
 /*   240 */    14,  154,  146,  159,   63,    7,   53,   18,   19,   28,
 /*   250 */    30,   21,   24,   29,   22,   15,   27,   23,  156,  146,
 /*   260 */    57,   31,  159,    6,   42,   18,   19,   28,   30,   21,
 /*   270 */    24,   29,   22,   15,   27,   23,  156,   34,   31,   72,
 /*   280 */   147,  114,  115,  116,  117,  118,  119,   21,   24,   29,
 /*   290 */    22,   15,   27,   23,  145,  156,  146,  137,   84,   88,
 /*   300 */    86,    9,   84,   91,   86,    9,   93,   41,  122,  131,
 /*   310 */    93,   41,  146,   93,   41,   31,   84,  105,   86,    9,
 /*   320 */   121,   51,   49,   74,   93,   41,  136,  135,   89,  121,
 /*   330 */   111,   31,   77,   84,  102,   86,    9,   84,   98,   86,
 /*   340 */     9,   93,   41,  137,  121,   93,   41,   76,   84,   85,
 /*   350 */    86,    9,   84,  149,   86,    9,   93,   41,   43,   65,
 /*   360 */    93,   41,   84,  101,   86,    9,   67,  104,   39,   94,
 /*   370 */    93,   41,  136,  135,   89,  160,   83,   71,   36,    9,
 /*   380 */   139,  146,  140,  146,   93,   41,  146,  138,    3,    4,
 /*   390 */   161,  146,  146,  146,   48,  121,  146,   90,   73,  123,
 /*   400 */    31,  158,   31,  155,   48,   31,  121,  143,    5,   82,
 /*   410 */    31,   31,   31,  121,  121,   31,  126,  132,  134,  158,
 /*   420 */   125,  155,   62,  121,  121,    2,   80,  144,   48,  152,
 /*   430 */   109,   92,  124,  108,  121,   10,  121,  130,  158,   78,
 /*   440 */   155,  121,  162,  121,   79,  113,   81,  225,   60,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     0,    3,    4,    5,    6,    7,    8,    9,   10,   11,
 /*    10 */    53,   59,   59,   13,   62,   58,   59,   17,   18,   19,
 /*    20 */    20,   59,   22,   23,   24,   25,   26,   27,   28,    0,
 /*    30 */    30,   31,   32,   52,   49,   50,   55,   37,   53,   39,
 /*    40 */    59,   61,   13,   58,   59,   65,   17,   18,   19,   20,
 /*    50 */    59,   22,   23,   24,   25,   26,   27,   28,    0,   54,
 /*    60 */    31,   32,   57,   14,   12,   30,   37,   15,   39,   20,
 /*    70 */    17,   13,   20,   20,   54,   17,   18,   19,   20,   47,
 /*    80 */    22,   23,   24,   25,   26,   27,   28,   38,   39,   31,
 /*    90 */    32,   39,   39,   54,   13,   37,   57,   39,   17,   18,
 /*   100 */    19,   20,   64,   22,   23,   24,   25,   26,   27,   28,
 /*   110 */    14,   54,   31,   32,   57,   13,   20,   15,   37,   17,
 /*   120 */    39,   19,   20,   13,   22,   23,   24,   25,   26,   27,
 /*   130 */    28,   58,   30,   31,   32,   39,   20,   21,   13,   54,
 /*   140 */    14,   39,   17,   18,   19,   20,    0,   22,   23,   24,
 /*   150 */    25,   26,   27,   28,   54,   39,   31,   32,   59,   13,
 /*   160 */    59,   62,   20,   17,   39,   19,   20,   66,   22,   23,
 /*   170 */    24,   25,   26,   27,   28,   61,   53,   31,   32,   65,
 /*   180 */    13,   58,   59,   54,   17,   39,   19,   20,   18,   22,
 /*   190 */    23,   24,   25,   26,   27,   28,   18,   30,   31,   32,
 /*   200 */    18,   13,   59,   60,   54,   17,   39,   19,   20,   54,
 /*   210 */    22,   23,   24,   25,   26,   27,   28,   63,   20,   31,
 /*   220 */    32,    8,    9,   10,   11,    0,   29,   39,   30,    1,
 /*   230 */     2,    3,    4,    5,    6,    7,    8,    9,   10,   11,
 /*   240 */    54,    0,   20,   18,   22,   17,   54,    1,    2,    3,
 /*   250 */     4,    5,    6,    7,    8,    9,   10,   11,    0,   20,
 /*   260 */    20,   39,   37,   17,   54,    1,    2,    3,    4,    5,
 /*   270 */     6,    7,    8,    9,   10,   11,   18,   38,   39,   16,
 /*   280 */    16,   41,   42,   43,   44,   45,   46,    5,    6,    7,
 /*   290 */     8,    9,   10,   11,   40,   37,   20,    5,   50,   51,
 /*   300 */    52,   53,   50,   51,   52,   53,   58,   59,   53,   18,
 /*   310 */    58,   59,   20,   58,   59,   39,   50,   51,   52,   53,
 /*   320 */    59,   54,   54,   62,   58,   59,   34,   35,   36,   59,
 /*   330 */    20,   39,   62,   50,   51,   52,   53,   50,   51,   52,
 /*   340 */    53,   58,   59,    5,   59,   58,   59,   62,   50,   51,
 /*   350 */    52,   53,   50,   51,   52,   53,   58,   59,   54,   21,
 /*   360 */    58,   59,   50,   51,   52,   53,    5,   37,   20,   30,
 /*   370 */    58,   59,   34,   35,   36,   14,   50,   14,   59,   53,
 /*   380 */    14,   20,   14,   20,   58,   59,   20,   14,   17,   17,
 /*   390 */    14,   20,   20,   20,   54,   59,   20,   57,   62,   18,
 /*   400 */    39,    0,   39,    0,   54,   39,   59,   57,   17,   62,
 /*   410 */    39,   39,   39,   59,   59,   39,   62,   62,    5,   18,
 /*   420 */    18,   18,    7,   59,   59,   38,   62,   62,   54,   18,
 /*   430 */    33,   57,   18,   17,   59,   56,   59,   62,   37,   62,
 /*   440 */    37,   59,   14,   59,   62,   67,   62,   68,   60,
};
#define YY_SHIFT_USE_DFLT (-3)
#define YY_SHIFT_MAX 112
static const short yy_shift_ofst[] = {
 /*     0 */   146,   29,   81,  125,  125,  125,  125,  125,  125,   58,
 /*    10 */   188,  188,  188,  361,  292,   52,   52,   52,   52,   52,
 /*    20 */    52,   52,   52,   52,   52,   52,   49,   52,   52,   52,
 /*    30 */    52,  116,  330,  330,   -3,   -3,   -3,   -3,   -3,  102,
 /*    40 */   240,  338,  376,  373,  372,  366,  371,  222,  239,  363,
 /*    50 */    53,   96,  276,  276,  276,  276,   35,   32,  110,   -3,
 /*    60 */    -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,
 /*    70 */    -3,    0,  167,  264,  246,  228,   -2,   -2,  282,  282,
 /*    80 */   213,  213,  213,  401,  258,  225,  403,  198,  402,  413,
 /*    90 */   391,  381,  368,  339,  348,  310,  254,  263,  291,  241,
 /*   100 */   197,  182,  178,  170,  142,  414,  126,  416,  397,  411,
 /*   110 */   387,  415,  428,
};
#define YY_REDUCE_USE_DFLT (-49)
#define YY_REDUCE_MAX 70
static const short yy_reduce_ofst[] = {
 /*     0 */   -15,  298,  302,  287,  248,  266,  312,  252,  283,  326,
 /*    10 */   255,  123,  -43,  -19,  143,  -48,   99,  261,  270,  285,
 /*    20 */   336,  347,  354,  355,  364,  365,  374,  375,  377,  384,
 /*    30 */   382,  101,  114,  -20,  350,  340,   57,    5,   39,  379,
 /*    40 */   378,  388,  -38,  -38,  -38,  -38,  -38,  319,  -38,  -38,
 /*    50 */   -38,  -38,  -47,  -38,  -38,   -9,   20,   38,   73,   85,
 /*    60 */   100,  129,  150,  155,  154,  186,  192,  210,  267,  268,
 /*    70 */   304,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   166,  166,  166,  166,  166,  166,  166,  166,  166,  166,
 /*    10 */   166,  166,  166,  223,  223,  223,  223,  223,  223,  223,
 /*    20 */   223,  223,  223,  223,  223,  223,  208,  223,  223,  223,
 /*    30 */   223,  223,  201,  201,  206,  206,  206,  206,  206,  223,
 /*    40 */   223,  223,  223,  223,  223,  223,  223,  223,  204,  223,
 /*    50 */   223,  223,  223,  222,  212,  223,  206,  221,  166,  206,
 /*    60 */   206,  206,  206,  206,  213,  206,  206,  206,  206,  206,
 /*    70 */   206,  223,  223,  223,  223,  223,  196,  197,  195,  194,
 /*    80 */   189,  198,  188,  223,  223,  223,  223,  223,  223,  223,
 /*    90 */   223,  223,  223,  223,  223,  223,  223,  223,  223,  223,
 /*   100 */   175,  223,  223,  223,  223,  223,  223,  223,  223,  223,
 /*   110 */   223,  223,  223,  214,  215,  216,  217,  218,  219,  220,
 /*   120 */   181,  187,  180,  178,  177,  176,  190,  202,  191,  174,
 /*   130 */   192,  173,  193,  172,  186,  185,  184,  183,  171,  170,
 /*   140 */   169,  211,  210,  205,  199,  209,  208,  200,  179,  203,
 /*   150 */   207,  167,  182,
};
#define YY_SZ_ACTTAB (int)(sizeof(yy_action)/sizeof(yy_action[0]))

/* The next table maps tokens into fallback tokens.  If a construct
** like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammer, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
*/
struct yyStackEntry {
  int stateno;       /* The state-number */
  int major;         /* The major token value.  This is the code
                     ** number for the token at this stack level */
  YYMINORTYPE minor; /* The user-supplied minor token value.  This
                     ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  int yyidx;                    /* Index of top element in stack */
  int yyerrcnt;                 /* Shifts left before out of the error */
  jamParseARG_SDECL                /* A place to hold %extra_argument */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void jamParseTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  "$",             "OR_OR",         "OR",            "AND_AND",     
  "AND",           "EQ",            "NEQ",           "IN",          
  "LT",            "LE",            "GT",            "GE",          
  "NOT",           "LOCAL",         "EOM",           "LPAREN",      
  "RPAREN",        "LBRACE",        "RBRACE",        "INCLUDE",     
  "ARG",           "ON",            "RETURN",        "FOR",         
  "SWITCH",        "IF",            "MODULE",        "CLASS",       
  "WHILE",         "ELSE",          "RULE",          "OM",          
  "ACTIONS",       "STRING",        "PLUS_EQ",       "OPT_EQ",      
  "DEFAULT",       "CASE",          "COLON",         "LBRACKET",    
  "RBRACKET",      "UPDATED",       "TOGETHER",      "IGNORE",      
  "QUITELY",       "PIECEMEAL",     "EXISTING",      "BIND",        
  "error",         "run",           "rules",         "block",       
  "null",          "rule",          "list",          "assign_list_opt",
  "arglist_opt",   "lol",           "local_opt",     "arg",         
  "assign",        "cases",         "expr",          "eflags",      
  "bindlist",      "case",          "func",          "eflag",       
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "run ::=",
 /*   1 */ "run ::= rules",
 /*   2 */ "block ::= null",
 /*   3 */ "block ::= rules",
 /*   4 */ "rules ::= rule",
 /*   5 */ "rules ::= rule rules",
 /*   6 */ "rules ::= LOCAL list assign_list_opt EOM block",
 /*   7 */ "null ::=",
 /*   8 */ "assign_list_opt ::= EQ list",
 /*   9 */ "assign_list_opt ::= null",
 /*  10 */ "arglist_opt ::= LPAREN lol RPAREN",
 /*  11 */ "arglist_opt ::=",
 /*  12 */ "local_opt ::= LOCAL",
 /*  13 */ "local_opt ::=",
 /*  14 */ "rule ::= LBRACE block RBRACE",
 /*  15 */ "rule ::= INCLUDE list EOM",
 /*  16 */ "rule ::= ARG lol EOM",
 /*  17 */ "rule ::= arg assign list EOM",
 /*  18 */ "rule ::= arg ON list assign list EOM",
 /*  19 */ "rule ::= RETURN list EOM",
 /*  20 */ "rule ::= FOR local_opt ARG IN list LBRACE block RBRACE",
 /*  21 */ "rule ::= SWITCH list LBRACE cases RBRACE",
 /*  22 */ "rule ::= IF expr LBRACE block RBRACE",
 /*  23 */ "rule ::= MODULE list LBRACE block RBRACE",
 /*  24 */ "rule ::= CLASS lol LBRACE block RBRACE",
 /*  25 */ "rule ::= WHILE expr LBRACE block RBRACE",
 /*  26 */ "rule ::= IF expr LBRACE block RBRACE ELSE rule",
 /*  27 */ "rule ::= local_opt RULE ARG arglist_opt rule",
 /*  28 */ "rule ::= OM arg rule",
 /*  29 */ "rule ::= ACTIONS eflags ARG bindlist LBRACE STRING RBRACE",
 /*  30 */ "assign ::= EQ",
 /*  31 */ "assign ::= PLUS_EQ",
 /*  32 */ "assign ::= OPT_EQ",
 /*  33 */ "assign ::= DEFAULT EQ",
 /*  34 */ "expr ::= arg",
 /*  35 */ "expr ::= expr EQ expr",
 /*  36 */ "expr ::= expr NEQ expr",
 /*  37 */ "expr ::= expr LT expr",
 /*  38 */ "expr ::= expr LE expr",
 /*  39 */ "expr ::= expr GT expr",
 /*  40 */ "expr ::= expr GE expr",
 /*  41 */ "expr ::= expr AND expr",
 /*  42 */ "expr ::= expr AND_AND expr",
 /*  43 */ "expr ::= expr OR expr",
 /*  44 */ "expr ::= expr OR_OR expr",
 /*  45 */ "expr ::= expr IN expr",
 /*  46 */ "expr ::= NOT expr",
 /*  47 */ "expr ::= LPAREN expr RPAREN",
 /*  48 */ "cases ::=",
 /*  49 */ "cases ::= case cases",
 /*  50 */ "case ::= CASE ARG COLON block",
 /*  51 */ "lol ::= list",
 /*  52 */ "lol ::= list COLON lol",
 /*  53 */ "list ::=",
 /*  54 */ "list ::= list arg",
 /*  55 */ "arg ::= ARG",
 /*  56 */ "arg ::= LBRACKET func RBRACKET",
 /*  57 */ "func ::= arg lol",
 /*  58 */ "func ::= ON arg arg lol",
 /*  59 */ "func ::= ON arg RETURN list",
 /*  60 */ "eflags ::=",
 /*  61 */ "eflags ::= eflags eflag",
 /*  62 */ "eflag ::= UPDATED",
 /*  63 */ "eflag ::= TOGETHER",
 /*  64 */ "eflag ::= IGNORE",
 /*  65 */ "eflag ::= QUITELY",
 /*  66 */ "eflag ::= PIECEMEAL",
 /*  67 */ "eflag ::= EXISTING",
 /*  68 */ "bindlist ::=",
 /*  69 */ "bindlist ::= BIND list",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.
*/
static void yyGrowStack(yyParser *p){
  int newSize;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  if( pNew ){
    p->yystack = pNew;
    p->yystksz = newSize;
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows to %d entries!\n",
              yyTracePrompt, p->yystksz);
    }
#endif
  }
}
#endif

/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to jamParse and jamParseFree.
*/
void *jamParseAlloc(void *(*mallocProc)(size_t)){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (size_t)sizeof(yyParser) );
  if( pParser ){
    pParser->yyidx = -1;
#if YYSTACKDEPTH<=0
    yyGrowStack(pParser);
#endif
  }
  return pParser;
}

/* The following function deletes the value associated with a
** symbol.  The symbol can be either a terminal or nonterminal.
** "yymajor" is the symbol code, and "yypminor" is a pointer to
** the value.
*/
static void yy_destructor(YYCODETYPE yymajor, YYMINORTYPE *yypminor){
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are not used
    ** inside the C code.
    */
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
**
** Return the major token number for the symbol popped.
*/
static int yy_pop_parser_stack(yyParser *pParser){
  YYCODETYPE yymajor;
  yyStackEntry *yytos = &pParser->yystack[pParser->yyidx];

  if( pParser->yyidx<0 ) return 0;
#ifndef NDEBUG
  if( yyTraceFILE && pParser->yyidx>=0 ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yymajor = yytos->major;
  yy_destructor( yymajor, &yytos->minor);
  pParser->yyidx--;
  return yymajor;
}

/* 
** Deallocate and destroy a parser.  Destructors are all called for
** all stack elements before shutting the parser down.
**
** Inputs:
** <ul>
** <li>  A pointer to the parser.  This should be a pointer
**       obtained from jamParseAlloc.
** <li>  A pointer to a function used to reclaim memory obtained
**       from malloc.
** </ul>
*/
void jamParseFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
  yyParser *pParser = (yyParser*)p;
  if( pParser==0 ) return;
  while( pParser->yyidx>=0 ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  free(pParser->yystack);
#endif
  (*freeProc)((void*)pParser);
}

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
  int stateno = pParser->yystack[pParser->yyidx].stateno;
 
  if( stateno>YY_SHIFT_MAX || (i = yy_shift_ofst[stateno])==YY_SHIFT_USE_DFLT ){
    return yy_default[stateno];
  }
  if( iLookAhead==YYNOCODE ){
    return YY_NO_ACTION;
  }
  i += iLookAhead;
  if( i<0 || i>=YY_SZ_ACTTAB || yy_lookahead[i]!=iLookAhead ){
    if( iLookAhead>0 ){
#ifdef YYFALLBACK
      int iFallback;            /* Fallback token */
      if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
             && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        return yy_find_shift_action(pParser, iFallback);
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        if( j>=0 && j<YY_SZ_ACTTAB && yy_lookahead[j]==YYWILDCARD ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
    }
    return yy_default[stateno];
  }else{
    return yy_action[i];
  }
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_reduce_action(
  int stateno,              /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
  /* int stateno = pParser->yystack[pParser->yyidx].stateno; */
 
  if( stateno>YY_REDUCE_MAX ||
      (i = yy_reduce_ofst[stateno])==YY_REDUCE_USE_DFLT ){
    return yy_default[stateno];
  }
  if( iLookAhead==YYNOCODE ){
    return YY_NO_ACTION;
  }
  i += iLookAhead;
  if( i<0 || i>=YY_SZ_ACTTAB || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }else{
    return yy_action[i];
  }
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser, YYMINORTYPE *yypMinor){
   jamParseARG_FETCH;
   yypParser->yyidx--;
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
   jamParseARG_STORE; /* Suppress warning about unused %extra_argument var */
}

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  YYMINORTYPE *yypMinor         /* Pointer ot the minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yyidx++;
#if YYSTACKDEPTH>0 
  if( yypParser->yyidx>=YYSTACKDEPTH ){
    yyStackOverflow(yypParser, yypMinor);
    return;
  }
#else
  if( yypParser->yyidx>=yypParser->yystksz ){
    yyGrowStack(yypParser);
    if( yypParser->yyidx>=yypParser->yystksz ){
      yyStackOverflow(yypParser, yypMinor);
      return;
    }
  }
#endif
  yytos = &yypParser->yystack[yypParser->yyidx];
  yytos->stateno = yyNewState;
  yytos->major = yyMajor;
  yytos->minor = *yypMinor;
#ifndef NDEBUG
  if( yyTraceFILE && yypParser->yyidx>0 ){
    int i;
    fprintf(yyTraceFILE,"%sShift %d\n",yyTracePrompt,yyNewState);
    fprintf(yyTraceFILE,"%sStack:",yyTracePrompt);
    for(i=1; i<=yypParser->yyidx; i++)
      fprintf(yyTraceFILE," %s",yyTokenName[yypParser->yystack[i].major]);
    fprintf(yyTraceFILE,"\n");
  }
#endif
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 49, 0 },
  { 49, 1 },
  { 51, 1 },
  { 51, 1 },
  { 50, 1 },
  { 50, 2 },
  { 50, 5 },
  { 52, 0 },
  { 55, 2 },
  { 55, 1 },
  { 56, 3 },
  { 56, 0 },
  { 58, 1 },
  { 58, 0 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 53, 4 },
  { 53, 6 },
  { 53, 3 },
  { 53, 8 },
  { 53, 5 },
  { 53, 5 },
  { 53, 5 },
  { 53, 5 },
  { 53, 5 },
  { 53, 7 },
  { 53, 5 },
  { 53, 3 },
  { 53, 7 },
  { 60, 1 },
  { 60, 1 },
  { 60, 1 },
  { 60, 2 },
  { 62, 1 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 2 },
  { 62, 3 },
  { 61, 0 },
  { 61, 2 },
  { 65, 4 },
  { 57, 1 },
  { 57, 3 },
  { 54, 0 },
  { 54, 2 },
  { 59, 1 },
  { 59, 3 },
  { 66, 2 },
  { 66, 4 },
  { 66, 4 },
  { 63, 0 },
  { 63, 2 },
  { 67, 1 },
  { 67, 1 },
  { 67, 1 },
  { 67, 1 },
  { 67, 1 },
  { 67, 1 },
  { 64, 0 },
  { 64, 2 },
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  int yyruleno                 /* Number of the rule by which to reduce */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  YYMINORTYPE yygotominor;        /* The LHS of the rule reduced */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  jamParseARG_FETCH;
  yymsp = &yypParser->yystack[yypParser->yyidx];
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno>=0 
        && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    fprintf(yyTraceFILE, "%sReduce [%s].\n", yyTracePrompt,
      yyRuleName[yyruleno]);
  }
#endif /* NDEBUG */

  /* Silence complaints from purify about yygotominor being uninitialized
  ** in some cases when it is copied into the stack after the following
  ** switch.  yygotominor is uninitialized when a rule reduces that does
  ** not set the value of its left-hand side nonterminal.  Leaving the
  ** value of the nonterminal uninitialized is utterly harmless as long
  ** as the value is never used.  So really the only thing this code
  ** accomplishes is to quieten purify.  
  **
  ** 2007-01-16:  The wireshark project (www.wireshark.org) reports that
  ** without this code, their parser segfaults.  I'm not sure what there
  ** parser is doing to make this happen.  This is the second bug report
  ** from wireshark this week.  Clearly they are stressing Lemon in ways
  ** that it has not been previously stressed...  (SQLite ticket #2172)
  */
  memset(&yygotominor, 0, sizeof(yygotominor));


  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
      case 7:
      case 8:
      case 9:
      case 10:
      case 11:
      case 12:
      case 13:
      case 14:
      case 15:
      case 16:
      case 17:
      case 18:
      case 19:
      case 20:
      case 21:
      case 22:
      case 23:
      case 24:
      case 25:
      case 26:
      case 27:
      case 28:
      case 29:
      case 30:
      case 31:
      case 32:
      case 33:
      case 34:
      case 35:
      case 36:
      case 37:
      case 38:
      case 39:
      case 40:
      case 41:
      case 42:
      case 43:
      case 44:
      case 45:
      case 46:
      case 47:
      case 48:
      case 49:
      case 50:
      case 51:
      case 52:
      case 53:
      case 54:
      case 55:
      case 56:
      case 57:
      case 58:
      case 59:
      case 60:
      case 61:
      case 62:
      case 63:
      case 64:
      case 65:
      case 66:
      case 67:
      case 68:
      case 69:
#line 21 "grammar.y"
{
}
#line 930 "grammar.c"
        break;
  };
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yypParser->yyidx -= yysize;
  yyact = yy_find_reduce_action(yymsp[-yysize].stateno,yygoto);
  if( yyact < YYNSTATE ){
#ifdef NDEBUG
    /* If we are not debugging and the reduce action popped at least
    ** one element off the stack, then we can push the new element back
    ** onto the stack here, and skip the stack overflow test in yy_shift().
    ** That gives a significant speed improvement. */
    if( yysize ){
      yypParser->yyidx++;
      yymsp -= yysize-1;
      yymsp->stateno = yyact;
      yymsp->major = yygoto;
      yymsp->minor = yygotominor;
    }else
#endif
    {
      yy_shift(yypParser,yyact,yygoto,&yygotominor);
    }
  }else if( yyact == YYNSTATE + YYNRULE + 1 ){
    yy_accept(yypParser);
  }
}

/*
** The following code executes when the parse fails
*/
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  jamParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
  jamParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  YYMINORTYPE yyminor            /* The minor type of the error token */
){
  jamParseARG_FETCH;
#define TOKEN (yyminor.yy0)
  jamParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  jamParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
  jamParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "jamParseAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void jamParse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  jamParseTOKENTYPE yyminor       /* The value for the token */
  jamParseARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  int yyact;            /* The parser action. */
  int yyendofinput;     /* True if we are at the end of input */
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
  yyParser *yypParser;  /* The parser */

  /* (re)initialize the parser, if necessary */
  yypParser = (yyParser*)yyp;
  if( yypParser->yyidx<0 ){
#if YYSTACKDEPTH<=0
    if( yypParser->yystksz <=0 ){
      memset(&yyminorunion, 0, sizeof(yyminorunion));
      yyStackOverflow(yypParser, &yyminorunion);
      return;
    }
#endif
    yypParser->yyidx = 0;
    yypParser->yyerrcnt = -1;
    yypParser->yystack[0].stateno = 0;
    yypParser->yystack[0].major = 0;
  }
  yyminorunion.yy0 = yyminor;
  yyendofinput = (yymajor==0);
  jamParseARG_STORE;

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput %s\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,yymajor);
    if( yyact<YYNSTATE ){
      yy_shift(yypParser,yyact,yymajor,&yyminorunion);
      yypParser->yyerrcnt--;
      if( yyendofinput && yypParser->yyidx>=0 ){
        yymajor = 0;
      }else{
        yymajor = YYNOCODE;
      }
    }else if( yyact < YYNSTATE + YYNRULE ){
      yy_reduce(yypParser,yyact-YYNSTATE);
    }else if( yyact == YY_ERROR_ACTION ){
      int yymx;
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yymx = yypParser->yystack[yypParser->yyidx].major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yymajor,&yyminorunion);
        yymajor = YYNOCODE;
      }else{
         while(
          yypParser->yyidx >= 0 &&
          yymx != YYERRORSYMBOL &&
          (yyact = yy_find_reduce_action(
                        yypParser->yystack[yypParser->yyidx].stateno,
                        YYERRORSYMBOL)) >= YYNSTATE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yyidx < 0 || yymajor==0 ){
          yy_destructor(yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          YYMINORTYPE u2;
          u2.YYERRSYMDT = 0;
          yy_shift(yypParser,yyact,YYERRORSYMBOL,&u2);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
      }
      yymajor = YYNOCODE;
#endif
    }else{
      yy_accept(yypParser);
      yymajor = YYNOCODE;
    }
  }while( yymajor!=YYNOCODE && yypParser->yyidx>=0 );
  return;
}
