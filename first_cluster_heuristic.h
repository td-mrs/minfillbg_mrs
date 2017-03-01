/// \file 
/// \brief Definitions related to the First_Cluster_Heuristic class

#ifndef FIRST_CLUSTER_HEURISTIC_H
#define FIRST_CLUSTER_HEURISTIC_H

#include "cluster_node.h"

class First_Cluster_Heuristic         /// This class allows to represent heuristics for choosing the first cluster when computing tree-decompositions by heuristic methods
{
	protected:
		Light_Graph * g;          ///< the graphical structure we want to decompose
		
	public:
		// destructor
		virtual ~First_Cluster_Heuristic () {};							 					///< destructor
		
		// basic functions
		virtual pair<int,vertex *> Choose () = 0;											///< returns the first cluster for a tree-decomposition according to a heuristic method. This cluster must be connected
		virtual Cluster_Node * Choose (bool is_available[]) = 0;			///< returns the first cluster for a tree-decomposition according to a heuristic method. This cluster must be connected and its vertices must be chosen among the vertices for which the flag is_available is set to true. For each selected vertex, is_available is set to false
		virtual First_Cluster_Heuristic * Duplicate () = 0;						///< returns a copy of the current heuristic
};

#endif

