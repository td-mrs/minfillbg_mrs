/// \file 
/// \brief Definitions related to the Tie_Break_Min_Fill_Next_Vertices_Heuristic class

#ifndef TIE_BREAK_MIN_FILL_NEXT_VERTICES_HEURISTIC_H
#define TIE_BREAK_MIN_FILL_NEXT_VERTICES_HEURISTIC_H

#include "next_vertices_heuristic.h"
#include "tie_break_policy.h"

class Tie_Break_Min_Fill_Next_Vertices_Heuristic: public Next_Vertices_Heuristic    /// This class defines a heuristic which chooses as next vertices the vertices of a cluster of a min-fill tree-decomposition using a policy for breaking ties
{
	protected:
		Light_Graph * current_g;	///< a copy of the original graph in which selected separators are completed by adding all the required edges
		Tie_Break_Policy * tie_break_policy;
	
	public:
		// constructors and destructor
		Tie_Break_Min_Fill_Next_Vertices_Heuristic (Light_Graph * ref_g, Tie_Break_Policy * tbp);	///< constructs a heuristic which chooses a vertex in the neighborhood (w.r.t. the graph ref_g) of a set of vertices 
		~Tie_Break_Min_Fill_Next_Vertices_Heuristic ();										///< destructor
		
		// basic functions
		virtual void Choose (pair<int,vertex *> & vs, Cluster_Node * cl, pair<int,vertex *> & sep, int current_w, bool is_available[]);					///< selects some vertices from the vertex set vs (according to the heuristic policy) and adds them to the cluster cl. The selected vertices are removed from vs. According to the heuristic, the selected vertices may have some relation (e.g. neighborhood) with some vertices of the vertex sets aux_vs or sep
		virtual Next_Vertices_Heuristic * Duplicate ();				///< returns a copy of the current heuristic
};

//-------------------------------
// definition of inline function
//-------------------------------

inline Next_Vertices_Heuristic * Tie_Break_Min_Fill_Next_Vertices_Heuristic::Duplicate ()
// returns a copy of the current heuristic
{
	return new Tie_Break_Min_Fill_Next_Vertices_Heuristic (g,tie_break_policy);
}

#endif
