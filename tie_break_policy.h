/// \file 
/// \brief Definitions related to the Tie_Break_Policy class

#ifndef TIE_BREAK_POLICY_H
#define TIE_BREAK_POLICY_H

#include "order.h"

class Tie_Break_Policy  		 /// This class allows to represent policies for breaking ties
{
	protected:
		int * exaequo;		///< the ex aequo values
		int nb;						///< the number of ex aequo values
	
	public:
		// constructor and destructor
		Tie_Break_Policy (unsigned int n);		///< constructs a tie-break policy with at most n ex aequo values
		virtual ~Tie_Break_Policy ();				 	///< destructor
		
		// basic functions
		virtual void Reset ();						///< deletes all the ex aequo values
		void Add (int j);									///< adds the values to the ex aequo values
		virtual int Choose (Light_Graph * g, vertex * candidates, Order * peo) = 0;			///< chooses a vertex according to the chosen policy
		virtual int Choose (Light_Graph * g, vertex * candidates, bool is_untreated []) = 0;			///< chooses a vertex according to the chosen policy
};


// definition of inline functions

inline void Tie_Break_Policy::Reset ()
// deletes all the ex aequo values
{
	nb = 0;
}


inline void Tie_Break_Policy::Add (int j)
// adds the values to the ex aequo values
{
	exaequo[nb] = j;
	nb++;
}

#endif
