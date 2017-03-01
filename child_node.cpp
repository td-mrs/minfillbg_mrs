#include "child_node.h"
#include <iostream>


//-----------------------------
// constructors and destructor
//-----------------------------


Child_Node::Child_Node (Light_Graph * gs) : Vertex_Set (gs)
// constructs an empty child node related to the graphical structure gs
{
	cluster_num = -1;
	cluster = 0;
}


Child_Node::Child_Node (Light_Vector<vertex> element_set, Light_Graph * gs) : Vertex_Set (element_set,gs)
// constructs a vertex set containing the vertices of element_set and related to the graphical structure gs
{
	cluster_num = -1;
	cluster = 0;
}


Child_Node::Child_Node (Child_Node & cn) : Vertex_Set (cn)
// constructs a child node by copying the child node cn
{
	cluster_num = cn.cluster_num;
	cluster =  cn.cluster;
}


Child_Node::~Child_Node ()
// destructor
{
}


//----------
// operator
//----------

Child_Node & Child_Node::operator= (const Child_Node & cn)
// operator =
{
  if (this != &cn)
	{
		g = cn.g;
		size = cn.size;
		elements = cn.elements;
		is_element = cn.is_element;
		nb_edges = cn.nb_edges;
		nb_partial_edges = cn.nb_partial_edges;
		nb_components = cn.nb_components;
		cluster_num = cn.cluster_num;
	}
	return *this;
}
