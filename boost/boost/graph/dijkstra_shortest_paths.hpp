//
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
//
#ifndef BOOST_GRAPH_DIJKSTRA_HPP
#define BOOST_GRAPH_DIJKSTRA_HPP

#include <functional>
#include <boost/pending/limits.hpp>
#include <boost/graph/uniform_cost_search.hpp>

namespace boost {

  // Variant (1)
  template <class VertexListGraph>
  inline void
  dijkstra_shortest_paths(VertexListGraph& g,
                  typename graph_traits<VertexListGraph>::vertex_descriptor s)
  {
    dijkstra_shortest_paths(g, s, 
                            get_vertex_property_accessor(G, distance_tag()));
  }

  // Variant (2)
  template <class VertexListGraph, class DistancePA>
  inline void
  dijkstra_shortest_paths(VertexListGraph& g,
                  typename graph_traits<VertexListGraph>::vertex_descriptor s, 
                  DistancePA d)
  {
    null_visitor null_vis;
    dijkstra_shortest_paths(g, s, d,
                            get_edge_property_accessor(g, weight_tag()), 
                            get_vertex_property_accessor(g, color_tag()), 
                            get_vertex_property_accessor(g, id_tag()), 
                            make_ucs_visitor(null_vis));
  }

  // Variant (3)
  template <class VertexListGraph, class DistancePA, class UniformCostVisitor>
  inline void
  dijkstra_shortest_paths(VertexListGraph& g, 
                  typename graph_traits<VertexListGraph>::vertex_descriptor s, 
                  DistancePA d, UniformCostVisitor visit)
  {
    dijkstra_shortest_paths(g, s, d, 
                            get_edge_property_accessor(g, weight_tag()), 
                            get_vertex_property_accessor(g, color_tag()), 
                            get_vertex_property_accessor(g, id_tag()), 
                            visit);
  }

  // Variant (4)
  template <class VertexListGraph, class UniformCostVisitor, 
            class DistancePA, class WeightPA, class ColorPA, class ID_PA>
  inline void
  dijkstra_shortest_paths(VertexListGraph& g,
                  typename graph_traits<VertexListGraph>::vertex_descriptor s, 
                  DistancePA distance, WeightPA weight, ColorPA color, ID_PA id,
                  UniformCostVisitor vis)
  {
    typedef typename property_traits<DistancePA>::value_type D;
    typedef typename property_traits<WeightPA>::value_type W;
    std::less<D> compare;
    std::plus<W> combine;

    typename boost::graph_traits<VertexListGraph>::vertex_iterator ui, ui_end;
    for (tie(ui, ui_end) = vertices(g); ui != ui_end; ++ui)
      put(distance, *ui, std::numeric_limits<D>::max());

    put(distance, s, D());
    uniform_cost_search(g, s, distance, weight, color, id, 
                        compare, combine, vis);
  }


} /*namespace*/

#endif /* BOOST_GRAPH_DIJKSTRA_HPP*/
