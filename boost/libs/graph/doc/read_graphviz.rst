============================
|(logo)|__ ``read_graphviz``
============================

.. |(logo)| image:: ../../../boost.png
   :align: middle
   :alt: Boost

__ ../../../index.htm

::

  template <typename MutableGraph>
  bool read_graphviz(std::istream& in, MutableGraph& graph,
		     dynamic_properties& dp, 
                     const std::string& node_id = "node_id");

  // Only available if BOOST_GRAPH_READ_GRAPHVIZ_ITERATORS is defined
  template <typename MultiPassIterator, typename MutableGraph>
  bool read_graphviz(MultiPassIterator begin, MultiPassIterator end,
		     MutableGraph& graph, dynamic_properties& dp, 
                     const std::string& node_id = "node_id");

  // Deprecated GraphViz readers
  void read_graphviz(const std::string& file, GraphvizDigraph& g);
  void read_graphviz(FILE* file, GraphvizDigraph& g);
  void read_graphviz(const std::string& file, GraphvizGraph& g);
  void read_graphviz(FILE* file, GraphvizGraph& g);

 
The ``read_graphviz`` function interprets a graph described using the
GraphViz_ DOT language and builds a BGL graph that captures that
description.  Using this function, you can initialize a graph using
data stored as text. To use the iterator version of ``read_graphviz``,
you will need to define the macro BOOST_GRAPH_READ_GRAPHVIZ_ITERATORS
before including the header ``<boost/graph/graphviz.hpp>``. Doing so
may greatly increase the amount of time required to compile the
GraphViz reader.

The DOT language can specify both directed and undirected graphs, and
``read_graphviz`` differentiates between the two. One must pass
``read_graphviz`` an undirected graph when reading an undirected graph;
the same is true for directed graphs. Furthermore, ``read_graphviz``
will throw an exception if it encounters parallel edges and cannot add
them to the graph.

To handle properties expressed in the DOT language, ``read_graphviz``
takes a dynamic_properties_ object and operates on its collection of
property maps.  The reader passes all the properties encountered to
this object, using the GraphViz string keys as the property keys.
Furthermore, ``read_graphviz`` stores node identifier names under the
vertex property map named node_id. 

Requirements:
 - The type of the graph must model the `Mutable Graph`_ concept.
 - The type of the iterator must model the `Multi-Pass Iterator`_
   concept.
 - The property map value types must be default-constructible.


.. contents::

Where Defined
-------------
``<boost/graph/graphviz.hpp>``

Exceptions
----------

::

  struct graph_exception : public std::exception {
    virtual ~graph_exception() throw();
    virtual const char* what() const throw() = 0;
  };

  struct bad_parallel_edge : public graph_exception {
    std::string from;
    std::string to;

    bad_parallel_edge(const std::string&, const std::string&);
    virtual ~bad_parallel_edge() throw();
    const char* what() const throw();
  };

  struct directed_graph_error : public graph_exception {
    virtual ~directed_graph_error() throw();
    virtual const char* what() const throw();
  };

  struct undirected_graph_error : public graph_exception {
    virtual ~undirected_graph_error() throw();
    virtual const char* what() const throw();
  };

Under certain circumstances, ``read_graphviz`` will throw one of the
above exceptions.  The three concrete exceptions can all be caught
using the general ``graph_exception`` moniker when greater precision
is not needed.  In addition, all of the above exceptions derive from
the standard ``std::exception`` for even more generalized error
handling.

The ``bad_parallel_edge`` exception is thrown when an attempt to add a
parallel edge to the supplied MutableGraph fails.  The DOT language
supports parallel edges, but some BGL-compatible graph types do not.
One example of such a graph is ``boost::adjacency_list<setS,vecS>``,
which allows at most one edge can between any two vertices.


The ``directed_graph_error`` exception occurs when an undirected graph
type is passed to ``read_graph`` but the textual representation of the
graph is directed, as indicated by the ``digraph`` keyword in the DOT
language.

The ``undirected_graph_error`` exception occurs when a directed graph
type is passed to ``read_graph`` but the textual representation of the
graph is undirected, as indicated by the ``graph`` keyword in the DOT
language.


Building the GraphViz Readers
-----------------------------
To use the GraphViz readers, you will need to build and link against
the "bgl-viz" library. The library can be built by following the
`Boost Jam Build Instructions`_ for the subdirectory ``libs/graph/build``.

Deprecated Readers
------------------
The deprecated readers do not provide exceptions on error (they
abort), they require the use of one of the predefined graph types
(``GraphvizDigraph`` or ``GraphvizGraph``), and they do not support
arbitrary properties. They will be removed in a future Boost version.


Notes
-----

 - The ``read_graphviz`` function does not use any code from the
   GraphViz distribution to interpret the DOT Language.  Rather, the
   implementation was based on documentation found on the GraphViz web
   site, as well as experiments run using the dot application.  The
   resulting interpretation may be subtly different from dot for some
   corner cases that are not well specified.

 - ``read_graphviz`` treats subgraphs as syntactic sugar.  It does not
   reflect subgraphs as actual entities in the BGL.  Rather, they are
   used to shorten some edge definitions as well as to give a subset
   of all nodes or edges certain properties. For example, the
   DOT graphs ``digraph { a -> subgraph {b -> c} -> e }`` and 
   ``digraph { a -> b -> e ; a -> c -> e ; b -> c}`` are equivalent.

 - Subgraph IDs refer to subgraphs defined earlier in the graph
   description.  Undefined subgraphs behave as empty subgraphs
   (``{}``).

 - On successful reading of a graph, every vertex and edge will have
   an associated value for every respective edge and vertex property
   encountered while interpreting the graph.  These values will be set
   using the ``dynamic_properties`` object.  Some properties may be
   ``put`` multiple times during the course of reading in order to
   ensure the same semantics as the GraphViz tools.  Those edges and
   vertices that are not explicitly given a value for a property (and that
   property has no default) will be
   given the default constructed value of the value type.  **Be sure
   that property map value types are default constructible.**

See Also
--------

write_graphviz_


Future Work
-----------

 - Currently the parser relies upon lowercase language keywords
   (i.e. "graph", "edge", etc.).  The DOT Language specifies that they
   are case-insensitive.  This change should be easy given the proper
   understanding of Spirit and some free time (hint hint!)

 - The parser currently does not handle continuation lines as defined
   in the DOT Language.  Some more sophisticated parsing of
   identifier(so-called "ID" in the source) is required to support this.

 

.. _GraphViz: http://graphviz.org/
.. _`Mutable Graph`: MutableGraph.html
.. _`Multi-Pass Iterator`: ../../iterator/index.html
.. _dynamic_properties: ../../property_map/doc/dynamic_property_map.html
.. _write_graphviz: write-graphviz.html
.. _Boost Jam Build Instructions: ../../../more/getting_started.html#Build_Install
