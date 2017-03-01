#ifndef MIN_FILL_FIRST_CLUSTER_HEURISTIC_H
#define MIN_FILL_FIRST_CLUSTER_HEURISTIC_H

#include "first_cluster_heuristic.h"
#include <climits>

class Min_Fill_First_Cluster_Heuristic: public First_Cluster_Heuristic
{

	public:
		// constructors and destructor
		Min_Fill_First_Cluster_Heuristic (Light_Graph * gs);	  // constructs a heuristic which chooses a clique (of the primal graph of the graphical structure gs)									
		
		// basic functions
		virtual pair<int,vertex *> Choose ();											// returns the first cluster for a tree-decomposition according to a heuristic method.
		virtual Cluster_Node * Choose (bool is_available[]);			// returns the first cluster for a tree-decomposition according to a heuristic method. This cluster must be connected and its vertices must be chosen among the vertices for which the flag is_available is set to true
		virtual First_Cluster_Heuristic * Duplicate ();						// returns a copy of the current heuristic
};

//-------------------------------
// definition of inline function
//-------------------------------

inline First_Cluster_Heuristic * Min_Fill_First_Cluster_Heuristic::Duplicate ()
// returns a copy of the current heuristic
{
	return new Min_Fill_First_Cluster_Heuristic (g);
}

#endif
