#include "cluster_tree.h"
#include <light_stack.h>
#include <iostream>
#include <queue>
#include <stack>
#include <typeinfo>
#include <cassert>

//-----------------------------
// constructors and destructor
//-----------------------------

Cluster_Tree::Cluster_Tree (Light_Graph * gs)
// constructs an empty cluster tree
{
	nb_clusters = 0;
	root = 0;
	root_num = -1;
	max_label = -1;
	g = gs;
	nb_vertices = 0;
}


Cluster_Tree::Cluster_Tree (Cluster_Tree & ct)
// constructs a cluster tree by copying the cluster tree ct
{
	root = ct.root;
	root_num = ct.root_num;
	nb_clusters = ct.nb_clusters;
	max_label = ct.max_label;
	g = ct.g;
	nb_vertices = ct.nb_vertices;
	
	map<int,Cluster_Node *>::iterator iter;
	Cluster_Node * cl;
	
	// copy of the cluster_list
	for (iter = ct.cluster_list.begin(); iter != ct.cluster_list.end(); iter++)
	{
		cl = new Cluster_Node (*(iter->second));
		cluster_list.insert(pair<int,Cluster_Node *>(iter->first,cl));	
		adjacency_list.insert (pair<int,deque<Child_Node *> >(iter->first,deque<Child_Node *>()));
	}
	
	// copy of the adjacency_list
	map<int,deque<Child_Node *> >::iterator iter2;
	deque<Child_Node *>::iterator iter3;
	Child_Node * intersection;
	  	
	
	for (iter2 = ct.adjacency_list.begin(); iter2 != ct.adjacency_list.end(); iter2++)
	{
		for (iter3 = iter2->second.begin(); iter3 != iter2->second.end(); iter3++)
		{
			intersection = new Child_Node (**iter3);
			intersection->Set_Cluster (cluster_list.find(intersection->Get_Cluster_Num())->second);
			adjacency_list.find(iter2->first)->second.push_back (intersection);
			
			cl = cluster_list.find(iter2->first)->second;
			if (intersection->Get_Cluster_Num() == cl->Get_Parent_Num())
				cl->Set_Separator (intersection);
		}
	}	
}


Cluster_Tree::~Cluster_Tree ()
// destructor
{
	map<int,Cluster_Node *>::iterator iter;
	deque<Child_Node *>::iterator iter2;
	
	for (iter = cluster_list.begin(); iter != cluster_list.end(); iter++)
	{
		for (iter2 = adjacency_list.find (iter->first)->second.begin(); iter2 != adjacency_list.find (iter->first)->second.end(); iter2++)
			delete *iter2;
 		delete iter->second;
 	}
}


//----------
// operator
//----------


Cluster_Tree & Cluster_Tree::operator= (Cluster_Tree & ct)
// operator =
{
	if (this != &ct)
	{
		// we free the allocated memory
		map<int,Cluster_Node *>::iterator iter;
		deque<Child_Node *>::iterator iter3;
		
		for (iter = cluster_list.begin(); iter != cluster_list.end(); iter++)
		{
			for (iter3 = adjacency_list.find (iter->first)->second.begin(); iter3 != adjacency_list.find (iter->first)->second.end(); iter3++)
				delete *iter3;
			delete iter->second;
		}
		
		cluster_list.clear();
		adjacency_list.clear();

		// we copy the cluster tree ct
		root = ct.root;
		nb_clusters = ct.nb_clusters;
		max_label = ct.max_label;
		nb_vertices = ct.nb_vertices;	
		g = ct.g;	
		
		Cluster_Node * cl;
		
		// copy of the cluster_list
		for (iter = ct.cluster_list.begin(); iter != ct.cluster_list.end(); iter++)
		{
			cl = new Cluster_Node (*(iter->second));
			cluster_list.insert(pair<int,Cluster_Node *>(iter->first,cl));	
			adjacency_list.insert (pair<int,deque<Child_Node *> >(iter->first,deque<Child_Node *>()));
		}
		
		// copy of the adjacency_list
		map<int,deque<Child_Node *> >::iterator iter2;
		Child_Node * intersection;
				
		
		for (iter2 = ct.adjacency_list.begin(); iter2 != ct.adjacency_list.end(); iter2++)
		{
			for (iter3 = iter2->second.begin(); iter3 != iter2->second.end(); iter3++)
			{
				intersection = new Child_Node (**iter3);
				intersection->Set_Cluster (cluster_list.find(intersection->Get_Cluster_Num())->second);
				adjacency_list.find(iter2->first)->second.push_back (intersection);
				
				cl = cluster_list.find(iter2->first)->second;
				if (intersection->Get_Cluster_Num() == cl->Get_Parent_Num())
					cl->Set_Separator (intersection);
			}
		}
	}
	return *this;
}


