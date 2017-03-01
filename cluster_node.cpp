#include "cluster_node.h"
#include "child_node.h"


//-----------------------------
// constructors and destructor
//-----------------------------


Cluster_Node::Cluster_Node (Light_Graph * gs) : Vertex_Set (gs)
// constructs an empty cluster node related to the graphical structure gs
{
	num = -1;
	separator = 0;
	parent = 0;
	parent_num = -1;
	depth = -1;
}


Cluster_Node::Cluster_Node (Light_Vector<vertex> element_set, Light_Graph * gs) : Vertex_Set (element_set,gs)
// constructs a vertex set containing the vertices of element_set and related to the graphical structure gs
{
	num = -1;
	separator = 0;
	parent = 0;
	parent_num = -1;
	depth = -1;
}


Cluster_Node::Cluster_Node (Cluster_Node & cn) : Vertex_Set (cn)
// constructs a cluster node by copying the cluster node cn
{
	num = cn.num;
	separator = cn.separator;
	parent = cn.parent;
	parent_num = cn.parent_num;
	depth = cn.depth;
}


Cluster_Node::~Cluster_Node ()
// destructor
{
}


//----------
// operator
//----------

Cluster_Node & Cluster_Node::operator= (const Cluster_Node & cn)
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
		num = cn.num;
		separator = cn.separator;
		parent = cn.parent;
		depth = cn.depth;
	}
	return *this;
}


//----------------
// basic function
//----------------


void Cluster_Node::Set_Separator (Child_Node * cn)
// sets the separator between the current cluster and its parent
{
	separator = cn;
	if (separator != 0)
	{
		parent = separator->Get_Cluster();
		parent_num = separator->Get_Cluster_Num();
	}
}
