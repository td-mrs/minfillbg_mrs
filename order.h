/// \file 
/// \brief Definitions related to the Order class

#ifndef ORDER_H
#define ORDER_H

#include <light_vector.h>
#include "light_graph.h"
using namespace std;


class Order           /// This class allows to represent vertex orderings
{
	private : 
		Light_Vector<int> order;           ///< provides the position of a vertex
		Light_Vector<vertex> rev_order;    ///< provides the vertex related to a position
		unsigned int n;						      	 ///< number of vertices in the order

  public :
  	// constructors and destructor
  	Order ();	       					 							///< constructs an empty order with 0 vertex
		Order (Order & o);	            				///< constructs an order by copying the order o
		~Order ();		 					  		  				///< destructor

		// operator
		Order & operator= (const Order & o);    ///< operator =
		
    // basic operations or functions on order
		void Init (unsigned int nb_vertices);		///< initializes the order with n vertices
		vertex Get_Vertex (int pos);            ///< returns the vertex at position pos
		int Get_Position (vertex x);            ///< returns the position of the vertex x
		void Set_Position (vertex x, int pos);  ///< puts the vertex x at the position pos
		int Width (Light_Graph * g);						///< computes the width of the order w.r.t. the graph g
		
		// output function;
		void Print ();   												///< prints the order and the reverse order
		
		// specific function for triangulated graphs
		bool Is_peo (Light_Graph * g);          ///< returns true if the order is a perfect elimination order of the graph g
};


//-----------------------------
// inline function definitions
//-----------------------------


//-----------------
// basic functions
//-----------------


inline vertex Order::Get_Vertex (int pos)
// returns the vertex at position pos
{
	if ((pos >= 0) && ((unsigned) pos < n))  return rev_order[pos];
	else return -1;
}


inline int Order::Get_Position (vertex x)
// returns the position of the vertex x
{
	if ((x >= 0) && (x < n))  return order[x];
	else return -1;
}

#endif
