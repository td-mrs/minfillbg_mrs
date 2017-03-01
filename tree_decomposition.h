/// \file 
/// \brief Definitions related to the Tree_Decomposition class

#ifndef TREE_DECOMPOSITION_H
#define TREE_DECOMPOSITION_H

#include <light_vector.h>
#include "order.h"
#include "cluster_tree.h"
#include "light_graph.h"

class Tree_Decomposition                        /// This class allows to represent tree-decompositions of graphical structures (see [Robertson and Seymour, 1986])
{
	protected:
		Light_Graph * g;										///< the graphical structure to which the tree-decomposition refers
		Light_Vector<Cluster_Tree *> cluster_tree;	///< the cluster trees of the tree-decomposition (we consider a cluster tree per connected componed of the graphical structure g)
		int ct_number;															///< the number of cluster trees of the tree-decomposition
		
	public:
		// constructors and destructor
		Tree_Decomposition (Light_Graph * gs);		      ///< constructs an empty tree-decomposition related to the graphical structure gs
		Tree_Decomposition (Tree_Decomposition & td);			      ///< constructs a tree-decomposition by copying the tree-decomposition td
		virtual ~Tree_Decomposition ();													///< destructor
		
		// operator
		Tree_Decomposition & operator= (Tree_Decomposition & td); 	///< operator =
		
		// basic functions on cluster tree
		int Get_W ();											///< returns the width of the tree-decomposition
		int Nb_Clusters ();							  ///< returns the number of clusters of the tree-decomposition
		int Get_Max_Label ();							///< returns the largest label of clusters for all the cluster trees
		int Get_Cluster_Tree_Number();		///< returns the number of cluster trees of the considered tree-decomposition
		Cluster_Tree * Get_Cluster_Tree (int i);					///< returns the i th cluster tree of the considered tree-decomposition
		Light_Graph * Get_Light_Graph ();	///< returns the graphical structure to which the tree-decomposition is related

		// function computing cluster trees
		virtual void Make_Tree (pair<int,Light_List<Cluster_Node *> > lc);		///< makes a tree from the cluster list lc
};


//-----------------------------
// inline function definitions
//-----------------------------

//-----------------
// basic functions 
//-----------------


inline int Tree_Decomposition::Get_Cluster_Tree_Number()
// returns the number of cluster trees of the considered tree-decomposition
{
	return ct_number;
}


inline Cluster_Tree * Tree_Decomposition::Get_Cluster_Tree (int i)
// returns the i th cluster tree of the considered tree-decomposition
{
	if (i < ct_number)	return cluster_tree[i];
	else return 0;
}


inline Light_Graph * Tree_Decomposition::Get_Light_Graph ()
// returns the graphical structure to which the tree-decomposition is related
{
	return g;
}

#endif
