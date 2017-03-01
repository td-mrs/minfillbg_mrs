#include "order.h"
#include <set>
#include <iostream>
#include <fstream>
using namespace std;

//-----------------------------
// constructors and destructor
//-----------------------------

Order::Order ()
// constructs an empty order with 0 vertex
{
	n = 0;
}


Order::Order (Order & o)
// constructs an order by copying the order o
{
	n = o.n;
	order = o.order;
	rev_order = o.rev_order;
}


Order::~Order ()
// destructor
{
}


//----------
// operator
//----------


Order & Order::operator= (const Order & o)
// operator =
{
  if (this != &o)
  {
		n = o.n;
		order = o.order;
		rev_order = o.rev_order;
	}
	return *this;
}


//----------------------------------------
// basic operations or functions on order
//----------------------------------------


void Order::Init (unsigned int nb_vertices)
// initializes the order with n vertices
{
	n = nb_vertices;
	order.expand (nb_vertices,-1);
	rev_order.expand (nb_vertices,-1);
}


void Order::Set_Position (vertex x, int pos)
// puts the vertex x at the position pos
{
	if ((x >= 0) && ((unsigned) x < n) && (pos >= 0) && ((unsigned) pos < n))
	{
		order[x] = pos;
		rev_order[pos] = x;
	}
}


int Order::Width (Light_Graph * g)
// computes the width of the order w.r.t. the graph g
{
  vertex x;
  int width_x;        // the width of the vertex x;
  int max_width = 0;  // the largest width  
  
  max_width = 0;
  for (x = 0; x < n; x++)
  {
    width_x = 0;
    
    for (Light_List<vertex>::iterator iter = g->Begin_Neighbor(x); iter != g->End_Neighbor(x); iter++)
      if (order[*iter] < order[x])
        width_x++;
      
    if (width_x > max_width)  max_width = width_x;
  }
  
  return max_width;
}


//-----------------
// output function
//-----------------


void Order::Print ()
// prints the order and the reverse order
{
	cout << "Order:";
	for (Light_Vector<int>::iterator iter=order.begin(); iter != order.end(); iter++)
		cout << " " << *iter;
	cout << endl;
		
	cout << "Reverse Order:";
	for (Light_Vector<vertex>::iterator iter=rev_order.begin(); iter != rev_order.end(); iter++)
		cout << " " << *iter;
	cout << endl;
}


//-------------------------------------------
// specific function for triangulated graphs
//-------------------------------------------


bool Order::Is_peo (Light_Graph * g)
// returns true if the order is a perfect elimination order of the graph g
{
	vertex v,w;
	unsigned int i, j;
	Light_List<vertex>::iterator iter;
	
  for (i = 0; i < g->N()-1; i++)
  {
    v = Get_Vertex (i);

    /* we exploit the notion of quasi-simplicial vertex */
    j = i+1;
    while ((j < g->N()) && (! g->Is_Edge (v,Get_Vertex(j)))) j++;
   
    if (j < g->N())
    {
      
      w = Get_Vertex (j);
      
      for (iter = g->Begin_Neighbor (v); iter != g->End_Neighbor (v); iter++)
        if ((Get_Position(v) < Get_Position(*iter)) && (! g->Is_Edge (w,*iter)) && (*iter != w))
					return false;
    }
  }
  return true;
}
