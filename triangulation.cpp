#include "triangulation.h"
#include <typeinfo>

//----------------------------
// constructor and destructor
//----------------------------


Triangulation::Triangulation (Light_Graph * g_init)
// construct a triangulation from a graph
{
	nb_added_edges = 0;
	
	if (g_init != 0)
		g = new Light_Graph (*g_init);
	else g = 0;
	peo = new Order;
}


Triangulation::~Triangulation ()
{
	delete g;
	delete peo;
}


//------------------------------------------------
// basic operations or functions on triangulation
//------------------------------------------------


pair<int,Light_List<Cluster_Node *> > Triangulation::Clique_List ()
// computes the list of the maximal cliques of the triangulated graph g by using the perfect elimination order o
{
	pair<int,Light_List<Cluster_Node *> > lc;
	lc.first = 0;
	
  int * S;
  S = new int [g->N()];
  vertex v;
     
  for (v = 0; v < g->N(); v++)
    S[v] = 0;

	int card;
	Cluster_Node * clique;
  for (unsigned int i = 0; i < g->N(); i++)
  {
    v = peo->Get_Vertex (i);
    
    // we compute the number of ulterior neighbor w.r.t the order o
    card = 0;
    int min = g->N();
    vertex v_min = -1;
    
    clique = new Cluster_Node (g);
    clique->Add_Vertex (v);
    
    for (Light_List<vertex>::iterator iter = g->Begin_Neighbor(v); iter != g->End_Neighbor(v); iter++)
			if ((unsigned) peo->Get_Position(*iter) > i)
			{
				card++;
				clique->Add_Vertex (*iter);
				if (peo->Get_Position(*iter) < min)
				{
					min = peo->Get_Position(*iter);
					v_min = *iter;
				}
			}
					

    if (g->Degree(v) == 0)
    {
			// there is no neighbor
			// we construct a clique of size 1
      lc.first++;
			lc.second.push_back (clique);
    }
    else
      if (card > 0)
      {
        // we consider v_min which is the first ulterior neighbor of v
      
        if (S[v_min] < card)  S[v_min] = card - 1;
      
        if (S[v] < card)
        {
          // we construct a clique of size card+1
          lc.first++;
          lc.second.push_back (clique);
        }
        else delete clique;
      }
      else delete clique;
  }
  
  delete [] S;
	return lc;
}
