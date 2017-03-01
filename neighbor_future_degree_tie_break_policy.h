/// \file 
/// \brief Definitions related to the Degree_Tie_Break_Policy class

#ifndef NEIGHBOR_FUTURE_DEGREE_TIE_BREAK_POLICY_H
#define NEIGHBOR_FUTURE_DEGREE_TIE_BREAK_POLICY_H

#include "tie_break_policy.h"

class Neighbor_Future_Degree_Tie_Break_Policy: public Tie_Break_Policy  		 /// This class implements a policy exploiting the future degrees for breaking ties
{
	protected:
		int stamp;							///< the stamp which allows to compute degrees only if needed
		int * last_compute;			///< the last time the degree of a given vertex has been computed
		unsigned int * futdeg;	///< the future degree of each vertex (i.e. the number of unnumbered neighbors)
		
	public:
		// constructor and destructor
		Neighbor_Future_Degree_Tie_Break_Policy (unsigned n);			///< constructs a tie-break policy with at most n ex aequo values
		~Neighbor_Future_Degree_Tie_Break_Policy ();							///< destructor
		
		// basic functions
		virtual void Reset ();						///< deletes all the ex aequo values
		virtual int Choose (Light_Graph * g, vertex * candidates, Order * peo);							///< chooses a vertex according to the chosen policy
		virtual int Choose (Light_Graph * g, vertex * candidates, bool is_untreated []);		///< chooses a vertex according to the chosen policy
};


// definition of inline function

inline void Neighbor_Future_Degree_Tie_Break_Policy::Reset ()
{
	stamp++;
	nb = 0;
}

#endif
