/// \file 
/// \brief Definitions related to the Triangulation class

#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include "order.h"
#include "cluster_node.h"
#include <light_list.h>

class Triangulation        /// This class allows to define triangulation operations
{
	protected :
		int nb_added_edges;    ///< number of edges which are added during the triangulation
		Light_Graph * g;			 ///< the obtained graph after having triangulated the original graph
		Order * peo;					 ///< a perfect elimination order related to triangulated graph
		
	public :
		// constructors and destructor
		Triangulation (Light_Graph * g_init);		 ///< construct a triangulation from a graph
		virtual ~Triangulation ();					 		 ///< destructor
		
		// basic operations or functions on triangulation
		int Get_Nb_Added_Edges (); 				 														///< returns the number of edges added during the triangulation
		Light_Graph * Get_Triangulated_Graph (); 											///< returns the graph obtained after the triangulation
		Order * Get_Peo_Order (); 			   														///< returns a perfect elimination order related to triangulated graph
		virtual pair<int,Light_List<Cluster_Node *> > Clique_List ();	///< computes the list of the maximal cliques of the triangulated graph g by using the perfect elimination order o

	private :	
		// function for triangulating the graph
		virtual void Triangulate ()=0; 	     ///< triangulates the graph g
};


//-----------------------------
// inline function definitions
//-----------------------------


//-----------------
// basic functions
//-----------------


inline int Triangulation::Get_Nb_Added_Edges ()
// returns the number of edges added during the triangulation
{
	return nb_added_edges;
}


inline Light_Graph * Triangulation::Get_Triangulated_Graph ()
// returns the graph obtained after the triangulation
{
	return g;
}


inline Order * Triangulation::Get_Peo_Order ()
// returns a perfect elimination order related to triangulated graph
{
	return peo;
}

#endif
