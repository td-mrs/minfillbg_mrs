/// \file 
/// \brief Definitions related to the Child_Node class

#ifndef CHILD_NODE_H
#define CHILD_NODE_H

#include <light_vector.h>
#include "cluster_node.h"
#include "vertex_set.h"

class Child_Node: public Vertex_Set   /// This class allows to represent the intersection between two clusters of a tree-decomposition
{
	protected:
		int cluster_num;                  ///< the number of the child cluster
		Cluster_Node * cluster;						///< a pointer on the child cluster whose number is cluster_num

	public:
		// constructors and destructor
		Child_Node (Light_Graph * gs);																	  ///< constructs an empty child node related to the graphical structure gs
		Child_Node (Light_Vector<vertex> element_set, Light_Graph * gs);	///< constructs a vertex set containing the vertices of element_set and related to the graphical structure gs
		Child_Node (Child_Node & cn);			                 	 ///< constructs a child node by copying the child node cn
		virtual ~Child_Node ();															 ///< destructor
		
		// operator
		Child_Node & operator= (const Child_Node & cn);   	 ///< operator =
		
		// basic functions on cluster node
		int Get_Cluster_Num (); 														 ///< returns the number of the child cluster
		Cluster_Node * Get_Cluster (); 											 ///< returns a pointer on the child cluster
		void Set_Cluster (Cluster_Node * cn); 							 ///< sets a pointer on the child cluster and the number of the child cluster
};

//-----------------------------
// inline function definitions
//-----------------------------

//-----------------
// basic functions
//-----------------

inline int Child_Node::Get_Cluster_Num ()
// returns the number of the child cluster
{
	return cluster_num;
}


inline Cluster_Node * Child_Node::Get_Cluster ()
// returns a pointer on the child cluster
{
	return cluster;
}


inline void Child_Node::Set_Cluster (Cluster_Node * cn)
// sets a pointer on the child cluster and the number of the child cluster
{
	cluster = cn;
	cluster_num = cn->Get_Num();
}

#endif

