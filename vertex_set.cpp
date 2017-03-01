#include "vertex_set.h"
#include "light_graph.h"
#include <algorithm>
#include <light_stack.h>
#include <typeinfo>


//-----------------------------
// constructors and destructor
//-----------------------------

Vertex_Set::Vertex_Set (Light_Graph * gs)
// constructs an empty vertex set related to gs
{
	g = gs;
	size = 0;
	nb_edges = 0;
	nb_partial_edges = 0;
	nb_components = 0;
}


Vertex_Set::Vertex_Set (Light_Vector<vertex> element_set, Light_Graph * gs)
// constructs a vertex set containing the vertices of element_set and related to gs
{
	g = gs;
	elements = element_set;
	size = elements.get_capacity();

	vertex max = -1;
	for (Light_Vector<vertex>::iterator iter = element_set.begin(); iter != element_set.end(); iter++)
		if (*iter > max)
			max = *iter;
			
	is_element = vector<bool> (max+1,false);
	
	Light_Vector<vertex>::iterator iter;
	for (iter = elements.begin(); iter != elements.end(); iter++)
	  is_element[*iter] = true;
	  
	nb_edges = 0;
	nb_partial_edges = 0;
	nb_components = 0;	
}


Vertex_Set::Vertex_Set (Vertex_Set & s)
// constructs a vertex set by copying the vertex set s
{
	g = s.g;
	size = s.size;
	elements = s.elements;
	is_element = s.is_element;
	nb_edges = s.nb_edges;
	nb_partial_edges = s.nb_partial_edges;
	nb_components = s.nb_components;
}


Vertex_Set::Vertex_Set (const Vertex_Set & s)
// constructs a vertex set by copying the vertex set s
{
	g = s.g;
	size = s.size;
	elements = s.elements;
	is_element = s.is_element;
	nb_edges = s.nb_edges;
	nb_partial_edges = s.nb_partial_edges;
	nb_components = s.nb_components;
}

Vertex_Set::~Vertex_Set ()
// destructor
{
}


//----------
// operator
//----------

Vertex_Set & Vertex_Set::operator= (const Vertex_Set & s)
// operator =
{
	if (this != &s)
	{
		g = s.g;
		size = s.size;
		elements = s.elements;
		is_element = s.is_element;
		nb_edges = s.nb_edges;
		nb_partial_edges = s.nb_partial_edges;
		nb_components = s.nb_components;
	}
	return *this;
}


//------------------------------
// basic function on vertex set
//------------------------------


void Vertex_Set::Add_Vertex (vertex v)
// adds the vertex v to the current vertex set
{
	if (v >= is_element.size())
	{
		elements.push_back (v);
		is_element.resize (v+1,false);
		is_element[v] = true;
		size++;
	}
	else
		if (! is_element[v])
		{
			elements.push_back (v);
			is_element[v] = true;
			size++;
		}
}


void Vertex_Set::Remove_Vertex (vertex v)
// removes the vertex v from the current vertex set
{
	if (Is_Element(v))
	{
	  elements.erase (v);
		is_element[v] = false;
		size--;
	}
}


bool Vertex_Set::Is_Connected()
// returns true if the cluster has a single connected component, false otherwise
{
	Light_Graph * pg = g;
	
	vector<bool> visited = vector<bool> (g->N(),false);  // true is the vertex x has been visited, false otherwise
	int nb_visited = 0;      	// number of visited vertices
	Light_Stack<vertex> s (g->N());
	vertex v;
	
	// the computation is achieved by a depth-first search of the graph
	
	// traversal of the connected component of the vertex element[0]
	v = elements[0];
	visited[v] = true;
	nb_visited++;

	s.push(v);

	while (! s.is_empty())
	{
		v = s.top();
		s.pop();

		for (Light_List<vertex>::iterator iter2 = pg->Begin_Neighbor (v); iter2 != pg->End_Neighbor (v); iter2++)
			if ((Is_Element(*iter2)) && (! visited[*iter2]))
			{
				s.push (*iter2);
				visited[*iter2] = true;
				nb_visited++;
			}
	}
	
	return nb_visited == size;
}


void Vertex_Set::Merge (Vertex_Set * s)
// adds the vertex set s to the current vertex set.
{
	if ((this != s) && (s->g == g))
	{
		Light_Vector<vertex>::iterator iter;
		
		for (iter = s->elements.begin(); iter != s->elements.end(); iter++)
			Add_Vertex (*iter);

		nb_edges = 0;
		nb_partial_edges = 0;
		nb_components = 0;
	}
}
