/// \file 
/// \brief Definitions related to the Tie_Break_Min_Fill_Triangulation class

#ifndef TIE_BREAK_MIN_FILL_TRIANGULATION_H
#define TIE_BREAK_MIN_FILL_TRIANGULATION_H

#include "tie_break_policy.h"
#include "triangulation.h"

class Tie_Break_Min_Fill_Triangulation: public Triangulation  		 /// This class allows to triangulate graphs thanks to the Min-Fill algorithm with a specific policy for breaking ties
{
	protected:
		Tie_Break_Policy * tie_break_policy;			///< the policy used for breaking ties
	
	public:
		// constructors and destructor
		Tie_Break_Min_Fill_Triangulation (Light_Graph * g_init, Tie_Break_Policy * tbp);	 ///< constructs a triangulation from a graph
		~Tie_Break_Min_Fill_Triangulation ();		 						       ///< destructor
	
	private :
		// function for triangulating the graph
		virtual void Triangulate ();  					 		 ///< triangulates the graph thanks to the Min-Fill algorithm
};

#endif
