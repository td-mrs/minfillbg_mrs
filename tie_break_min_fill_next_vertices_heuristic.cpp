#include "tie_break_min_fill_next_vertices_heuristic.h"
#include "tie_break_partial_min_fill_triangulation.h"
#include <iostream>
#include <cassert>

//-------------
// constructor
//-------------


Tie_Break_Min_Fill_Next_Vertices_Heuristic::Tie_Break_Min_Fill_Next_Vertices_Heuristic (Light_Graph * ref_g, Tie_Break_Policy * tbp): Next_Vertices_Heuristic(ref_g)
// constructs a heuristic which chooses vertices in the neighborhood (w.r.t. the graph ref_g) of a set of vertices 
{
	tie_break_policy = tbp;
	
	current_g = new Light_Graph (*g);
}


Tie_Break_Min_Fill_Next_Vertices_Heuristic::~Tie_Break_Min_Fill_Next_Vertices_Heuristic ()
{
	delete current_g;
	delete tie_break_policy;
}

//-----------------
// basic functions
//-----------------


void Tie_Break_Min_Fill_Next_Vertices_Heuristic::Choose (pair<int,vertex *> & vs, Cluster_Node * cl, pair<int,vertex *> & sep, int current_w, bool is_available[])
// selects some vertices from the vertex set vs (according to the heuristic policy) and adds them to the cluster cl. The selected vertices are removed from vs. According to the heuristic, the selected vertices may have some relation (e.g. neighborhood) with some vertices of the vertex sets aux_vs or sep
// we select as next vertices the neigbhors in vs of the vertices in sep that has least neighbors
// the selected vertices are set to false in is_available
{
	assert (vs.first > 0);
	assert (sep.first > 0);
	
	int n = g->N();
	int * belong = new int [n];		// belong[x] is set to 0 if x must be ignored, 1 if x may be considerd or 2 if x must be considered
	
	for (int v = 0; v < n ; v++)
		belong[v] = 0;
	
	for (int v = 0; v < vs.first; v++)
		belong[vs.second[v]] = 1;
  
  // we complete (if necessary) the separator sep by adding the missing edges between the vertices of sep
  for (int i = 0; i < sep.first; i++)
  {
		belong[sep.second[i]] = 2;
		for (int j = i+1; j < sep.first; j++)
      if (! current_g->Is_Edge (sep.second[i],sep.second[j]))
        current_g->Add_Edge (sep.second[i],sep.second[j]);
	}
	
	// we compute a triangulation of the graph current_g
  Tie_Break_Partial_Min_Fill_Triangulation T (current_g,belong,tie_break_policy);
	Order * peo = T.Get_Peo_Order ();
	Light_Graph * tg = T.Get_Triangulated_Graph();

	// we look for a clique including sep among the cliques of the graph obtained by triangulating current_g

	// we first look for the first vertex of sep according to the peo order
	int ind_min = 0;	
	for (int i = 1; i < sep.first; i++)		
		if (peo->Get_Position (sep.second[i]) < peo->Get_Position (sep.second[ind_min]))
			ind_min = i;
	
	// we then look for the first vertex according to the peo order which is a neighbor of each vertex of sep
			
	int pos = peo->Get_Position (sep.second[ind_min]);			
	int j = 0; 
	bool ok = false;
	vertex v = -1;
	while ((j < pos) && (! ok))
	{
		// we check whether the j th vertex (aka v) is a neighbor of each vertex of the separator sep
		v = peo->Get_Vertex(j);
		int k = 0;
		while ((k < sep.first) && (tg->Is_Edge (sep.second[k],v)))
			k++;
		
		if (k == sep.first)
			ok = true;
		else j++;
	}

	// we build the cluster from the clique containing v and its ulterior neighbor
	if (ok)
	{		
		// we add the vertex v to the cluster cl 
		cl->Add_Vertex (v);
				
		// we remove this vertex from the vertex set vs
		int k = 0;
		while (vs.second[k] != v)
			k++;
		
		if (vs.first > 0)
		{
			vs.first--;
			vs.second[k] = vs.second[vs.first];
		}
		is_available[v] = false;		
	}
	else v = sep.second[ind_min];
		
	for (Light_List<vertex>::iterator iter_vertex = tg->Begin_Neighbor (v); iter_vertex != tg->End_Neighbor(v); iter_vertex++)
	{				
		if ((j < peo->Get_Position(*iter_vertex)) && (! cl->Is_Element (*iter_vertex)))
		{
			// we add the vertex *iter_vertex to the cluster cl 
			cl->Add_Vertex (*iter_vertex);
					
			// we remove this vertex from the vertex set vs
			int k = 0;
			while (vs.second[k] != *iter_vertex)
				k++;
			
			if (vs.first > 0)
			{
				vs.first--;
				vs.second[k] = vs.second[vs.first];
			}
			is_available[*iter_vertex] = false;
		}
	}
		
	delete [] belong;
}