//-----------------
// basic functions 
//-----------------


void Cluster_Tree::Add_Cluster (Cluster_Node * cn, bool duplicate)
// adds a cluster to the cluster tree without connecting it to the existing cluster tree (the cluster is duplicated if duplicate is true)
{
	Cluster_Node * elt;

	if (duplicate)	elt = new Cluster_Node (*cn);
	else elt = cn;
	
	elt->Change_Light_Graph(g);
	
	max_label++;
	nb_clusters++;
	elt->Set_Num (max_label);
	
	if (root_num == -1)
	{
		root = elt;
		root_num = max_label;
		elt->Set_Depth(0);
	}
	
	cluster_list.insert(pair<int,Cluster_Node *>(max_label,elt));
	adjacency_list.insert (pair<int,deque<Child_Node *> >(max_label,deque<Child_Node *>()));
	
	nb_vertices = 0;
}


void Cluster_Tree::Add_Child_Node (int lp, int lc)
// adds two child nodes in the cluster tree such that lc is the label of the child cluster and lp is the label of the parent cluster
{
	Cluster_Node * parent = cluster_list.find(lp)->second;
	Cluster_Node * child = cluster_list.find(lc)->second;
	
	Child_Node * intersection = new Child_Node (g);

	for (Light_Vector<vertex>::iterator iter_elt = parent->begin(); iter_elt != parent->end(); iter_elt++)
		if (child->Is_Element (*iter_elt))
			intersection->Add_Vertex (*iter_elt);
	
	assert (intersection->Size() > 0);
	
	intersection->Set_Cluster (child);
	adjacency_list.find(lp)->second.push_back (intersection);	
	
	Child_Node * intersection2 = new Child_Node (*intersection);
	
	intersection->Set_Cluster (parent);
	child->Set_Separator (intersection2);	
	adjacency_list.find(lc)->second.push_back (intersection2);
	
	child->Set_Depth(parent->Get_Depth()+1);
	nb_vertices = 0;
}


void Cluster_Tree::Add_Child_Node (Cluster_Node * parent, Cluster_Node * child)
// adds two child nodes in the cluster tree such that child is a pointer on the child cluster and parent is a pointer on the parent cluster
{
	Child_Node * intersection = new Child_Node (g);

	for (Light_Vector<vertex>::iterator iter_elt = parent->begin(); iter_elt != parent->end(); iter_elt++)
		if (child->Is_Element (*iter_elt))
			intersection->Add_Vertex (*iter_elt);
	
	assert (intersection->Size() > 0);
	
	intersection->Set_Cluster (child);
	adjacency_list.find(parent->Get_Num())->second.push_back (intersection);	
	
	Child_Node * intersection2 = new Child_Node (*intersection);
	
	intersection2->Set_Cluster (parent);
	child->Set_Separator (intersection2);	
	adjacency_list.find(child->Get_Num())->second.push_back (intersection2);

	child->Set_Depth(parent->Get_Depth()+1);
	nb_vertices = 0;
}


void Cluster_Tree::Set_Root (int root_label)
// sets the cluster whose label is root_label as root cluster of the cluster tree
{	
	if (nb_clusters > 1)
	{
		root = Get_Cluster(root_label);
		root_num = root_label;
	
		// case of the root cluster
		root->Set_Parent (0);
		root->Set_Separator (0);
		root->Set_Depth (0);
		
		// case of the other clusters
		vector<bool> mark = vector<bool> (max_label+1,false);
		queue<Cluster_Node *> next_cluster;
		Cluster_Node * cn;
		deque<Child_Node *> cn_deque, cn_deque2;
		deque<Child_Node *>::iterator iter,iter2;
		int lp, lchild;

		mark[root_label] = true;
		
		next_cluster.push (root);
		
		Cluster_Node * parent;
		
		do  // we apply a breath-first traversal of the cluster tree
		{
			parent = next_cluster.front ();
			lp = parent->Get_Num();
			next_cluster.pop ();
			
			cn_deque = adjacency_list.find(lp)->second;
			
			for (iter= cn_deque.begin(); iter != cn_deque.end(); iter++)
			{
				lchild = (*iter)->Get_Cluster_Num();
				if (! mark[lchild])
				{
					cn = (*iter)->Get_Cluster();
					cn->Set_Depth (parent->Get_Depth()+1);
			
					cn_deque2 = adjacency_list.find(lchild)->second;
					iter2 = cn_deque2.begin(); 
					while ((*iter2)->Get_Cluster_Num() != lp)
						iter2++;
						
					cn->Set_Separator (*iter2);
					
					// we add the label lchild to the queue
					mark[lchild] = true;
					next_cluster.push (cn);
				}
			}
		}
		while (next_cluster.size() > 0);
	}	
}


