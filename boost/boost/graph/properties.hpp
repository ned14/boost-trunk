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
#ifndef BOOST_GRAPH_PROPERTIES_HPP
#define BOOST_GRAPH_PROPERTIES_HPP

#include <boost/config.hpp>
#include <boost/pending/property.hpp>
#include <boost/property_map.hpp>

namespace boost {

  enum default_color_type { white_color, gray_color, black_color };

  template <class ColorValue>
  struct color_traits { };

  template <>
  struct color_traits<default_color_type> {
    static default_color_type white() { return white_color; }
    static default_color_type gray() { return gray_color; }
    static default_color_type black() { return black_color; }
  };

  // These functions are now obsolete, replaced by color_traits.
  inline default_color_type white(default_color_type) { return white_color; }
  inline default_color_type gray(default_color_type) { return gray_color; }
  inline default_color_type black(default_color_type) { return black_color; }

#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  template <>
  struct property_traits<default_color_type*> {
    typedef default_color_type value_type;
    typedef std::ptrdiff_t key_type;
    typedef lvalue_property_map_tag category;
  };
  // get/put already defined for T*
#endif

  namespace detail {
    // These enum's are only necessary for a workaround for compilers that
    // don't do partial specialization (like VC++).
    enum property_tag_num
    {
      vertex_index_num = 1, edge_index_num, vertex_name_num,
      edge_name_num, graph_name_num, edge_weight_num, vertex_distance_num,
      vertex_color_num, vertex_degree_num, vertex_out_degree_num, 
      vertex_in_degree_num, vertex_discover_time_num, vertex_finish_time_num,
      edge_reverse_num, edge_residual_capacity_num, edge_capacity_num,
      last_property_num
    };
  } // namespace detail


  struct graph_property_tag { };
  struct vertex_property_tag { };
  struct edge_property_tag { };

#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  // See examples/edge_property.cpp for how to use this.
#define BOOST_INSTALL_PROPERTY(KIND, NAME) \
  template <> struct property_num<KIND##_##NAME##_t> { \
    enum { value = KIND##_##NAME }; }; \
  template <> struct property_kind<KIND##_##NAME##_t> { \
    typedef KIND##_property_tag type; \
  }
#else
#define BOOST_INSTALL_PROPERTY(KIND, NAME) \
  template <> struct property_kind<KIND##_##NAME##_t> { \
    typedef KIND##_property_tag type; \
  }
#endif

#define BOOST_DEF_PROPERTY(KIND, NAME) \
  enum KIND##_##NAME##_t { KIND##_##NAME = detail::KIND##_##NAME##_num  }; \
  BOOST_INSTALL_PROPERTY(KIND, NAME)

  BOOST_DEF_PROPERTY(vertex, index);
  BOOST_DEF_PROPERTY(edge, index);
  BOOST_DEF_PROPERTY(edge, name);
  BOOST_DEF_PROPERTY(edge, weight);
  BOOST_DEF_PROPERTY(vertex, name);
  BOOST_DEF_PROPERTY(graph, name);
  BOOST_DEF_PROPERTY(vertex, distance);
  BOOST_DEF_PROPERTY(vertex, color);
  BOOST_DEF_PROPERTY(vertex, degree);
  BOOST_DEF_PROPERTY(vertex, in_degree);
  BOOST_DEF_PROPERTY(vertex, out_degree);
  BOOST_DEF_PROPERTY(vertex, discover_time);
  BOOST_DEF_PROPERTY(vertex, finish_time);
  BOOST_DEF_PROPERTY(edge, reverse);
  BOOST_DEF_PROPERTY(edge, capacity);
  BOOST_DEF_PROPERTY(edge, residual_capacity);

#undef BOOST_DEF_PROPERTY

  namespace detail {

    struct dummy_edge_property_selector {
      template <class Graph, class Property, class Tag>
      struct bind {
        typedef identity_property_map type;
        typedef identity_property_map const_type;
      };
    };
    struct dummy_vertex_property_selector {
      template <class Graph, class Property, class Tag>
      struct bind {
        typedef identity_property_map type;
        typedef identity_property_map const_type;
      };
    };

  } // namespace detail

  // Graph classes can either partially specialize property_map
  // or they can specialize these two selector classes.
  template <class GraphTag>
  struct edge_property_selector {
    typedef detail::dummy_edge_property_selector type;
  };

  template <class GraphTag>
  struct vertex_property_selector {
    typedef detail::dummy_vertex_property_selector type;
  };

  namespace detail {

    template <class Graph, class PropertyTag>
    struct edge_property_map {
      typedef typename Graph::edge_property_type Property;
      typedef typename Graph::graph_tag graph_tag;
      typedef typename edge_property_selector<graph_tag>::type Selector;
      typedef typename Selector::template bind<Graph,Property,PropertyTag>
        Bind;
      typedef typename Bind::type type;
      typedef typename Bind::const_type const_type;
    };
    template <class Graph, class PropertyTag>
    class vertex_property_map {
      typedef typename Graph::vertex_property_type Property;
      typedef typename Graph::graph_tag graph_tag;
      typedef typename vertex_property_selector<graph_tag>::type Selector;
      typedef typename Selector::template bind<Graph,Property,PropertyTag>
        Bind;
    public:
      typedef typename Bind::type type;
      typedef typename Bind::const_type const_type;
    };

    // This selects the kind of property map, whether is maps from
    // edges or from vertices.
    //
    // It is overly complicated because it's a workaround for
    // partial specialization.
    struct choose_vertex_property_map {
      template <class Graph, class Property>
      struct bind {
        typedef vertex_property_map<Graph, Property> type;
      };
    };
    struct choose_edge_property_map {
      template <class Graph, class Property>
      struct bind {
        typedef edge_property_map<Graph, Property> type;
      };
    };
    template <class Kind>
    struct property_map_kind_selector {
      // VC++ gets confused if this isn't defined, even though
      // this never gets used.
      typedef choose_vertex_property_map type;
    };
    template <> struct property_map_kind_selector<vertex_property_tag> {
      typedef choose_vertex_property_map type;
    };
    template <> struct property_map_kind_selector<edge_property_tag> {
      typedef choose_edge_property_map type;
    };
  } // namespace detail

  template <class Graph, class Property>
  struct property_map {
  private:
    typedef typename property_kind<Property>::type Kind;
    typedef typename detail::property_map_kind_selector<Kind>::type Selector;
    typedef typename Selector::template bind<Graph, Property> Bind;
    typedef typename Bind::type Map;
  public:
    typedef typename Map::type type;
    typedef typename Map::const_type const_type;
  };

  template <class Graph, class Property>
  class graph_property {
  public:
    typedef typename property_value<typename Graph::graph_property_type, 
      Property>::type type;
  };

} // namespace boost

#endif /* BOOST_GRAPH_PROPERTIES_HPPA */
