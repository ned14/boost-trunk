//=======================================================================
// Copyright 2001 University of Notre Dame.
// Author: Lie-Quan Lee
//
// This file is part of the Boost Graph Library
//
// You should have received a copy of the License Agreement for the
// Boost Graph Library along with the software; see the file LICENSE.
// If not, contact Office of Research, University of Notre Dame, Notre
// Dame, IN 46556.
//
// Permission to modify the code and to distribute modified code is
// granted, provided the text of this NOTICE is retained, a notice that
// the code was modified is included with the above COPYRIGHT NOTICE and
// with the COPYRIGHT NOTICE in the LICENSE file, and that the LICENSE
// file is distributed with the modified code.
//
// LICENSOR MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESS OR IMPLIED.
// By way of example, but not limitation, Licensor MAKES NO
// REPRESENTATIONS OR WARRANTIES OF MERCHANTABILITY OR FITNESS FOR ANY
// PARTICULAR PURPOSE OR THAT THE USE OF THE LICENSED SOFTWARE COMPONENTS
// OR DOCUMENTATION WILL NOT INFRINGE ANY PATENTS, COPYRIGHTS, TRADEMARKS
// OR OTHER RIGHTS.
//=======================================================================

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* If NAME_PREFIX is specified substitute the variables and functions
   names.  */
#define yyparse bgl_undir_parse
#define yylex   bgl_undir_lex
#define yyerror bgl_undir_error
#define yylval  bgl_undir_lval
#define yychar  bgl_undir_char
#define yydebug bgl_undir_debug
#define yynerrs bgl_undir_nerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     GRAPH_T = 258,
     NODE_T = 259,
     EDGE_T = 260,
     DIGRAPH_T = 261,
     EDGEOP_T = 262,
     SUBGRAPH_T = 263,
     ID_T = 264
   };
#endif
#define GRAPH_T 258
#define NODE_T 259
#define EDGE_T 260
#define DIGRAPH_T 261
#define EDGEOP_T 262
#define SUBGRAPH_T 263
#define ID_T 264




/* Copy the first part of user declarations.  */
#line 1 "graphviz_parser.yy"


#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

#include <boost/config.hpp>
#include <boost/graph/graphviz.hpp>

#if defined BOOST_NO_STRINGSTREAM 
  //#include <strstream> //We cannot use it since there is a bug in strstream  
#include <stdlib.h>
#else
#include <sstream>
#endif

#ifndef GRAPHVIZ_DIRECTED
#error Need to define the GRAPHVIZ_DIRECTED macro to either 0 or 1
#endif 

#if GRAPHVIZ_DIRECTED == 0
#define GRAPHVIZ_GRAPH boost::GraphvizGraph
#define yyrestart bgl_undir_restart
#else
#define GRAPHVIZ_GRAPH boost::GraphvizDigraph
#define yyrestart bgl_dir_restart
#endif

#define YYPARSE_PARAM g

