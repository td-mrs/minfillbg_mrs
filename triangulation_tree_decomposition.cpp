#include "triangulation_tree_decomposition.h"
#include <iostream>

//-----------------------------
// constructors and destructor
//-----------------------------


Triangulation_Tree_Decomposition::Triangulation_Tree_Decomposition (Light_Graph * gs) : Tree_Decomposition (gs)
// constructs an empty tree-decomposition related to the graphical structure gs
{
	T = 0;
}


Triangulation_Tree_Decomposition::~Triangulation_Tree_Decomposition ()
// destructor
{
	delete T;
}
