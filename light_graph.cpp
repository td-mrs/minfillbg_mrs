#include "light_graph.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <set>
#include <vector>
#include <map>


//-----------------------------
// constructors and destructor
//-----------------------------

Light_Graph::Light_Graph ()
// constructs an empty graph with 0 vertex and 0 edge
{
 	n = 0;
	m = 0;
}


Light_Graph::Light_Graph (Light_Graph & g)
// constructs an graph by copying the graph g
{
	// initialization of the graph with g.n vertices and 0 edge
	n = g.n;
	m = 0;

	adjacency_list.expand (n);
	degree.expand (n,0);
	  
	// copy of the edges of the graph g
	
	for (vertex x = 0; x < n; x++)
  {
    for (Light_List<vertex>::iterator iter = g.adjacency_list[x].begin(); iter != g.adjacency_list[x].end(); iter++)
      if (x < *iter)
        Add_Edge (x,*iter);
  }
}


Light_Graph::~Light_Graph ()
// destructor
{
}


//----------
// operator
//----------


Light_Graph & Light_Graph::operator= (Light_Graph & g)
// operator =
{
  if (this != &g)
  {
		// initialization of the graph with g.n vertices and 0 edge
		n = g.n;
		m = 0;

		adjacency_list.expand(n);
		degree.expand (n,0);

		// copy of the edges of the graph g
		
		for (vertex x = 0; x < n; x++)
		{
			for (Light_List<vertex>::iterator iter = g.adjacency_list[x].begin(); iter != g.adjacency_list[x].end(); iter++)
				if (x < *iter)
					Add_Edge (x,*iter);
		} 
	}
	
	return *this;
}



//----------------------------
// basic operations on graphs
//----------------------------


void Light_Graph::Init (int nb_vertices)
// initializes the graph with n vertices and 0 edge
{
	n = nb_vertices;
	m = 0;
	adjacency_list.expand (n);
	degree.expand (n,0);
}


void Light_Graph::Add_Vertex ()
// adds a vertex to the graph
{
	n++;
	adjacency_list.expand (1);
	degree.expand (1,0);
}


bool Light_Graph::Is_Edge (vertex x, vertex y)
// returns true if {x,y} is an edge of the graph, false otherwise
{
	Light_List<vertex>::iterator iter;
	for (iter = adjacency_list[x].begin(); (iter != adjacency_list[x].end()) && (*iter != y); iter++);
	
  return iter != adjacency_list[x].end();
}


void Light_Graph::Add_Edge (vertex elements[], int arity)
// adds the vertices of elements as a new edge of the graph if the value of arity is 2, otherwise adds these vertices as a new clique of the graph
{
	int i,j;
	for (i=0; i < arity; i++)
		for (j=i+1; j < arity; j++)
			Add_Edge (elements[i],elements[j]);
}


void Light_Graph::Add_Edge (vertex x, vertex y)
// adds the edge {x,y} to the graph
{
  adjacency_list[x].push_front (y);
  adjacency_list[y].push_front (x);
  degree[x]++;
  degree[y]++;
  m++;
}


void Light_Graph::Add_Edge_End (vertex x, vertex y)
// adds the edge {x,y} to the graph at the end of adjacency list
{
  adjacency_list[x].push_back (y);
  adjacency_list[y].push_back (x);
  degree[x]++;
  degree[y]++;
  m++;
}


void Light_Graph::Remove_Edge (vertex x, vertex y)  
// removes the edge {x,y} to the graph
{
	if (Is_Edge (x,y))
	{
		adjacency_list[x].remove (y);
		adjacency_list[y].remove (x);
		degree[x]--;
		degree[y]--;
		m--;
	}
}


void Light_Graph::Load_TW ()
// reads the graphical structure from the file filename containing a graph instance (in TW format)
{
  // read of the comment lines
  char type;
  string comment;
  bool pb_defined = false;   // true if the number of vertices and the number of edges have been read, false otherwise.
  int nb_vertices; 
  int nb_edges;
	vertex edge[2];
	string line;
	istringstream iss;
	
	map <int,int> name_to_index;

  
  while (! cin.eof())
  {
  	cin >> type;
  	
    if (! cin.eof())
    {
      switch (type)
      {
        case 'c' : getline(cin,comment);     // the line is a comment
                   break;
        case 'p' : if (pb_defined)					  // the line defined the number of vertices and the number of edges
                     throw ("Error: file is incorrect");
                   else
                     {
                       cin.get ();   // skip the space character
                       
                       string instance_format;
                       getline (cin,instance_format,' ');
                       
                       if (instance_format != "tw")
                         throw ("Error: file is incorrect");
                      
                       cin >> nb_vertices >> nb_edges;
                       
                       pb_defined = true;

                       Init (nb_vertices);
                     }
                   break;
        default :  if (! cin.eof())
                   {
                     if (pb_defined)					  // the line defined an edge
                     {	
                       cin.unget();
                       
                       cin >> edge[0] >> edge[1];
                       edge[0]--;
                       edge[1]--;
                       Add_Edge (edge,2);
                     }
                     else throw ("Error: file is incorrect");
                   }
      }
    }
  }
}