#include "yystype.h"

  extern void yyerror(char* str);
  extern void yyrestart(FILE* str);
  extern int yylex(YYSTYPE* lvalp);

  enum AttrState {GRAPH_GRAPH_A, GRAPH_NODE_A, GRAPH_EDGE_A, NODE_A, EDGE_A};

  using boost::GraphvizAttrList;

  namespace graphviz {

    typedef boost::graph_traits<GRAPHVIZ_GRAPH>::vertex_descriptor Vertex;
    typedef boost::graph_traits<GRAPHVIZ_GRAPH>::edge_descriptor   Edge;
    typedef GRAPHVIZ_GRAPH Subgraph;

    static Vertex current_vertex;
    static Edge   current_edge;
    static Subgraph* current_graph = NULL;
    static Subgraph* previous_graph = NULL;

    static std::vector< std::pair<void*, bool>* > vlist;//store a list of rhs 

    static std::map<std::string,std::string> attributes;//store attributes temporarily
    static AttrState attribute_state;

    static std::map<std::string, Subgraph*> subgraphs;  //store the names of subgraphs
    static std::map<std::string, Vertex> nodes;         //store the names of nodes

    typedef std::map<std::string, Subgraph*>::iterator It; 
    typedef std::map<std::string, Vertex>::iterator Iter; 

    static const std::string& get_graph_name(const Subgraph& g) {
      const boost::graph_property<Subgraph, boost::graph_name_t>::type&
        name = boost::get_property(g, boost::graph_name);
      return name; 
    }

    static std::pair<Iter, bool> lookup(const std::string& name) {
      //lookup in the top level
      Iter it = nodes.find(name);
      bool found = (it != nodes.end() );
      return std::make_pair(it, found);
    }
    
    static Vertex add_name(const std::string& name, GRAPHVIZ_GRAPH& g) {
      Vertex v = boost::add_vertex(*current_graph);
      v = current_graph->local_to_global(v);

      //set the label of vertex, it could be overwritten later.
      boost::property_map<GRAPHVIZ_GRAPH, boost::vertex_attribute_t>::type
        va = boost::get(boost::vertex_attribute, g); 
      va[v]["label"] = name; 
      
      //add v into the map so next time we will find it.
      nodes[name] = v; 
      return v;
    }

    static std::pair<It, bool> lookup_subgraph(const std::string& name) {
      It it = subgraphs.find(name);
      bool found = (it != subgraphs.end() );
      return std::make_pair(it, found);
    }
    
    static Subgraph* create_subgraph(const std::string& name) { 

      Subgraph* new_subgraph = &(current_graph->create_subgraph()); 

      subgraphs[name]        = new_subgraph;
      return new_subgraph;
    }

    
    static void set_attribute(GraphvizAttrList& p,
                              const GraphvizAttrList& attr) {
      GraphvizAttrList::const_iterator i, end;
      for ( i=attr.begin(), end=attr.end(); i!=end; ++i)
        p[i->first]=i->second;
    }
  
    static void set_attribute(Subgraph& g,
                              AttrState s, bool clear_attribute = true) {
      typedef Subgraph Graph;
      switch ( s ) {
      case GRAPH_GRAPH_A: 
        {
          boost::graph_property<Graph, boost::graph_graph_attribute_t>::type&
            gga = boost::get_property(g, boost::graph_graph_attribute);
          set_attribute(gga, attributes); 
        }
        break;
      case GRAPH_NODE_A: 
        {
          boost::graph_property<Graph, boost::graph_vertex_attribute_t>::type&
            gna = boost::get_property(g, boost::graph_vertex_attribute);
          set_attribute(gna, attributes); 
        }
        break;
      case GRAPH_EDGE_A: 
        {
          boost::graph_property<Graph, boost::graph_edge_attribute_t>::type&
            gea = boost::get_property(g, boost::graph_edge_attribute);
          set_attribute(gea, attributes); 
        }
        break;
      case NODE_A:
        {
          boost::property_map<Graph, boost::vertex_attribute_t>::type
            va = boost::get(boost::vertex_attribute, g);    //va[v]
          set_attribute(va[current_vertex], attributes);
        }
        break;
      case EDGE_A: 
        {
          boost::property_map<Graph, boost::edge_attribute_t>::type
            ea = boost::get(boost::edge_attribute, g);      //ea[e]
          set_attribute(ea[current_edge], attributes); 
        }
        break;
      }
      if ( clear_attribute )
        attributes.clear();
    }


    static void add_edges(const Vertex& u,
                          const Vertex& v, GRAPHVIZ_GRAPH& g) {
      graphviz::current_edge = boost::add_edge(u, v, g).first; 
      graphviz::set_attribute(g, EDGE_A, false);
    }
    
    static void add_edges(Subgraph* G1, Subgraph* G2,
                          GRAPHVIZ_GRAPH& g) {
      boost::graph_traits<Subgraph>::vertex_iterator i, j, m, n;
      for ( boost::tie(i, j) = boost::vertices(*G1); i != j; ++i) {
        for ( boost::tie(m, n) = boost::vertices(*G2); m != n; ++m) {
          graphviz::add_edges(G1->local_to_global(*i),
                              G2->local_to_global(*m), g);
        }
      }
    }

    static void add_edges(Subgraph* G, const Vertex& v, GRAPHVIZ_GRAPH& g) {
      boost::graph_traits<Subgraph>::vertex_iterator i, j;
      for ( boost::tie(i, j) = boost::vertices(*G); i != j; ++i) {
        graphviz::add_edges(G->local_to_global(*i), v, g);
      }
    }

    static void add_edges(const Vertex& u, Subgraph* G, GRAPHVIZ_GRAPH& g) {
      boost::graph_traits<Subgraph>::vertex_iterator i, j;
      for ( boost::tie(i, j) = boost::vertices(*G); i != j; ++i) {
        graphviz::add_edges(u, G->local_to_global(*i), g);
      }
    }

    static std::string random_string() {
      static int i=0;
#if defined BOOST_NO_STRINGSTREAM
      //std::strstream out;
      char buf[256];
      sprintf(buf, "default%i\0", i);
      ++i;
      return std::string(buf);
#else
      std::stringstream out;
      out << "default" << i;
      ++i;
      return out.str();
#endif
    }


    static void set_graph_name(const std::string& name) {
      boost::graph_property<Subgraph, boost::graph_name_t>::type&
        gea = boost::get_property(*current_graph, boost::graph_name);
      gea = name;
    }

  } //namespace detail {



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 354 "graphviz_graph_parser.cpp"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

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
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
         || (YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))                         \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)              \
      do                                        \
        {                                       \
          register YYSIZE_T yyi;                \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (To)[yyi] = (From)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)                                        \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack, Stack, yysize);                          \
        Stack = &yyptr->Stack;                                          \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   58

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  18
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  28
/* YYNRULES -- Number of rules. */
#define YYNRULES  47
/* YYNRULES -- Number of states. */
#define YYNSTATES  66

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   264

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    16,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    17,    12,
       2,    15,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    13,     2,    14,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    10,     2,    11,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     6,    10,    13,    15,    17,    19,    20,
      23,    25,    27,    28,    31,    34,    39,    41,    43,    45,
      47,    51,    55,    57,    59,    60,    62,    64,    66,    68,
      70,    73,    77,    78,    80,    82,    86,    90,    93,    95,
      98,   100,   102,   105,   106,   109,   112,   114
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      19,     0,    -1,    21,    20,    -1,    10,    24,    11,    -1,
      22,    23,    -1,     3,    -1,     6,    -1,     9,    -1,    -1,
      24,    26,    -1,    26,    -1,    12,    -1,    -1,    27,    25,
      -1,    32,    25,    -1,    28,    13,    29,    14,    -1,     3,
      -1,     4,    -1,     5,    -1,    30,    -1,    29,    31,    30,
      -1,     9,    15,     9,    -1,    12,    -1,    16,    -1,    -1,
      34,    -1,    38,    -1,    33,    -1,    42,    -1,    30,    -1,
      36,    35,    -1,    13,    29,    14,    -1,    -1,     9,    -1,
      37,    -1,     9,    17,     9,    -1,    41,    40,    35,    -1,
       7,    41,    -1,    39,    -1,    40,    39,    -1,    36,    -1,
      42,    -1,    44,    45,    -1,    -1,    43,    20,    -1,     8,
       9,    -1,    20,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   254,   254,   257,   260,   274,   274,   277,   277,   280,
     280,   283,   283,   286,   287,   290,   297,   298,   299,   302,
     302,   305,   315,   315,   315,   318,   318,   318,   318,   321,
     329,   340,   340,   343,   358,   361,   380,   425,   429,   429,
     432,   441,   452,   460,   460,   474,   495,   495
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "GRAPH_T", "NODE_T", "EDGE_T", "DIGRAPH_T", 
  "EDGEOP_T", "SUBGRAPH_T", "ID_T", "'{'", "'}'", "';'", "'['", "']'", 
  "'='", "','", "':'", "$accept", "graph", "graph_body", "graph_header", 
  "graph_type", "graph_name", "stmt_list", "semicolon", "stmt", 
  "attr_stmt", "attr_header", "attr_list", "attr", "attr_separator", 
  "compound_stmt", "graph_attr", "node_stmt", "opt_attr", "node_id", 
  "node_port", "edge_stmt", "edge_rhs_one", "edge_rhs", "edge_endpoint", 
  "subgraph", "@1", "subgraph_header", "opt_graph_body", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     123,   125,    59,    91,    93,    61,    44,    58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    18,    19,    20,    21,    22,    22,    23,    23,    24,
      24,    25,    25,    26,    26,    27,    28,    28,    28,    29,
      29,    30,    31,    31,    31,    32,    32,    32,    32,    33,
      34,    35,    35,    36,    36,    37,    38,    39,    40,    40,
      41,    41,    42,    43,    42,    44,    45,    45
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     2,     3,     2,     1,     1,     1,     0,     2,
       1,     1,     0,     2,     2,     4,     1,     1,     1,     1,
       3,     3,     1,     1,     0,     1,     1,     1,     1,     1,
       2,     3,     0,     1,     1,     3,     3,     2,     1,     2,
       1,     1,     2,     0,     2,     2,     1,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     5,     6,     0,     0,     8,     1,    43,     2,     7,
       4,    16,    17,    18,     0,    33,    43,    10,    12,     0,
      29,    12,    27,    25,    32,    34,    26,     0,    28,     0,
      47,    45,     0,     0,     3,     9,    11,    13,     0,    14,
       0,    30,    43,    38,    32,    44,    46,    42,    21,    35,
       0,    24,    19,    24,    33,    40,    37,    41,    36,    39,
      22,    15,    23,     0,    31,    20
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,     3,     8,     4,     5,    10,    16,    37,    17,    18,
      19,    51,    20,    63,    21,    22,    23,    41,    24,    25,
      26,    43,    44,    27,    28,    29,    30,    47
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -39
static const yysigned_char yypact[] =
{
      23,   -39,   -39,     6,    17,    22,   -39,     9,   -39,   -39,
     -39,   -39,   -39,   -39,    27,    13,     0,   -39,    25,     2,
     -39,    25,   -39,   -39,    -6,   -39,   -39,    31,    32,    17,
      17,   -39,    33,    34,   -39,   -39,   -39,   -39,    35,   -39,
      35,   -39,    24,   -39,     3,   -39,   -39,   -39,   -39,   -39,
      26,     7,   -39,     8,    28,   -39,   -39,   -39,   -39,   -39,
     -39,   -39,   -39,    35,   -39,   -39
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
     -39,   -39,     5,   -39,   -39,   -39,   -39,    19,    30,   -39,
     -39,    10,   -38,   -39,   -39,   -39,   -39,     4,    11,   -39,
     -39,    12,   -39,    15,    16,   -39,   -39,   -39
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -42
static const yysigned_char yytable[] =
{
      52,   -40,    52,    11,    12,    13,     6,    40,    14,    15,
      42,    34,    11,    12,    13,    38,    40,    14,    15,    60,
      60,    61,    64,    62,    62,    65,     1,     7,    32,     2,
      33,     9,    14,    54,    45,    46,    31,    36,    42,   -41,
      39,    32,    48,    49,    50,    33,    35,     0,    58,     0,
      53,     0,     0,    55,     0,     0,    59,    56,    57
};

static const yysigned_char yycheck[] =
{
      38,     7,    40,     3,     4,     5,     0,    13,     8,     9,
       7,    11,     3,     4,     5,    13,    13,     8,     9,    12,
      12,    14,    14,    16,    16,    63,     3,    10,    15,     6,
      17,     9,     8,     9,    29,    30,     9,    12,     7,     7,
      21,    15,     9,     9,     9,    17,    16,    -1,    44,    -1,
      40,    -1,    -1,    42,    -1,    -1,    44,    42,    42
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,     6,    19,    21,    22,     0,    10,    20,     9,
      23,     3,     4,     5,     8,     9,    24,    26,    27,    28,
      30,    32,    33,    34,    36,    37,    38,    41,    42,    43,
      44,     9,    15,    17,    11,    26,    12,    25,    13,    25,
      13,    35,     7,    39,    40,    20,    20,    45,     9,     9,
       9,    29,    30,    29,     9,    36,    41,    42,    35,    39,
      12,    14,    16,    31,    14,    30
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrlab1


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL          goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY && yylen == 1)                          \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      yytoken = YYTRANSLATE (yychar);                           \
      YYPOPSTACK;                                               \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror ("syntax error: cannot back up");\
      YYERROR;                                                  \
    }                                                           \
