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
#include <iostream>
#include <vector>
#include <string>
#include <boost/graph/adjacency_list.hpp>
#include <boost/utility.hpp>

using namespace std;

/*
     Family Tree Example

           Jeanie
          /  |   \
    Debbie  Rick  John
     /       |      \
  Amanda   Margaret  Benjamin


  Sample Output:
    Jeanie is the parent of Debbie  Rick  John  
    Debbie is the parent of Amanda  
    Rick is the parent of Margaret  
    John is the parent of Benjamin  
    Amanda has no children
    Margaret has no children
    Benjamin has no children

*/

enum family { Jeanie, Debbie, Rick, John, Amanda, Margaret, Benjamin, N };

int main(int , char* []) 
{
  using namespace boost;
  using boost::tie;


  std::vector<std::string> name(N);
  name[Jeanie] = "Jeanie";
  name[Debbie] = "Debbie";
  name[Rick] = "Rick";
  name[John] = "John";
  name[Amanda] = "Amanda";
  name[Margaret] = "Margaret";
  name[Benjamin] = "Benjamin";

  adjacency_list<>  G(N);
  add_edge(Jeanie, Debbie, G);
  add_edge(Jeanie, Rick, G);
  add_edge(Jeanie, John, G);
  add_edge(Debbie, Amanda, G);
  add_edge(Rick, Margaret, G);
  add_edge(John, Benjamin, G);

  graph_traits<adjacency_list<> >::vertex_iterator i, end;
  graph_traits<adjacency_list<> >::adjacency_iterator ai, a_end;

  property_map<adjacency_list<>, vertex_index_t>::type
    id = get(vertex_index, G);

  for(tie(i, end) = vertices(G); i != end; ++i) {
    cout << name[get(id, *i)];
    tie(ai, a_end) = adjacent_vertices(*i, G);
    if (ai == a_end)
      cout << " has no children";
    else
      cout << " is the parent of ";
    for (; ai != a_end; ++ai)
      cout << name[get(id, *ai)] << "  ";
    cout << endl;
  }
  return 0;
}
