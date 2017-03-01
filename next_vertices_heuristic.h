/// \file 
/// \brief Definitions related to the Next_Vertices_Heuristic class

#ifndef NEXT_VERTICES_HEURISTIC_H
#define NEXT_VERTICES_HEURISTIC_H

#include "cluster_node.h"

class Next_Vertices_Heuristic     /// This class allows to represent heuristic for choosing the next vertices when computing tree-decompositions by heuristic methods
{
	protected:
		Light_Graph * g;		///< the original graph
	
	public:
		// constructor and destructor
		Next_Vertices_Heuristic (Light_Graph * ref_g);	///< constructor
		virtual ~Next_Vertices_Heuristic () {};					///< destructor
		
		// basic functions
		virtual pair<int,vertex *> Choose (pair<int,vertex *> & vs, pair<int,vertex *> & aux_vs, pair<int,vertex *> & sep, int current_w);	///< returns vertices of the vertex set vs as next vertices according to the heuristic policy. The selected vertices are removed from vs. According to the heuristic, the selected vertices may have some relation (e.g. neighborhood) with some vertices of the vertex sets aux_vs or sep
		virtual void Choose (pair<int,vertex *> & vs, Cluster_Node * cl, pair<int,vertex *> & sep, int current_w, bool is_available[])=0;		///< selects some vertices from the vertex set vs (according to the heuristic policy) and adds them to the cluster cl. The selected vertices are removed from vs. According to the heuristic, the selected vertices may have some relation (e.g. neighborhood) with some vertices of the vertex sets aux_vs or sep
		virtual Next_Vertices_Heuristic * Duplicate ()=0;			///< returns a copy of the current heuristic
};

#endif
