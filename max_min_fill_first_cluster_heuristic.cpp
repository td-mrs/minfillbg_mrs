#include "max_min_fill_first_cluster_heuristic.h"
#include <iostream>
#include <light_stack.h>
#include <typeinfo>
#include <tuple>
#include "connected_component.h"


//----------------------------
// constructor and destructor
//----------------------------

Max_Min_Fill_First_Cluster_Heuristic::Max_Min_Fill_First_Cluster_Heuristic (Light_Graph * gs)
// constructs a heuristic which chooses a clique (of the primal graph of the graphical structure gs)
{
	g = gs;
}

//-----------------
// basic functions
//-----------------

pair<int,vertex *> Max_Min_Fill_First_Cluster_Heuristic::Choose ()
{
  Light_Graph * pg = g;

	// choose the vertex which must first be chosen by Min-Fill
	Light_List<vertex>::iterator iter,iter2;
	
	unsigned int n = g->N();
		
	// computation of the initial number of edges to add
	vertex x;
	vertex x_min = -1;
	unsigned long min = n * n;
	
	
  int * marked;
  marked = new int [n];
  for (x = 0; x < n; x++)
    marked[x] = -1;
    
  for (x = 0; x < n; x++)
  {
    unsigned int nb_additions_x = 0;
    
    for (iter = pg->Begin_Neighbor(x); (iter != pg->End_Neighbor (x)) && (nb_additions_x <= min); iter++)
    {
      for (iter2 = pg->Begin_Neighbor(*iter); iter2 != pg->End_Neighbor (*iter); iter2++)
        marked[*iter2] = *iter;
      
      for (iter2 = iter, iter2++; (iter2 != pg->End_Neighbor (x)) && (nb_additions_x <= min); iter2++)
        if (marked[*iter2] != (signed) *iter)
          nb_additions_x ++;
    }
    
    if (nb_additions_x < min)
    {
      min = nb_additions_x;
      x_min = x;	
    }
    else
      if ((nb_additions_x == min) && (pg->Degree(x) > pg->Degree(x_min)))
        x_min = x;	
  }
  delete [] marked;
						
	// construct the cluster of x_min and its neighbors
	pair<int, vertex *> cluster;

	cluster.second[0] = x_min;
	cluster.first = 1;
	
	for (iter = pg->Begin_Neighbor(x_min); iter != pg->End_Neighbor (x_min); iter++)
	{	
		cluster.second[cluster.first] = *iter;
		cluster.first++;
	}
		
	return cluster;	
}	


Cluster_Node * Max_Min_Fill_First_Cluster_Heuristic::Choose (bool is_available[])
// returns the first cluster for a tree-decomposition according to a heuristic method. This cluster must be connected and its vertices must be chosen among the vertices for which the flag is_available is set to true. For each selected vertex, is_available is set to false
{
  Light_Graph * pg = g;

	// choose the vertex which must first be chosen by Min-Fill
	Light_List<vertex>::iterator iter,iter2;
	
	unsigned int n = g->N();
		
	// computation of the initial number of edges to add
	vertex x;
	vertex x_min = 0;
	unsigned long min = ((long) n) * n;
	
  int * marked;
  marked = new int [n];
  for (x = 0; x < n; x++)
    marked[x] = -1;
    
  for (x = 0; x < n && min != 0 ; x++)
  {
    if (is_available[x])
    {
      unsigned int nb_additions_x = 0;
      
      for (iter = pg->Begin_Neighbor(x); (iter != pg->End_Neighbor (x)) && (nb_additions_x <= min); iter++)
        if (is_available[*iter])
        {
          for (iter2 = pg->Begin_Neighbor(*iter); iter2 != pg->End_Neighbor (*iter); iter2++)
            marked[*iter2] = *iter;
          
          for (iter2 = iter, iter2++; (iter2 != pg->End_Neighbor (x)) && (nb_additions_x <= min); iter2++)
            if ((is_available[*iter2]) && (marked[*iter2] != (signed) *iter))
              nb_additions_x ++;
        }
      
      if (nb_additions_x < min)
      {
        min = nb_additions_x;
        x_min = x;	
      }
    }
  }
  delete [] marked;
				
	// construct the cluster of x_min and its neighbors
	Cluster_Node * cluster = new Cluster_Node (g);
	cluster->Add_Vertex (x_min);
	is_available[x_min] = false;
	
	for (iter = pg->Begin_Neighbor(x_min); iter != pg->End_Neighbor (x_min); iter++)
		if (is_available[*iter])
		{	
			cluster->Add_Vertex (*iter);		
			is_available[*iter] = false;
		}
		
	return cluster;
}



