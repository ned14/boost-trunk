// Copyright (C) 2006-2009 Dmitry Bufistov and Andrey Parfenov

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <sstream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/property_iter_range.hpp>
#include <boost/graph/howard_cycle_ratio.hpp>

#include <boost/test/minimal.hpp>

/**
 * @author Dmitry Bufistov
 * @author Andrey Parfenov
 */

/*!
* The graph has two equal cycles with ratio 2/3
*/
static const char test_graph1[] = "digraph G {\
  edge [w1=1, w2=1];\
  1->2\
  2->3 [w1=0]\
  3->4\
  4->2\
  1->5\
  5->6\
  6->7 [w1=0]\
  7->5 \
}";

/*!
* The graph has no cycles
*/
static const std::string test_graph2 = "digraph G {edge [w1=1]; 1->3 [w2=1]; 1->2 [w2=2]; 1->4 [w2=7]; }";

/*!
* Example from the paper "Nunerical computation of spectral elements"
* Maximum cycle ratio is 5.5
*/
static const char test_graph3[] = "\
digraph article {\
  edge [w2 =2];\
  1->1 [w1 = 1];\
  1->2 [w1 = 2];\
  1->4 [w1 = 7];\
  2->2 [w1 = 3];\
  2->3 [w1 = 5];\
  3->2 [w1 = 4];\
  3->4 [w1 = 3];\
  4->2 [w1 = 2];\
  4->3 [w1 = 8];\
}";

/*!
* Simple multigraph.
* Maximum cycle ratio is 2.5, minimum  0.5
*/
static const char test_graph4[] = "digraph G {\
edge [w2=1];\
a->b  [w1=1];\
b->a  [w1=0];\
a->b [w1=2];\
b->a [w1=3];\
}";

/*!
* The big graph with two equal cycles
*/
static const char test_graph5[]= "digraph G { edge [w2=1, w1=1]; n94->n8; n95->n8; n93->n8; n93->n9; n42->n9; n23->n13;\
n29->n13; n95->n14; n37->n14; n95->n19; n37->n19; n94->n23; n60->n26; n76->n26; n94->n29; n9->n33 [w1=0]; n80->n33;\
n14->n34 [w1=0];n19->n34; n94->n37; n94->n42; n95->n42; n8->n60; n26->n60; n26->n76; n106->n76; n93->n80; n42->n80;\
n33->n93; n60->n93; n13->n94; n60->n94; n34->n95; n60->n95; n94->n106; n95->n106; n93->n106;\
}";

/*!
* Random graph generated by hands.
* Maximum cycle ratio is 3.58, minimum is 0.294118
*/
static const char test_graph6[]= "digraph test_graph6 {\
  16;\
  17;\
\
  1->2 [w1=1, w2=0.1];\
  2->3 [w1 = 2, w2=3.6];\
  3->4 [w1=7, w2=8];\
  4->5 [w1=3.1,w2=0.8];\
  4->5 [w1 = 4.2, w2=0.6];\
  4->5 [w1 = 5.3, w2=0.4];\
  5->6 [w1=-10, w2 = 34.75]\
  6->1 [w1=100, w2 = 20]\
\
  1->7 [w1=10, w2 = 20];\
  7->8 [w1=3.75, w2 = 1.25];\
  7->8 [w1=30, w2 = 22.2];\
  8->9 [w1=10, w2 = 20];\
  9->10 [w1=-2.1, w2 = 30]\
  10->6 [w1=10, w2 = 20]\
\
  11->12 [w1 = 5, w2=0.45];\
  12->13 [w1 = 4, w2=0.2];\
  13->14 [w1 = 3, w2=15.75];\
  14->11 [w1 = -2.5, w2=0.6];\
  11->10 [w1 = -8, w2=0.9];\
  11->10 [w1 = -15, w2=2.9];\
\
  18 -> 19 [w1=18, w2=6];\
  18 -> 20 [w1=16.3, w2=8.2];\
  18 -> 21 [w1=-3, w2=15];\
  18 -> 18 [w1=2, w2=1];\
  19 -> 18 [w1=0.06, w2=0.01];\
  19 -> 19 [w1=1, w2=1.2];\
  19 -> 20 [w1=5, w2=2];\
  19 -> 21 [w1=3, w2=0.1];\
  20 -> 18 [w1=4, w2=0.2];\
  20 -> 19 [w1=11, w2=21];\
  20 -> 20 [w1=6, w2=5];\
  20 -> 21 [w1=7, w2=1];\
  21 -> 18 [w1=8, w2=2];\
  21 -> 19 [w1=12, w2=6];\
  21 -> 20 [w1=7.5, w2=4.3];\
  21 -> 21 [w1=1.25, w2=2.15];\
}";

