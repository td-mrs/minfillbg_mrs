/// \file 
/// \brief Definitions related to the Cluster_Tree class

#ifndef CLUSTER_TREE_H
#define CLUSTER_TREE_H

#include <map>
#include <deque>
#include "order.h"
#include "cluster_node.h"
#include "child_node.h"

class Cluster_Tree          /// This class allows to represent cluster-trees which are parts of the tree-decompositions
{
	protected:
		map<int,deque<Child_Node *> > adjacency_list;  ///< the tree represented as a graph
		map<int,Cluster_Node *> cluster_list;  	     	 ///< the list of clusters in the cluster tree
		Cluster_Node * root;											     ///< the number of the root of the cluster tree
		int root_num;															     ///< the number of the root of the cluster tree
		int nb_clusters;       								  	     ///< the number of clusters of the cluster tree
		int max_label;																 ///< the largest label related to a cluster
		int nb_vertices;															 ///< the number of vertices of the cluster tree
		Light_Graph * g;   										 ///< the graphical structure to which the tree-decomposition is related

	public:
		// constructors and destructor
		Cluster_Tree (Light_Graph * gs);				  		  ///< constructs an empty cluster tree
		Cluster_Tree (Cluster_Tree & ct);			                  ///< constructs a cluster tree by copying the cluster tree ct
		virtual ~Cluster_Tree ();															  ///< destructor
		
		// operator
		Cluster_Tree & operator= (Cluster_Tree & ct); 			    ///< operator =
		
		// iterators
		map<int,Cluster_Node *>::iterator Begin_List ();				///< returns an iterator referring to the first cluster
		map<int,Cluster_Node *>::iterator End_List ();					///< returns an iterator referring to the position after the last cluster
		deque<Child_Node *>::iterator Begin_Neighbor (int num); ///< returns an iterator referring to the first neighbor of the cluster num
		deque<Child_Node *>::iterator End_Neighbor (int num);   ///< returns an iterator referring to the position after the last neighbor of the cluster num
		
		// basic functions on cluster tree
		int Get_Nb_Vertices ();																	///< returns the number of vertices of the cluster tree
		int Nb_Clusters ();																		  ///< returns the number of clusters of the cluster tree
		int Get_Max_Label ();																		///< returns the largest label of clusters of the cluster tree
		Cluster_Node * Get_Cluster (int num);									  ///< returns the cluster num if it exists
		void Add_Cluster (Cluster_Node * cn, bool duplicate = false);				///< adds a cluster to the cluster tree without connecting it to the existing cluster tree (the cluster is duplicated if duplicate is true)
		void Add_Child_Node (int lp, int lc);									 							///< adds two child nodes in the cluster tree such that lc is the label of the child cluster and lp is the label of the parent cluster
		void Add_Child_Node (Cluster_Node * parent, Cluster_Node * child);	///< adds two child nodes in the cluster tree such that child is a pointer on the child cluster and parent is a pointer on the parent cluster

		Cluster_Node * Get_Root ();														  ///< returns the root cluster
		int Get_Root_Num ();																	  ///< returns the number root cluster
		void Set_Root (int root_label);												  ///< sets the cluster whose label is root_label as root cluster of the cluster tree
		void Set_Root (Cluster_Node * root_cluster);					  ///< sets the cluster root_cluster as root cluster of the cluster tree
		Vertex_Set Get_Descent (int num); 										  ///< returns the set of vertices which belong to the descent rooted in the cluster num
		void Print ();																				  ///< prints the cluster tree
		
		// functions computing cluster trees
		void Clique_Tree (Light_Graph * g, Order * o);				  ///< computes the cluster tree from the maximal cliques of the triangulated graph g by using the perfect elimination order o
		void Make_Tree ();																			///< makes a tree from the clusters		
};


//-----------------------------
// inline function definitions
//-----------------------------

//-----------
// iterators
//-----------


inline map<int,Cluster_Node *>::iterator Cluster_Tree::Begin_List ()
// returns an iterator referring to the first cluster
{
	return cluster_list.begin();
}


inline map<int,Cluster_Node *>::iterator Cluster_Tree::End_List ()
// returns an iterator referring to the position after the last cluster
{
	return cluster_list.end();
}		
		

inline deque<Child_Node *>::iterator Cluster_Tree::Begin_Neighbor (int num)
// returns an iterator referring to the first neighbor of the cluster num
{
	return adjacency_list.find(num)->second.begin();
}


inline deque<Child_Node *>::iterator Cluster_Tree::End_Neighbor (int num)
// returns an iterator referring to the position after the last neighbor of the cluster num
{
	return adjacency_list.find(num)->second.end();
}


//-----------------
// basic functions 
//-----------------


inline int Cluster_Tree::Get_Nb_Vertices ()
// returns the number of vertices of the cluster tree
{
	if (nb_vertices == 0)
	{
		for (map<int,Cluster_Node *>::iterator iter = cluster_list.begin(); iter != cluster_list.end(); iter++)
		{
			if (iter->first == root_num)
				nb_vertices += iter->second->Size();
			else nb_vertices += iter->second->Size() - iter->second->Get_Separator()->Size();
		}
	}
	
	return nb_vertices;
}


inline int Cluster_Tree::Nb_Clusters ()
// returns the number of clusters of the cluster tree
{
	return nb_clusters;
}


inline int Cluster_Tree::Get_Max_Label ()
// returns the largest label of clusters of the cluster tree
{
	return max_label;
}


inline Cluster_Node * Cluster_Tree::Get_Cluster (int num)
// returns the cluster num if it exists
{
	map<int,Cluster_Node *>::iterator iter = cluster_list.find(num);
	
	if (iter == cluster_list.end()) return 0;
	else return iter->second;
}


inline Cluster_Node * Cluster_Tree::Get_Root ()
// returns the number root cluster
{
	return root;
}


inline int Cluster_Tree::Get_Root_Num ()
// returns the number root cluster
{
	return root_num;
}

#endif

