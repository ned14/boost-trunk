//-*-c++-*-
//=======================================================================
// Copyright 1997-2001 University of Notre Dame.
// Authors: Lie-Quan Lee
//
// This file is part of the Boost Graph Library
//
// You should have received a copy of the License Agreement for the
// Generic Graph Component Library along with the software;  see the
// file LICENSE.  If not, contact Office of Research, University of Notre
// Dame, Notre Dame, IN  46556.
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

/*
  This file is to demo how to use minimum_degree_ordering algorithm.
  
  Important Note: This implementation requires the BGL graph to be
  directed.  Therefore, nonzero entry (i, j) in a symmetrical matrix
  A coresponds to two directed edges (i->j and j->i).

  The bcsstk01.rsa is an example graph in Harwell-Boeing format,
  and bcsstk01 is the ordering produced by Liu's MMD implementation.
  Link this file with iohb.c to get the harwell-boeing I/O functions.
  To run this example, type:

  ./minimum_degree_ordering bcsstk01.rsa bcsstk01

*/

#include <fstream>
#include <iostream>
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/graph_utility.hpp"
#include "boost/graph/minimum_degree_ordering.hpp"
#include "iohb.h"

//copy and modify from mtl harwell boeing stream 
struct harwell_boeing
{
  harwell_boeing(char* filename) {
    int Nrhs;
    char* Type;
    Type = new char[4];
    isComplex = false;
    readHB_info(filename, &M, &N, &nonzeros, &Type, &Nrhs);
    colptr = (int *)malloc((N+1)*sizeof(int));
    if ( colptr == NULL ) IOHBTerminate("Insufficient memory for colptr.\n");
    rowind = (int *)malloc(nonzeros*sizeof(int));
    if ( rowind == NULL ) IOHBTerminate("Insufficient memory for rowind.\n");

    if ( Type[0] == 'C' ) {
      isComplex = true;
      val = (double *)malloc(nonzeros*sizeof(double)*2);
      if ( val == NULL ) IOHBTerminate("Insufficient memory for val.\n");

    } else {
      if ( Type[0] != 'P' ) {   
	val = (double *)malloc(nonzeros*sizeof(double));
	if ( val == NULL ) IOHBTerminate("Insufficient memory for val.\n");
      }
    }

    readHB_mat_double(filename, colptr, rowind, val);

    cnt = 0;
    col = 0;
    delete [] Type;
  }

  ~harwell_boeing() {
    free(colptr);
    free(rowind);
    free(val);
  }

  inline int nrows() const { return M; }

  int cnt;
  int col; 
  int* colptr;
  bool isComplex;
  int M;
  int N;
  int nonzeros;
  int* rowind;
  double* val;
};

int main(int argc, char* argv[]) 
{
  using namespace std;
  using namespace boost;

  if (argc < 2) {
    cout << argv[0] << " HB file"  << endl;
    return -1;
  }

  int delta = 0;

  if ( argc >= 4 )
  delta = atoi(argv[3]);
  
  typedef double Type;
 
  harwell_boeing hbs(argv[1]);

  //must be BGL directed graph now
  typedef adjacency_list<vecS, vecS, directedS>  Graph;
  typedef graph_traits<Graph>::vertex_descriptor Vertex;

  int n = hbs.nrows();

  cout << "n is " << n << endl;

  Graph G(n);

  int num_edge = 0;

  for (int i = 0; i < n; ++i)
    for (int j = hbs.colptr[i]; j < hbs.colptr[i+1]; ++j)
      if ( (hbs.rowind[j - 1] - 1 ) > i ) {
	add_edge(hbs.rowind[j - 1] - 1, i, G);
	add_edge(i, hbs.rowind[j - 1] - 1, G);
	num_edge++;
      }

  cout << "number of off-diagnal elements: " << num_edge << endl;
 
  typedef std::vector<int> Vector;

  Vector inverse_perm(n, 0);
  Vector perm(n, 0);

  Vector supernode_sizes(n, 1); // init has to be 1

  boost::property_map<Graph, vertex_index_t>::type 
    id = get(vertex_index, G);

  Vector degree(n, 0);

  minimum_degree_ordering
    (G,
     make_iterator_property_map(&degree[0], id, degree[0]),
     &inverse_perm[0],
     &perm[0],
     make_iterator_property_map(&supernode_sizes[0], id, supernode_sizes[0]), 
     delta, id);

  if ( argc >= 3 ) {
    ifstream  input(argv[2]);
    if ( input.fail() ) {
      cout << argv[3] << " is failed to open!. " << endl;
      return -1;
    }
    int comp;
    bool is_correct = true;
    int i;
    for ( i=0; i<n; i++ ) {
      input >> comp;
      if ( comp != inverse_perm[i]+1 ) {
	cout << "at i= " << i << ": " << comp
	     << " ***is NOT EQUAL to*** " << inverse_perm[i]+1 << endl;
	is_correct = false;
      }      
    }
    for ( i=0; i<n; i++ ) {
      input >> comp;
      if ( comp != perm[i]+1 ) {
	cout << "at i= " << i << ": " << comp
	     << " ***is NOT EQUAL to*** " << perm[i]+1 << endl;
	is_correct = false;
      }
    }
    if ( is_correct ) 
      cout << "Permutation and inverse permutation are correct. "<< endl;
    else 
      cout << "WARNING -- Permutation or inverse permutation is not the "
	   << "same ones generated by Liu's " << endl;
    
  }
  return 0;
}
