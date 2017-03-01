#include "next_vertices_heuristic.h"


Next_Vertices_Heuristic::Next_Vertices_Heuristic (Light_Graph * ref_g)
// constructor
{
	g = ref_g;
}


pair<int,vertex *> Next_Vertices_Heuristic::Choose (pair<int,vertex *> & vs, pair<int,vertex *> & aux_vs, pair<int,vertex *> & sep, int current_w)
{
	Cluster_Node cluster (g);
	
	for (int i = 0; i < aux_vs.first; i++)
		cluster.Add_Vertex (aux_vs.second[i]);
		
	bool is_available [g->N()];
	for (int i = g->N()-1; i >=0; i--)
		is_available [i] = true;
	
	Choose (vs,&cluster,sep,current_w,is_available);

	pair<int, vertex *> chosen_v;
	chosen_v.first = 0;
	chosen_v.second = new vertex [cluster.Size()];
	
	for (Light_Vector<vertex>::iterator iter = cluster.begin(); iter != cluster.end(); iter++)
	{
		chosen_v.second[chosen_v.first] = *iter;
		chosen_v.first++;
	}

	return chosen_v;
}
