// Boost.Graph library isomorphism test

// Copyright (C) 2001 Doug Gregor (gregod@cs.rpi.edu)
//
// Permission to copy, use, sell and distribute this software is granted
// provided this copyright notice appears in all copies.
// Permission to modify the code and to distribute modified code is granted
// provided this copyright notice appears in all copies, and a notice
// that the code was modified is included with the copyright notice.
//
// This software is provided "as is" without express or implied warranty,
// and with no claim as to its suitability for any purpose.

// For more information, see http://www.boost.org

#define BOOST_INCLUDE_MAIN
#include <boost/test/test_tools.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/isomorphism.hpp>
#include <boost/property_map.hpp>
#include <iostream>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace boost;

// Verify that the given mapping iso_map from the vertices of g1 to the
// vertices of g2 describes an isomorphism.
// Note: this could be made much faster by specializing based on the graph
// concepts modeled, but since we're verifying an O(n^(lg n)) algorithm,
// O(n^4) won't hurt us.
template<typename Graph1, typename Graph2, typename IsoMap>
inline bool verify_isomorphism(const Graph1& g1, const Graph2& g2, 
			       IsoMap iso_map)
{
  if (num_vertices(g1) != num_vertices(g2) || num_edges(g1) != num_edges(g2))
    return false;
  
  for (typename graph_traits<Graph1>::edge_iterator e1 = edges(g1).first;
       e1 != edges(g1).second; ++e1) {
    bool found_edge = false;
    for (typename graph_traits<Graph2>::edge_iterator e2 = edges(g2).first;
	 e2 != edges(g2).second && !found_edge; ++e2) {
      if (source(*e2, g2) == get(iso_map, source(*e1, g1)) &&
	  target(*e2, g2) == get(iso_map, target(*e1, g1))) {
	found_edge = true;
      }
    }
    
    if (!found_edge)
      return false;
  }
  
  return true;
}

template<typename Graph1, typename Graph2>
void randomly_permute_graph(const Graph1& g1, Graph2& g2)
{
  // Need a clean graph to start with
  assert(num_vertices(g2) == 0);
  assert(num_edges(g2) == 0);

  typedef typename graph_traits<Graph1>::vertex_descriptor vertex1;
  typedef typename graph_traits<Graph2>::vertex_descriptor vertex2;
  typedef typename graph_traits<Graph1>::edge_iterator edge_iterator;

  // Decide new order
  std::vector<vertex1> orig_vertices(vertices(g1).first, vertices(g1).second);
  std::random_shuffle(orig_vertices.begin(), orig_vertices.end());
  std::map<vertex1, vertex2> vertex_map;

  for (std::size_t i = 0; i < num_vertices(g1); ++i) {
    vertex_map[orig_vertices[i]] = add_vertex(g2);
  }

  for (edge_iterator e = edges(g1).first; e != edges(g1).second; ++e) {
    add_edge(vertex_map[source(*e, g1)], vertex_map[target(*e, g1)], g2);
  }
}

template<typename Graph>
void generate_random_digraph(Graph& g, double edge_probability)
{
  typedef typename graph_traits<Graph>::vertex_iterator vertex_iterator;

  for (vertex_iterator u = vertices(g).first; u != vertices(g).second; ++u) {
    vertex_iterator v = u;
    ++v;
    for (; v != vertices(g).second; ++v) {
      if (drand48() <= edge_probability)
        add_edge(*u, *v, g);
    }
  }
}

void test_isomorphism(int n, double edge_probability) 
{
  typedef adjacency_list<vecS, vecS, bidirectionalS> graph1;
  typedef graph1 graph2;
  //  typedef adjacency_list<listS, listS, bidirectionalS,
  //                         property<vertex_index_t, int> > graph2;

  graph1 g1(n);
  generate_random_digraph(g1, edge_probability);
  graph2 g2;
  randomly_permute_graph(g1, g2);

#if 0
  int v_idx = 0;
  for (graph2::vertex_iterator v = vertices(g2).first; 
       v != vertices(g2).second; ++v) {
    put(vertex_index_t(), g2, *v, v_idx++);
  }
#endif

  std::map<graph1::vertex_descriptor, graph2::vertex_descriptor> mapping;

  BOOST_TEST(isomorphism(g1, g2, 
                         isomorphism_map(make_assoc_property_map(mapping))));
  BOOST_TEST(verify_isomorphism(g1, g2, make_assoc_property_map(mapping)));
}

int test_main(int argc, char* argv[])
{
  srandom(std::time(0));
  srand48(std::time(0));
  typedef adjacency_list<vecS, vecS, bidirectionalS> graph;

  if (argc < 3) {
    for (int n = 50; n <= 100; n += 10) {
      test_isomorphism(n, 0.45);
    }
    return 0;
  }

  int n = atoi(argv[1]);
  double edge_prob = atof(argv[2]);
  test_isomorphism(n, edge_prob);

  return 0;
}
