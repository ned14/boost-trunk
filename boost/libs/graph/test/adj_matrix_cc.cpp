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
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/graph_archetypes.hpp>
#include <boost/graph/adjacency_matrix.hpp>

int main(int,char*[])
{
  using namespace boost;
  // Check adjacency_matrix without properties
  {
    typedef adjacency_matrix<directedS> Graph;
    function_requires< VertexAndEdgeListGraphConcept<Graph> >();
    function_requires< MutableGraphConcept<Graph> >();
    function_requires< AdjacencyMatrixConcept<Graph> >();
  }
  {
    typedef adjacency_matrix<undirectedS> Graph;
    function_requires< VertexAndEdgeListGraphConcept<Graph> >();
    function_requires< MutableGraphConcept<Graph> >();
    function_requires< AdjacencyMatrixConcept<Graph> >();
  }
  // Check adjacency_matrix with properties
  {
    typedef adjacency_matrix<directedS, 
      property<vertex_color_t, int>,
      property<edge_weight_t, float> > Graph;
    typedef graph_traits<Graph>::vertex_descriptor Vertex;
    typedef graph_traits<Graph>::edge_descriptor Edge;
    function_requires< VertexAndEdgeListGraphConcept<Graph> >();
    function_requires< AdjacencyMatrixConcept<Graph> >();
    function_requires< MutablePropertyGraphConcept<Graph> >();
    function_requires< ReadablePropertyGraphConcept<Graph, 
      Vertex, vertex_index_t> >();
    function_requires< PropertyGraphConcept<Graph, Vertex, vertex_color_t> >();
    function_requires< PropertyGraphConcept<Graph, Edge, edge_weight_t> >();
  }
  {
    typedef adjacency_matrix<undirectedS, 
      property<vertex_color_t, int>,
      property<edge_weight_t, float> > Graph;
    typedef graph_traits<Graph>::vertex_descriptor Vertex;
    typedef graph_traits<Graph>::edge_descriptor Edge;
    function_requires< VertexAndEdgeListGraphConcept<Graph> >();
    function_requires< AdjacencyMatrixConcept<Graph> >();
    function_requires< MutablePropertyGraphConcept<Graph> >();
    function_requires< ReadablePropertyGraphConcept<Graph, 
      Vertex, vertex_index_t> >();
    function_requires< PropertyGraphConcept<Graph, Vertex, vertex_color_t> >();
    function_requires< PropertyGraphConcept<Graph, Edge, edge_weight_t> >();
  }
  return 0;
}
