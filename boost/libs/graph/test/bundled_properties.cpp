// Boost Graph library

//  Copyright Douglas Gregor 2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/minimal.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/filtered_graph.hpp>
#include <boost/graph/subgraph.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace boost;

struct City
{
  City() {}
  City(const std::string& name, int pop, int zipcode) : name(name), population(pop)
  { 
    zipcodes.push_back(zipcode); 
  }

  string name;
  int population;
  vector<int> zipcodes;
};

struct Highway
{
  Highway() {}
  Highway(const string& name, double miles, int speed_limit = 65, int lanes = 4, bool divided = true) 
    : name(name), miles(miles), speed_limit(speed_limit), lanes(lanes), divided(divided) {}

  string name;
  double miles;
  int speed_limit;
  int lanes;
  bool divided;
};

template<bool> struct truth {};

template<typename Map, typename VertexIterator, typename Bundle>
typename boost::graph_traits<Map>::vertex_descriptor 
do_add_vertex(Map& map, VertexIterator, const Bundle& bundle, truth<true>)
{
  return add_vertex(bundle, map);
}

template<typename Map, typename VertexIterator, typename Bundle>
typename boost::graph_traits<Map>::vertex_descriptor 
do_add_vertex(Map& map, VertexIterator& vi, const Bundle& bundle, truth<false>)
{
  get(boost::vertex_bundle, map)[*vi] = bundle;
  return *vi++;
}


template<typename Map, bool CanAddVertex>
void test_bundled_properties(Map*, truth<CanAddVertex> can_add_vertex)
{
  typedef typename boost::graph_traits<Map>::vertex_iterator   vertex_iterator;
  typedef typename boost::graph_traits<Map>::vertex_descriptor vertex_descriptor;
  typedef typename boost::graph_traits<Map>::edge_descriptor   edge_descriptor;

  Map map(3);

  vertex_iterator vi = vertices(map).first;
  vertex_descriptor v = *vi;
  map[v].name = "Troy";
  map[v].population = 49170;
  map[v].zipcodes.push_back(12180);

  ++vi;
  vertex_descriptor u = *vi++;
  map[u].name = "Albany";
  map[u].population = 95658;
  map[u].zipcodes.push_back(12201);

  // Try adding a vertex with a property value
  vertex_descriptor bloomington = do_add_vertex(map, vi, City("Bloomington", 39000, 47401),
                                                can_add_vertex);
  BOOST_CHECK(get(boost::vertex_bundle, map)[bloomington].zipcodes[0] == 47401);
  
  edge_descriptor e = add_edge(v, u, map).first;
  map[e].name = "I-87";
  map[e].miles = 10;
  map[e].speed_limit = 65;
  map[e].lanes = 4;
  map[e].divided = true;

  edge_descriptor our_trip = add_edge(v, bloomington, Highway("Long haul", 1000), map).first;
  BOOST_CHECK(get(boost::edge_bundle, map, our_trip).miles == 1000);
  
  BOOST_CHECK(get(get(&City::name, map), v) == "Troy");
  BOOST_CHECK(get(get(&Highway::name, map), e) == "I-87");
  BOOST_CHECK(get(&City::name, map, u) == "Albany");
  BOOST_CHECK(get(&Highway::name, map, e) == "I-87");
  put(&City::population, map, v, 49168);
  BOOST_CHECK(get(&City::population, map)[v] == 49168);
  
  boost::filtered_graph<Map, boost::keep_all> fmap(map, boost::keep_all());
  BOOST_CHECK(get(boost::edge_bundle, map, our_trip).miles == 1000);
  
  BOOST_CHECK(get(get(&City::name, fmap), v) == "Troy");
  BOOST_CHECK(get(get(&Highway::name, fmap), e) == "I-87");
  BOOST_CHECK(get(&City::name, fmap, u) == "Albany");
  BOOST_CHECK(get(&Highway::name, fmap, e) == "I-87");
  put(&City::population, fmap, v, 49169);
  BOOST_CHECK(get(&City::population, fmap)[v] == 49169);

}

void test_subgraph_bundled_properties()
{
  typedef boost::subgraph<
            boost::adjacency_list<boost::vecS, boost::vecS, 
                                  boost::bidirectionalS, City, 
                                  boost::property<boost::edge_index_t, int,
                                                  Highway> > > SubMap;
  typedef boost::graph_traits<SubMap>::vertex_descriptor Vertex;
  typedef boost::graph_traits<SubMap>::vertex_iterator vertex_iterator;

  SubMap map(3);
  vertex_iterator vi = vertices(map).first;
  Vertex troy = *vi++;
  map[troy].name = "Troy";
  map[*vi++].name = "Bloomington";
  map[*vi++].name = "Endicott";

  SubMap& g1 = map.create_subgraph();
  Vertex troy1 = add_vertex(*vertices(map).first, g1);
  BOOST_CHECK(map[troy1].name == g1[troy1].name);
}

int test_main(int, char*[])
{
  typedef boost::adjacency_list<
    boost::listS, boost::vecS, boost::bidirectionalS,
    City, Highway> Map1;
  typedef boost::adjacency_matrix<boost::directedS,
    City, Highway> Map2;

  test_bundled_properties(static_cast<Map1*>(0), truth<true>());
  test_bundled_properties(static_cast<Map2*>(0), truth<false>());
  test_subgraph_bundled_properties();
  return 0;
}
