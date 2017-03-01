#include "neighbor_future_degree_tie_break_policy.h"
#include <cassert>


//-------------
// constructor 
//-------------


Neighbor_Future_Degree_Tie_Break_Policy::Neighbor_Future_Degree_Tie_Break_Policy (unsigned int n): Tie_Break_Policy (n)
// constructs a tie-break policy with at most n ex aequo values
{
	stamp = 0;
	last_compute = new int [n];
	for (vertex i = 0; i < n; i++)
		last_compute[i] = -1;
	futdeg = new unsigned int [n];
}


Neighbor_Future_Degree_Tie_Break_Policy::~Neighbor_Future_Degree_Tie_Break_Policy ()
// destructor
{
	delete [] last_compute;
	delete [] futdeg;
}


//----------------
// basic function 
//----------------


int Neighbor_Future_Degree_Tie_Break_Policy::Choose (Light_Graph * g, vertex * candidates, Order * peo)
// chooses a vertex according to the chosen policy
{
	if (nb == 1)
		return exaequo[0];
	else
		{
			int ind_min = -1;
			unsigned int min = g->N()+1;
			unsigned int min0 = g->N()+1;
			for (int j = 0; j < nb; j++)
			{
				vertex v = candidates[exaequo[j]];
				unsigned int max_deg = 0;
				
				if (last_compute[v] != stamp)
				{
					futdeg[v] = 0;
					for (Light_List<vertex>::iterator iter = g->Begin_Neighbor(v); iter != g->End_Neighbor(v); iter++)
						if (peo->Get_Position (*iter) == -1)
							futdeg[v]++;
				}
				assert (futdeg[v] > 0);
				max_deg = futdeg[v];
				
				for (Light_List<vertex>::iterator iter = g->Begin_Neighbor(v); iter != g->End_Neighbor(v); iter++)
					if (peo->Get_Position (*iter) == -1)
					{
						if (last_compute[*iter] != stamp)
						{
							futdeg[*iter] = 0;
							for (Light_List<vertex>::iterator iter2 = g->Begin_Neighbor(*iter); iter2 != g->End_Neighbor(*iter); iter2++)
								if (peo->Get_Position (*iter2) == -1)
									futdeg[*iter]++;
						}
								
						if (futdeg[*iter]-1 > max_deg)
							max_deg = futdeg[*iter]-1;
					}

				if (max_deg < min)
				{
					ind_min = exaequo[j];
					min = max_deg;
					min0 = futdeg[v];
				}
				else
					if ((max_deg == min) && (futdeg[v] < min0))
					{
						min0 = futdeg[v];
						ind_min = exaequo[j];
					}
					else
						if (((max_deg == min) && (futdeg[v] == min0)) && (g->Degree(v) < g->Degree(candidates[ind_min])))
							ind_min = exaequo[j];
						else
							if (((max_deg == min) && (futdeg[v] == min0)) && (g->Degree(v) == g->Degree(candidates[ind_min])) && (v < candidates[ind_min]))
								ind_min = exaequo[j];
			}
			
			return ind_min;
		}
}


int Neighbor_Future_Degree_Tie_Break_Policy::Choose (Light_Graph * g, vertex * candidates, bool is_untreated [])
// chooses a vertex according to the chosen policy
{
	if (nb == 1)
		return exaequo[0];
	else
		{
			int ind_min = -1;
			int min = g->N()+1;
			for (int j = 0; j < nb; j++)
			{
				int deg = 0;
				for (Light_List<vertex>::iterator iter = g->Begin_Neighbor(candidates[exaequo[j]]); (iter != g->End_Neighbor(candidates[exaequo[j]])) && (deg <= min); iter++)
					if (is_untreated [*iter])
						deg++;
              
				if (deg < min)
				{
					ind_min = exaequo[j];
					min = deg;
				}
				else
					if ((deg == min) && (candidates[exaequo[j]] < candidates[ind_min]))
						ind_min = exaequo[j];
			}
			
			return ind_min;
		}
}
