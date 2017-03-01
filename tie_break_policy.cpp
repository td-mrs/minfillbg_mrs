#include "tie_break_policy.h"


//----------------------------
// constructor and destructor
//----------------------------


Tie_Break_Policy::Tie_Break_Policy (unsigned int n)
// constructs a tie-break policy with at most n ex aequo values
{
	exaequo = new int [n];
	nb = 0;
}


Tie_Break_Policy::~Tie_Break_Policy ()
// destructor
{
	delete [] exaequo;
}