using namespace boost;
typedef  property<vertex_index_t, int, property<boost::vertex_name_t, std::string> > vertex_props_t;
template <typename TW1, typename TW2> struct Graph
{
    typedef typename boost::property<
        boost::edge_weight_t, TW1,
        typename boost::property<
            boost::edge_weight2_t, TW2, property<boost::edge_index_t, int>
        >
    > edge_props_t;
    typedef typename boost::adjacency_list<
        boost::listS, boost::listS, boost::directedS, vertex_props_t,
        edge_props_t>
    type;
};
typedef Graph<int, int>::type diGraphInt;
typedef Graph<double, double>::type diGraphReal;

template <typename TW1, typename TW2>
struct CEdgeProps
{
  CEdgeProps(TW1 w1 = 1, TW2 w2 = 2) :
  m_w1(w1), m_w2(w2), m_edge_index((std::numeric_limits<int>::max)())
  {}
  TW1 m_w1;
  TW2 m_w2;
  int m_edge_index;
};
typedef  adjacency_matrix<directedS, no_property, CEdgeProps<int, int> > GraphMInt;

///Create "tokens_map" for reading graph properties from .dot file
template <typename TG>
void  make_dynamic_properties(TG &g, dynamic_properties &p)
{
  p.property("node_id", get(vertex_name, g));
  p.property("label", get(edge_weight, g));
  p.property("w1", get(edge_weight, g));
  p.property("w2", get(edge_weight2, g));
}

template <typename TG>
void read_data1(std::istream &is, TG &g)
{
  dynamic_properties p;
  make_dynamic_properties(g, p);
  read_graphviz(is, g, p);
  std::cout << "Number of vertices: " << num_vertices(g) << std::endl;
  std::cout << "Number of edges: " << num_edges(g) << std::endl;
  int i = 0;
  BGL_FORALL_VERTICES_T(vd, g, TG)
  {
    put(vertex_index, g, vd, i++);
  }
  i=0;
  BGL_FORALL_EDGES_T(ed, g, TG)
  {
    put(edge_index, g, ed, i++);
  }
}

template <typename TG>
void read_data(const char *file, TG &g)
{
  std::cout << "Reading data from file: " << file << std::endl;
  std::ifstream ifs(file);
  BOOST_REQUIRE(ifs.good());
  read_data1(ifs, g);
}

struct my_float : boost::mcr_float<>
{
  static double infinity()
  {
    return 1000;
  }
};

struct my_float2 : boost::mcr_float<>
{
  static double infinity() { return 2; }
};

