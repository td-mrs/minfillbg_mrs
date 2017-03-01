#include "tie_break_partial_min_fill_triangulation.h"
#include <iostream>
#include <cassert>
#include <light_stack.h>


//-----------------------------
// constructors and destructor
//-----------------------------

Tie_Break_Partial_Min_Fill_Triangulation::Tie_Break_Partial_Min_Fill_Triangulation (Light_Graph * g_init, int available [], Tie_Break_Policy * tbp): Triangulation(0)
// construct a triangulation from a graph
{	
	is_available = available;
	remaining_vertices = 0;
	tie_break_policy = tbp;
	
	if (g_init != 0)
	{
		// we copy the graph g_init restricted to the vertices which are set to true in is_available

		g = new Light_Graph();
		
		g->Init (g_init->N());
		for (vertex x = 0; x < g_init->N(); x++)
			if (is_available[x] > 0)
			{
				for (Light_List<vertex>::iterator iter = g_init->Begin_Neighbor (x); iter != g_init->End_Neighbor(x); iter++)
					if ((is_available[*iter]) && (x < *iter))
						g->Add_Edge (x,*iter);
						
				if (is_available[x] == 2)
					remaining_vertices++;
			}
	
		Triangulate ();	
	}
	else g = 0;
}
	
		
Tie_Break_Partial_Min_Fill_Triangulation::~Tie_Break_Partial_Min_Fill_Triangulation ()
// destructor
{
}


//---------------------------------------
// functions for triangulating the graph
//---------------------------------------


// header of auxiliary functions
void nb_additions_update2 (Light_Graph * g, Order * o, vertex v, unsigned int nb_additions []);
void nb_additions_update2 (Light_Graph * g, Order * o, vertex v, unsigned int nb_additions [], int marked []);
void nb_additions_update (Light_Graph * g, Order * o, vertex x, vertex y, unsigned int nb_additions [], Light_Stack<vertex> & no_addition_stack, bool * is_in_stack, int marked []);
void nb_additions_update2 (Light_Graph * g, Order * o, vertex v, unsigned int nb_additions [], Light_Stack<vertex> & no_addition_stack, bool * is_in_stack, int marked []);


void Tie_Break_Partial_Min_Fill_Triangulation::Triangulate ()
// triangulates the graph induced by the vertices which are set to true in is_available thanks to the Min-Fill algorithm
{ 
	unsigned int * nb_additions;   // number of edges which must be added in order to make adjacent each pair of ulterior neighbors
	nb_additions = new unsigned int [g->N()];
	Light_List<vertex>::iterator iter,iter2;
	
	// computation of the initial number of edges to add
	
	vertex * candidates;
	candidates = new vertex [g->N()];
	int candidates_nb = 0;
	Light_Stack<vertex> no_addition_stack (g->N());
	bool * is_in_stack;
	is_in_stack = new bool [g->N()];

	int * marked;
	marked = new int [g->N()];
	int * marked2;
	marked2 = new int [g->N()];

	for (vertex x = 0; x < g->N(); x++)
	{
		marked[x] = -1;
		marked2[x] = -1;
	}

	unsigned int pos = 0;
	peo->Init (g->N());
	
	for (vertex x = 0; x < g->N(); x++)
		if (is_available[x] > 0)
		{
			nb_additions [x] = g->Degree(x)* (g->Degree(x)-1);
			
			for (iter = g->Begin_Neighbor(x); iter != g->End_Neighbor (x); iter++)
				marked[*iter] = x;

			for (iter = g->Begin_Neighbor(x); iter != g->End_Neighbor (x); iter++)
				for (iter2 = g->Begin_Neighbor(*iter); iter2 != g->End_Neighbor (*iter); iter2++)
					if (marked[*iter2] == (signed) x)
						nb_additions[x]--;

			nb_additions[x] /= 2;
			
			if (nb_additions[x] == 0)
			{
				no_addition_stack.push (x);
				is_in_stack[x] = true;
			}
			else 
				{
					candidates[candidates_nb] = x;
					candidates_nb++;
					is_in_stack[x] = false;
				}
		}
		else
			{
				peo->Set_Position(x,pos);
				pos++;
			}
	
	// computation of the triangulation
	unsigned long min;
	
	vertex v;

	while (pos < g->N())
	{
		// we first consider the vertices which add no edge
		while (! no_addition_stack.is_empty())
		{
			v = no_addition_stack.top();
			no_addition_stack.pop();
			
			if (nb_additions[v] == 0)
			{
				peo->Set_Position(v,pos);
				pos++;

			if (is_available[v] == 2)
				remaining_vertices--;

				nb_additions_update2 (g,peo,v,nb_additions,no_addition_stack,is_in_stack,marked);						
			}
			else is_in_stack[v] = false;
		}
		
		if (pos < g->N())
		{
			// we look for the vertex which leads to add the smallest number of edges
			
			assert (candidates_nb > 0);
			min = ((long) g->N())*g->N();

			for (int j = 0; j < candidates_nb; )
				if (nb_additions[candidates[j]] == 0)
				{
					candidates_nb--;
					candidates[j] = candidates[candidates_nb];
				}
				else
					{
						if (nb_additions[candidates[j]] < min)
						{
							tie_break_policy->Reset();
							tie_break_policy->Add(j);
							min = nb_additions[candidates[j]];
						}
						else
							if (nb_additions[candidates[j]] == min)
								tie_break_policy->Add(j);
						j++;
					}
			
			int ind_min = tie_break_policy->Choose (g,candidates,peo);
			
			assert (candidates_nb > 0);
			assert (ind_min >= 0);
			assert (nb_additions[candidates[ind_min]] > 0);
			
			v = candidates[ind_min];

			peo->Set_Position(v,pos);
			pos++;

			if (is_available[v] == 2)
				remaining_vertices--;
			
			candidates_nb--;
			candidates[ind_min] = candidates[candidates_nb];
			

			// the neighborhood is made complete
			nb_additions_update2 (g,peo,v,nb_additions,marked);
			
			for (iter = g->Begin_Neighbor(v); iter != g->End_Neighbor(v); iter++)
				if (peo->Get_Position (*iter) == -1)
				{
					for (iter2 = g->Begin_Neighbor(*iter); iter2 != g->End_Neighbor(*iter); iter2++)
						marked[*iter2] = *iter;
					
					for (iter2 = iter, iter2++; iter2 != g->End_Neighbor (v); iter2++)
					{
						if ((peo->Get_Position (*iter2) == -1) && (marked[*iter2] != (signed) *iter))
						{
							g->Add_Edge (*iter,*iter2);
							
							nb_added_edges++;
							
							nb_additions_update (g,peo,*iter,*iter2,nb_additions,no_addition_stack, is_in_stack,marked2);
						}
					}
				}
				
			for (iter = g->Begin_Neighbor(v); iter != g->End_Neighbor(v); iter++)
				if ((peo->Get_Position (*iter) == -1) && (nb_additions[*iter] == 0) && (! is_in_stack[*iter]))
				{
					no_addition_stack.push(*iter);
					is_in_stack[*iter] = true;
				}
		}
	}

	delete [] candidates;
	delete [] is_in_stack;
	delete [] nb_additions;
	delete [] marked;
	delete [] marked2;
}
