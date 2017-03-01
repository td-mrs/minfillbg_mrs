#include "tree_decomposition_triangulation.h"
#include <iostream>

//-----------------------------
// constructors and destructor
//-----------------------------


Tree_Decomposition_Triangulation::Tree_Decomposition_Triangulation (Light_Graph * gs) : Tree_Decomposition (gs)
// constructs an empty tree-decomposition related to the graphical structure gs
{
	T = 0;
}


Tree_Decomposition_Triangulation::~Tree_Decomposition_Triangulation ()
// destructor
{
	delete T;
}