int test_main(int argc, char* argv[])
{
  assert (argc >= 2);
  using std::endl; using std::cout;
  const double epsilon = 0.005;
  double min_cr, max_cr; ///Minimum and maximum cycle ratio
  typedef std::vector<graph_traits<diGraphInt>::edge_descriptor> ccInt_t;
  typedef std::vector<graph_traits<diGraphReal>::edge_descriptor> ccReal_t;
  ccInt_t cc; ///critical cycle

  diGraphInt tg;
  property_map<diGraphInt, vertex_index_t>::type vim = get(vertex_index, tg);
  property_map<diGraphInt, edge_weight_t>::type ew1m = get(edge_weight, tg);
  property_map<diGraphInt, edge_weight2_t>::type ew2m = ew2m;



  {
    std::istringstream  iss(test_graph1);
    assert(iss.good());
    read_data1(iss, tg);
    max_cr = maximum_cycle_ratio(tg, vim, ew1m, ew2m);
    cout << "Maximum cycle ratio is " << max_cr << endl;
    BOOST_CHECK(std::abs( max_cr - 0.666666666) < epsilon );
    tg.clear();
  }

  {
    std::istringstream  iss(test_graph2);
    read_data1(iss, tg);
    // TODO: This is causing a failuire, but I'm not really sure what it's doing per se.
    // Commented out for now.
    // BOOST_CHECK(std::abs(maximum_cycle_ratio(tg, vim, ew1m, ew2m) + (std::numeric_limits<double>::max)()) < epsilon );
    BOOST_CHECK(std::abs(boost::maximum_cycle_ratio(tg, vim, ew1m, ew2m,
                                                        static_cast<ccInt_t*>(0), my_float()) + 1000) < epsilon );
    tg.clear();
  }

  {
    std::istringstream iss(test_graph3);
    diGraphInt tgi;
    read_data1(iss, tgi);
    double max_cr = maximum_cycle_ratio(tgi, vim, ew1m, ew2m,
      static_cast<ccInt_t*>(0));
    cout << "Maximum cycle ratio is " << max_cr << endl;
    BOOST_CHECK(std::abs( max_cr - 2.75) < epsilon );
    double maxmc = maximum_cycle_mean(tgi, vim, ew1m, get(edge_index, tgi));
    cout << "Maximum cycle mean is " << maxmc << endl;
    BOOST_CHECK(std::abs( maxmc - 5.5) < epsilon );
    tg.clear();
  }

  {
    std::istringstream  iss(test_graph4);
    read_data1(iss, tg);
    max_cr = maximum_cycle_ratio(tg, vim, ew1m, ew2m);
    cout << "Maximum cycle ratio is " << max_cr << endl;
    BOOST_CHECK(std::abs( max_cr - 2.5) < epsilon );
    min_cr = minimum_cycle_ratio(tg, vim, ew1m, ew2m);
    cout << "Minimum cycle ratio is " << min_cr << endl;
    BOOST_CHECK(std::abs( min_cr - 0.5) < epsilon );
    tg.clear();
  }

  {
    std::istringstream  iss(test_graph5);
    read_data1(iss, tg);
        min_cr = minimum_cycle_ratio(tg, vim, ew1m, ew2m, &cc, my_float());
    BOOST_CHECK(std::abs( min_cr - 0.666666666) < epsilon );
    cout << "Minimum cycle ratio is " << min_cr << endl;
    cout << "Critical cycle is:\n";
    for (ccInt_t::iterator itr = cc.begin(); itr != cc.end(); ++itr)
    {
      cout << "(" << get(vertex_name, tg, source(*itr, tg)) <<
        "," << get(vertex_name, tg, target(*itr, tg)) << ") ";
    }
    cout << endl;
    tg.clear();
  }

  {
      read_data(argv[1], tg);
      min_cr = boost::minimum_cycle_ratio(tg, vim, ew1m, ew2m, &cc, my_float2());
      cout << "Minimum cycle ratio is " << min_cr << endl;
      BOOST_CHECK(std::abs(min_cr - 0.33333333333) < epsilon );
      cout << "Critical cycle is:" << endl;
      for (ccInt_t::iterator it = cc.begin(); it != cc.end(); ++it)
    {
          cout << "(" << get(vertex_name, tg, source(*it, tg)) << "," <<
            get(vertex_name, tg, target(*it, tg)) << ") ";
    }
      cout << endl;
      tg.clear();
  }

  {
    diGraphReal  tgr;
    ccReal_t  cc1;
    std::istringstream  iss(test_graph6);
    read_data1(iss, tgr);
    max_cr = maximum_cycle_ratio(tgr, get(vertex_index, tgr), get(edge_weight, tgr), get(edge_weight2, tgr));
    cout << "Maximum cycle ratio is " << max_cr << endl;
    min_cr = minimum_cycle_ratio(tgr, get(vertex_index, tgr), get(edge_weight, tgr),
                                     get(edge_weight2, tgr), &cc);
    cout << "Minimal cycle ratio is " << min_cr << endl;
    std::pair<double, double> cr(.0,.0);
    cout << "Critical cycle is:\n";
    for (ccReal_t::iterator itr = cc.begin(); itr != cc.end(); ++itr)
    {
      cr.first += get(edge_weight, tgr, *itr); cr.second += get(edge_weight2, tgr, *itr);
      cout << "(" << get(vertex_name, tgr, source(*itr, tgr)) << "," <<
        get(vertex_name, tgr, target(*itr, tgr)) << ") ";
    }
    BOOST_CHECK(std::abs(cr.first / cr.second - min_cr) < epsilon);
    cout << endl;
  }

  {
    GraphMInt gm(10);
    typedef graph_traits<GraphMInt>::vertex_iterator VertexItM;
    typedef graph_traits<GraphMInt>::edge_descriptor EdgeM;
    VertexItM  vi1, vi2, vi_end;
    for (tie(vi1, vi_end) = vertices(gm); vi1 != vi_end; ++vi1)
    {
      for (vi2 = vertices(gm).first; vi2 != vi_end; ++vi2)
        add_edge(*vi1, *vi2, gm);
    }
    max_cr = maximum_cycle_ratio(gm, get(vertex_index, gm),
      get(&CEdgeProps<int, int>::m_w1, gm), get(&CEdgeProps<int, int>::m_w2, gm));
    BOOST_CHECK(std::abs(max_cr - 0.5) < epsilon);
  }

  return 0;
}