while (0)

#define YYTERROR        1
#define YYERRCODE       256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

# define YYDSYMPRINT(Args)                      \
do {                                            \
  if (yydebug)                                  \
    yysymprint Args;                            \
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)            \
do {                                                            \
  if (yydebug)                                                  \
    {                                                           \
      YYFPRINTF (stderr, "%s ", Title);                         \
      yysymprint (stderr,                                       \
                  Token, Value);        \
      YYFPRINTF (stderr, "\n");                                 \
    }                                                           \
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylineno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylineno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (Rule);             \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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



#if YYERROR_VERBOSE

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

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  /* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;             /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

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

  if (yyss + yystacksize - 1 <= yyssp)
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
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow ("parser stack overflow",
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),

                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        short *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyoverflowlab;
        YYSTACK_RELOCATE (yyss);
        YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


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

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 257 "graphviz_parser.yy"
    {yyval.i=0;;}
    break;

  case 4:
#line 261 "graphviz_parser.yy"
    {
    graphviz::vlist.clear();
    graphviz::attributes.clear();
    graphviz::subgraphs.clear();
    graphviz::nodes.clear();
    std::string* name = static_cast<std::string*>(yyvsp[0].ptr);
    graphviz::previous_graph = static_cast<graphviz::Subgraph*>(g);
    graphviz::current_graph = static_cast<graphviz::Subgraph*>(g);
    graphviz::set_graph_name(*name);
    delete name;
  ;}
    break;

  case 7:
#line 277 "graphviz_parser.yy"
    {yyval.ptr = yyvsp[0].ptr; ;}
    break;

  case 8:
#line 277 "graphviz_parser.yy"
    {yyval.ptr=(void*)(new std::string("G")); ;}
    break;

  case 15:
#line 291 "graphviz_parser.yy"
    { 
    graphviz::set_attribute(*graphviz::current_graph,
                          graphviz::attribute_state); 
  ;}
    break;

  case 16:
#line 297 "graphviz_parser.yy"
    { graphviz::attribute_state = GRAPH_GRAPH_A; ;}
    break;

  case 17:
#line 298 "graphviz_parser.yy"
    { graphviz::attribute_state = GRAPH_NODE_A; ;}
    break;

  case 18:
#line 299 "graphviz_parser.yy"
    { graphviz::attribute_state = GRAPH_EDGE_A; ;}
    break;

  case 21:
#line 306 "graphviz_parser.yy"
    { 
    std::string* name  = static_cast<std::string*>(yyvsp[-2].ptr);
    std::string* value = static_cast<std::string*>(yyvsp[0].ptr);
    graphviz::attributes[*name] = *value; 
    delete name;
    delete value;
  ;}
    break;

  case 28:
#line 318 "graphviz_parser.yy"
    { yyval.i = 0; ;}
    break;

  case 29:
#line 322 "graphviz_parser.yy"
    { 
    graphviz::set_attribute(
         *static_cast<graphviz::Subgraph*>(graphviz::current_graph),
                            GRAPH_GRAPH_A);
  ;}
    break;

  case 30:
#line 330 "graphviz_parser.yy"
    { 
    graphviz::Vertex* temp   = static_cast<graphviz::Vertex*>(yyvsp[-1].ptr); 
    graphviz::current_vertex = *temp;
    graphviz::set_attribute(*static_cast<GRAPHVIZ_GRAPH*>(YYPARSE_PARAM),
                            NODE_A); 
    delete temp;
    yyval.i = 0;
  ;}
    break;

  case 31:
#line 340 "graphviz_parser.yy"
    { yyval.i=0; ;}
    break;

  case 32:
#line 340 "graphviz_parser.yy"
    { yyval.i=0; ;}
    break;

  case 33:
#line 344 "graphviz_parser.yy"
    {
    std::string* name  = static_cast<std::string*>(yyvsp[0].ptr);
    std::pair<graphviz::Iter, bool> result = graphviz::lookup(*name); 
    if (result.second) {
      graphviz::current_vertex = result.first->second; 
      if (! graphviz::current_graph->is_root())
        boost::add_vertex(graphviz::current_vertex, *graphviz::current_graph);
    } else
      graphviz::current_vertex = graphviz::add_name(*name, *static_cast<GRAPHVIZ_GRAPH*>(YYPARSE_PARAM)) ; 
    graphviz::Vertex* temp = new graphviz::Vertex(graphviz::current_vertex);
    yyval.ptr = (void *)temp;
    graphviz::attribute_state = NODE_A;  
    delete name;
  ;}
    break;

  case 34:
#line 358 "graphviz_parser.yy"
    { yyval.ptr=yyvsp[0].ptr; ;}
    break;

  case 35:
#line 362 "graphviz_parser.yy"
    {
    //consider port as a special properties ?? --need work here
    std::string* name = static_cast<std::string*>(yyvsp[-2].ptr);
    std::string* port = static_cast<std::string*>(yyvsp[0].ptr);

    std::pair<graphviz::Iter, bool> result = graphviz::lookup(*name); 
    if (result.second) 
      graphviz::current_vertex = result.first->second; 
    else
      graphviz::current_vertex = graphviz::add_name(*name, *static_cast<GRAPHVIZ_GRAPH*>(YYPARSE_PARAM)) ; 
    graphviz::Vertex* temp = new graphviz::Vertex(graphviz::current_vertex);
    yyval.ptr = (void *)temp;
    graphviz::attribute_state = NODE_A;  
    delete name;
    delete port;
  ;}
    break;

  case 36:
#line 381 "graphviz_parser.yy"
    {

    typedef std::pair<void*, bool>* Ptr;
    Ptr source = static_cast<Ptr>(yyvsp[-2].ptr);

    for (std::vector<Ptr>::iterator it=graphviz::vlist.begin();
         it !=graphviz::vlist.end(); ++it) { 
      if ( source->second ) {
        if ( (*it)->second )
          graphviz::add_edges(static_cast<graphviz::Subgraph*>(source->first),
                            static_cast<graphviz::Subgraph*>((*it)->first),
                            *static_cast<GRAPHVIZ_GRAPH*>(YYPARSE_PARAM));
        else
          graphviz::add_edges(static_cast<graphviz::Subgraph*>(source->first),
                            *static_cast<graphviz::Vertex*>((*it)->first),
                            *static_cast<GRAPHVIZ_GRAPH*>(YYPARSE_PARAM));
      } else {
        graphviz::Vertex* temp = static_cast<graphviz::Vertex*>(source->first);
        if ( (*it)->second )
          graphviz::add_edges(*temp,
                            static_cast<graphviz::Subgraph*>((*it)->first),
                            *static_cast<GRAPHVIZ_GRAPH*>(YYPARSE_PARAM));
        else
          graphviz::add_edges(*temp,
                            *static_cast<graphviz::Vertex*>((*it)->first),
                            *static_cast<GRAPHVIZ_GRAPH*>(YYPARSE_PARAM));
        delete temp;
      }

      delete source; 
      source = *it; 
    } 
    
    if ( ! source->second ) {
      graphviz::Vertex* temp = static_cast<graphviz::Vertex*>(source->first);
      delete temp;
    }
    delete source;

    graphviz::attributes.clear();
    graphviz::vlist.clear(); 
  ;}
    break;

  case 37:
#line 426 "graphviz_parser.yy"
    { graphviz::vlist.push_back(static_cast<std::pair<void*, bool>*>(yyvsp[0].ptr)); ;}
    break;

  case 40:
#line 433 "graphviz_parser.yy"
    { 
    std::pair<void*, bool>* temp = new std::pair<void*, bool>;
    temp->first = yyvsp[0].ptr;
    temp->second = false;
    yyval.ptr = (void*)temp;

    graphviz::attribute_state = EDGE_A; 
  ;}
    break;

  case 41:
#line 442 "graphviz_parser.yy"
    { 
    std::pair<void*, bool>* temp = new std::pair<void*, bool>;
    temp->first = yyvsp[0].ptr;
    temp->second = true;
    yyval.ptr = (void*)temp;

    graphviz::attribute_state = EDGE_A; 
  ;}
    break;

  case 42:
#line 453 "graphviz_parser.yy"
    {
    if ( yyvsp[0].i )
      graphviz::current_graph = &graphviz::current_graph->parent();
    else
      graphviz::current_graph = graphviz::previous_graph;
  ;}
    break;

  case 43:
#line 460 "graphviz_parser.yy"
    {
    graphviz::previous_graph = graphviz::current_graph;
    std::string name = graphviz::random_string();
    graphviz::Subgraph* temp = graphviz::create_subgraph(name);
    graphviz::current_graph = temp;
    graphviz::set_graph_name(name);

    yyval.ptr = (void *) graphviz::current_graph;
  ;}
    break;

  case 44:
#line 469 "graphviz_parser.yy"
    {
    graphviz::current_graph = &graphviz::current_graph->parent();
  ;}
    break;

  case 45:
#line 475 "graphviz_parser.yy"
    {
    //lookup ID_T if it is already in the subgraph,
    //if it is not, add a new subgraph
    std::string* name  = static_cast<std::string*>(yyvsp[0].ptr);

    std::pair<graphviz::It, bool> temp = graphviz::lookup_subgraph(*name);

    graphviz::previous_graph = graphviz::current_graph;
    if ( temp.second )  {//found 
      graphviz::current_graph = (temp.first)->second;
    } else {
      graphviz::current_graph = graphviz::create_subgraph(*name);
      graphviz::set_graph_name(*name);
    }

    yyval.ptr = (void *) graphviz::current_graph;
    delete name;
  ;}
    break;

  case 46:
#line 495 "graphviz_parser.yy"
    {yyval.i = 1; ;}
    break;

  case 47:
#line 495 "graphviz_parser.yy"
    { yyval.i = 0; ;}
    break;


    }

/* Line 999 of yacc.c.  */
#line 1562 "graphviz_graph_parser.cpp"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
        {
          YYSIZE_T yysize = 0;
          int yytype = YYTRANSLATE (yychar);
          char *yymsg;
          int yyx, yycount;

          yycount = 0;
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  */
          for (yyx = yyn < 0 ? -yyn : 0;
               yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
              yysize += yystrlen (yytname[yyx]) + 15, yycount++;
          yysize += yystrlen ("syntax error, unexpected ") + 1;
          yysize += yystrlen (yytname[yytype]);
          yymsg = (char *) YYSTACK_ALLOC (yysize);
          if (yymsg != 0)
            {
              char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
              yyp = yystpcpy (yyp, yytname[yytype]);

              if (yycount < 5)
                {
                  yycount = 0;
                  for (yyx = yyn < 0 ? -yyn : 0;
                       yyx < (int) (sizeof (yytname) / sizeof (char *));
                       yyx++)
                    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
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
            yyerror ("syntax error; also virtual memory exhausted");
        }
      else
#endif /* YYERROR_VERBOSE */
        yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
          /* Pop the error token.  */
          YYPOPSTACK;
          /* Pop the rest of the stack.  */
          while (yyss < yyssp)
            {
              YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
              yydestruct (yystos[*yyssp], yyvsp);
              YYPOPSTACK;
            }
          YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval);
      yychar = YYEMPTY;

    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      yyvsp--;
      yystate = *--yyssp;

      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 497 "graphviz_parser.yy"


namespace boost {
  
  void read_graphviz(const std::string& filename, GRAPHVIZ_GRAPH& g) {
    FILE* file = fopen(filename.c_str(), "r");
    yyrestart(file);
    void* in = static_cast<void*>(file);
    yyparse(static_cast<void*>(&g));
  }

  void read_graphviz(FILE* file, GRAPHVIZ_GRAPH& g) {
    void* in = static_cast<void*>(file);
    yyrestart(file);
    yyparse(static_cast<void*>(&g));
  }
    
}


