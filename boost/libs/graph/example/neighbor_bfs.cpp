//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
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

#include <boost/config.hpp>

#include <algorithm>
#include <vector>
#include <utility>
#include <iostream>

#include <boost/graph/visitors.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/property_map.hpp>

/*
  
  Sample Output:

  0 --> 2 
  1 --> 1 3 4 
  2 --> 1 3 4 
  3 --> 1 4 
  4 --> 0 1 
  distances: 0 2 1 2 1 
  parent[0] = 0
  parent[1] = 2
  parent[2] = 0
  parent[3] = 2
  parent[4] = 0

*/

template <class ParentDecorator>
struct print_parent {
  print_parent(const ParentDecorator& p_) : p(p_) { }
  template <class Vertex>
  void operator()(const Vertex& v) const {
    std::cout << "parent[" << v << "] = " <<  p[v]  << std::endl;
  }
  ParentDecorator p;
};

template <class DistanceMap, class PredecessorMap, class ColorMap>
class distance_and_pred_visitor : public boost::bfs_visitor<>
{
  typedef typename boost::property_traits<ColorMap>::value_type ColorValue;
  typedef boost::color_traits<ColorValue> Color;
public:
  distance_and_pred_visitor(DistanceMap d, PredecessorMap p, ColorMap c)
    : m_distance(d), m_predecessor(p), m_color(c) { }

  template <class Edge, class Graph>
  void tree_edge(Edge e, const Graph& g) const
  {
    typename boost::graph_traits<Graph>::vertex_descriptor 
      u = source(e, g), v = target(e, g);
    if (get(m_color, v) == Color::white()) {
      put(m_distance, v, get(m_distance, u) + 1);
      put(m_predecessor, v, u);
    } else if (get(m_color, u) == Color::white()) {
      put(m_distance, u, get(m_distance, v) + 1);
      put(m_predecessor, u, v);
    }
  }
  DistanceMap m_distance;
  PredecessorMap m_predecessor;
  ColorMap m_color;
};

int main(int , char* []) 
{
  typedef boost::adjacency_list< 
    boost::mapS, boost::vecS, boost::bidirectionalS,
    boost::property<boost::vertex_color_t, boost::default_color_type>
  > Graph;

  typedef boost::property_map<Graph, boost::vertex_color_t>::type
    ColorMap;
  
  Graph G(5);
  boost::add_edge(0, 2, G);
  boost::add_edge(1, 1, G);
  boost::add_edge(1, 3, G);
  boost::add_edge(1, 4, G);
  boost::add_edge(2, 1, G);
  boost::add_edge(2, 3, G);
  boost::add_edge(2, 4, G);
  boost::add_edge(3, 1, G);
  boost::add_edge(3, 4, G);
  boost::add_edge(4, 0, G);
  boost::add_edge(4, 1, G);

  typedef Graph::vertex_descriptor Vertex;

  // Array to store predecessor (parent) of each vertex. This will be
  // used as a Decorator (actually, its iterator will be).
  std::vector<Vertex> p(boost::num_vertices(G));
  // VC++ version of std::vector has no ::pointer, so
  // I use ::value_type* instead.
  typedef std::vector<Vertex>::value_type* Piter;

  // Array to store distances from the source to each vertex .  We use
  // a built-in array here just for variety. This will also be used as
  // a Decorator.  
  typedef boost::graph_traits<Graph>::vertices_size_type size_type;
  size_type d[5];
  std::fill_n(d, 5, 0);

  // The source vertex
  Vertex s = *(boost::vertices(G).first);
  p[s] = s;
  distance_and_pred_visitor<size_type*, Vertex*, ColorMap> 
    vis(d, &p[0], get(boost::vertex_color, G));
  boost::neighbor_breadth_first_search
    (G, s, boost::visitor(vis).
     color_map(get(boost::vertex_color, G)));

  boost::print_graph(G);

  if (boost::num_vertices(G) < 11) {
    std::cout << "distances: ";
#ifdef BOOST_OLD_STREAM_ITERATORS
    std::copy(d, d + 5, std::ostream_iterator<int, char>(std::cout, " "));
#else
    std::copy(d, d + 5, std::ostream_iterator<int>(std::cout, " "));
#endif
    std::cout << std::endl;

    std::for_each(boost::vertices(G).first, boost::vertices(G).second, 
                  print_parent<Piter>(&p[0]));
  }

  return 0;
}
