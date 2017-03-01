#include "tree_decomposition.h"
#include <iostream>
#include <queue>
#include <stack>
#include <light_stack.h>


//-----------------------------
// constructors and destructor
//-----------------------------


Tree_Decomposition::Tree_Decomposition (Light_Graph * gs)
// constructs an empty tree-decomposition related to the graphical structure gs
{
	g = gs;
	ct_number = 0;
}


Tree_Decomposition::Tree_Decomposition (Tree_Decomposition & td)
// constructs a tree-decomposition by copying the tree-decomposition td
{
	g = td.g;

	cluster_tree.expand (td.ct_number);
	ct_number = td.ct_number;
	
	for (int i = 0; i < ct_number; i++)
		cluster_tree[i] = new Cluster_Tree (*(td.cluster_tree[i]));
}


Tree_Decomposition::~Tree_Decomposition ()
// destructor
{
	for (int i = 0; i < ct_number; i++)
		delete cluster_tree[i];
}
		

//----------
// operator
//----------


Tree_Decomposition & Tree_Decomposition::operator= (Tree_Decomposition & td)
// operator =
{
	if (this != &td)
	{
		// we free the allocated memory
		for (int i = 0; i < ct_number; i++)
			delete cluster_tree[i];
			
		// we copy the data
		g = td.g;
		
		if (cluster_tree.get_capacity() < td.ct_number)
			cluster_tree.expand (td.ct_number-cluster_tree.get_capacity());
		ct_number = td.ct_number;
		
		for (int i = 0; i < ct_number; i++)
			cluster_tree[i] = new Cluster_Tree (*(td.cluster_tree[i]));
	}
	
	return *this;
}


//-----------------
// basic functions 
//-----------------


int Tree_Decomposition::Get_W ()
// returns the width of the tree-decomposition
{
	int w = -1;
	
	for (int i = 0; i < ct_number; i++)
	{
		for (map<int,Cluster_Node *>::iterator iter = cluster_tree[i]->Begin_List(); iter != cluster_tree[i]->End_List(); iter++)
			if (w < iter->second->Size()-1)
				w = iter->second->Size()-1;
	}

	return w;
}


int Tree_Decomposition::Nb_Clusters ()
// returns the number of clusters of the cluster tree
{
	int sum = 0;
	
	for (int i = 0; i < ct_number; i++)
		sum += cluster_tree[i]->Nb_Clusters ();
	
	return sum;
}


int Tree_Decomposition::Get_Max_Label ()
// returns the largest label of clusters of the cluster tree
{
	int max = 0;
	
	for (int i = 0; i < ct_number; i++)
		if (max < cluster_tree[i]->Get_Max_Label ())
			max = cluster_tree[i]->Get_Max_Label ();
			
	return max;
}


//-----------------------------------
// function computing cluster trees
//-----------------------------------


void Tree_Decomposition::Make_Tree (pair<int,Light_List<Cluster_Node *> > lc)
// makes a tree from the cluster list lc
{  
	// we count the number of clusters in the list lc
	int nb_clusters = lc.first;

  // we compute the cluster tree by connecting, at each step, a new cluster from lc to a cluster chosen previously with which it shares the largest intersection (we use the Prim's algorithm)
  	
  // initialization of keys
  int * key;
  key = new int [nb_clusters];
  Cluster_Node ** parent;
  parent = new Cluster_Node * [nb_clusters];
  int * index ;
  index = new int [nb_clusters];
  Cluster_Node ** clusters;
  clusters = new Cluster_Node * [nb_clusters];

	Light_List<Cluster_Node *>::iterator iter_cl = lc.second.begin();
  for (int i = 0; i < nb_clusters; i++)
  {
    key[i] = 0;
    parent[i] = 0;
    index[i] = i;
    clusters[i] = *iter_cl;
    iter_cl++;
  }

	// we apply the Prim's Algorithm
	int ind_max = -1;
	int max;
	Light_List<pair<vertex,int> >::iterator neighbor_iter;
	Light_Vector<vertex>::iterator iter_v;
	int inter, j, choice;
	  
  while (nb_clusters > 0)
  {
    max = -1;
    for (j = 0; j < nb_clusters; j++)
      if (key[index[j]] > max)
      {
        max = key[index[j]];
        ind_max = j;
      }
      else
				if ((key[index[j]] == max) && (index[j] < index[ind_max]))
					ind_max = j;

		choice = index[ind_max];
		
		// we update the cluster tree
		if (max == 0)
		{
			// we create a new cluster tree
			ct_number++;
			if (ct_number >= cluster_tree.get_capacity ())
				cluster_tree.expand(50);
			cluster_tree[ct_number-1] = new Cluster_Tree(g);
				
			// we add the selected cluster to the current cluster tree
			cluster_tree[ct_number-1]->Add_Cluster (clusters[choice]);
		}
		else
			{
				// we add the selected cluster to the current cluster tree
				cluster_tree[ct_number-1]->Add_Cluster (clusters[choice]);
				
				// we link the selected cluster with its parent cluster
				cluster_tree[ct_number-1]->Add_Child_Node (parent[choice],clusters[choice]);
			}
				
		// we update the index data structure
		nb_clusters--;
    index[ind_max] = index[nb_clusters];
     
    // we update the key values
    for (j = 0; j < nb_clusters; j++)
    {
			// we compute the intersection between the last selected cluster and the unchosen clusters
      
      inter = 0;
      for (iter_v = clusters[choice]->begin(); iter_v != clusters[choice]->end(); iter_v++)
        if (clusters[index[j]]->Is_Element (*iter_v))
          inter++;

      if (inter > key[index[j]])
      {
        key[index[j]] = inter;
        parent[index[j]] = clusters[choice];
      }
    }
  }

  delete [] key;
  delete [] parent;
  delete [] index;
  delete [] clusters;
}
