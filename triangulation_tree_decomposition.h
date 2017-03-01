/// \file 
/// \brief Definitions related to the Triangulation_Tree_Decomposition class

#ifndef TRIANGULATION_TREE_DECOMPOSITION_H
#define TRIANGULATION_TREE_DECOMPOSITION_H

#include "tree_decomposition.h"
#include "triangulation.h"
#include <light_list.h>


class Triangulation_Tree_Decomposition : public Tree_Decomposition   /// This class allows to represent tree-decompositions of graphical structures based on triangulation
{	
	protected:
		Triangulation * T;      ///< the considered triangulation
	
	public:
		// constructors and destructor
		Triangulation_Tree_Decomposition (Light_Graph * gs);	///< constructs an empty tree-decomposition related to the graphical structure gs
		virtual ~Triangulation_Tree_Decomposition ();									///< destructor

		// accessor to the related triangulation
		Triangulation * Get_Triangulation ();					///< returns the triangulation used for computing the tree-decomposition
};


//-----------------------------
// inline function definitions
//-----------------------------

//---------------------------------------
// accessor to the related triangulation
//---------------------------------------


inline Triangulation * Triangulation_Tree_Decomposition::Get_Triangulation ()
// returns the triangulation used for computing 
{
	return T;
}

#endif

