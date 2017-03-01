/// \file 
/// \brief Definitions related to the Tie_Break_Partial_Min_Fill_Triangulation class

#ifndef TIE_BREAK_PARTIAL_MIN_FILL_TRIANGULATION_H
#define TIE_BREAK_PARTIAL_MIN_FILL_TRIANGULATION_H

#include "triangulation.h"
#include "tie_break_policy.h"

class Tie_Break_Partial_Min_Fill_Triangulation: public Triangulation    /// This class allows to triangulate a part of graph thanks to the Min-Fill algorithm using a policy for breaking ties
{	
	protected:
		int * is_available;			///< is_available[x] is set to 0 if x must be ignored, 1 if x may be considerd or 2 if x must be considered
		int remaining_vertices;	///< the number of vertices which must be considered
		Tie_Break_Policy * tie_break_policy;			///< the policy used for breaking ties
	
	public :
		// constructors and destructor
		Tie_Break_Partial_Min_Fill_Triangulation (Light_Graph * g_init, int available [], Tie_Break_Policy * tbp);	 ///< constructs a triangulation from a graph
		~Tie_Break_Partial_Min_Fill_Triangulation ();		 						 ///< destructor
	
	private :	
		// function for triangulating the graph
		virtual void Triangulate ();  					 										  ///< triangulates the graph induced by the vertices which are set to true in is_available thanks to the Min-Fill algorithm
};

#endif