void Cluster_Tree::Set_Root (Cluster_Node * root_cluster)
// sets the cluster root_cluster as root cluster of the cluster tree
{	
	if (nb_clusters > 1)
	{
		root = root_cluster;
		root_num = root->Get_Num();
	
		// case of the root cluster
		root->Set_Parent (0);
		root->Set_Separator (0);
		root->Set_Depth (0);
		
		// case of the other clusters
		vector<bool> mark = vector<bool> (max_label+1,false);
		queue<Cluster_Node *> next_cluster;
		Cluster_Node * cn;
		deque<Child_Node *> cn_deque, cn_deque2;
		deque<Child_Node *>::iterator iter,iter2;
		int lp, lchild;

		mark[root_num] = true;
		
		next_cluster.push (root);
		
		Cluster_Node * parent;
		
		do  // we apply a breath-first traversal of the cluster tree
		{
			parent = next_cluster.front ();
			lp = parent->Get_Num();
			next_cluster.pop ();
			
			cn_deque = adjacency_list.find(lp)->second;
			
			for (iter= cn_deque.begin(); iter != cn_deque.end(); iter++)
			{
				lchild = (*iter)->Get_Cluster_Num();
				if (! mark[lchild])
				{
					cn = (*iter)->Get_Cluster();
					cn->Set_Depth (parent->Get_Depth()+1);
			
					cn_deque2 = adjacency_list.find(lchild)->second;
					iter2 = cn_deque2.begin(); 
					while ((*iter2)->Get_Cluster_Num() != lp)
						iter2++;
						
					cn->Set_Separator (*iter2);
					
					// we add the label lchild to the queue
					mark[lchild] = true;
					next_cluster.push (cn);
				}
			}
		}
		while (next_cluster.size() > 0);
	}	
}


void Get_Descent_Rec (Cluster_Tree * CT, int num, int parent_num, Vertex_Set * descent)
// returns the set of vertices which belong to the descent rooted in the cluster num whose parent number is parent_num
{
	Cluster_Node * cl = CT->Get_Cluster (num);

	for (Light_Vector<vertex>::iterator iter = cl->begin(); iter != cl->end(); iter++)
		descent->Add_Vertex (*iter);

	deque<Child_Node *>::iterator iter2;
	for (iter2 = CT->Begin_Neighbor(num); iter2 != CT->End_Neighbor(num); iter2++)
		if ((*iter2)->Get_Cluster_Num() != parent_num)
			Get_Descent_Rec (CT,(*iter2)->Get_Cluster_Num(),num,descent);
}


Vertex_Set Cluster_Tree::Get_Descent (int num)
// returns the set of vertices which belong to the descent rooted in the cluster num
{
	Vertex_Set descent (g);
	
	Get_Descent_Rec (this,num,Get_Cluster(num)->Get_Parent_Num(),&descent);
	
	return descent;
}


void Cluster_Tree::Print ()
// prints the cluster tree
{
	map<int,Cluster_Node *>::iterator iter;
	deque<Child_Node *>::iterator iter2;
	
	for (iter = cluster_list.begin(); iter != cluster_list.end(); iter++)
	{
		cout << "Cluster " << iter->first << ": parent = " << iter->second->Get_Parent() << ", depth = " << iter->second->Get_Depth() << ", child =";
		cout.flush();
		
		for (iter2 = adjacency_list.find (iter->first)->second.begin(); iter2 != adjacency_list.find (iter->first)->second.end(); iter2++)
			if ((*iter2)->Get_Cluster()->Get_Parent_Num() == iter->first)
				cout << " " << (*iter2)->Get_Cluster_Num();
		
		cout << endl;
	}
}
