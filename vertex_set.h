/// \file 
/// \brief Definitions related to the Vertex_Set class

#ifndef VERTEX_SET_H
#define VERTEX_SET_H

#include <vector>
#include "light_graph.h"

class Vertex_Set                   /// This class allows to represent vertex sets
{
	protected:
		int size;                      ///< the size of the vertex set
		Light_Vector<vertex> elements; ///< the vertices which belong to the vertex set
		vector<bool> is_element;		   ///< is_element[x] is true if the vertex x belongs to the vertex set, false otherwise

		Light_Graph * g;		   ///< the graphical structure to which the vertex set is related

		int nb_edges;          			   ///< number of edges included in the vertex set
		int nb_partial_edges;          ///< number of edges which intersect the vertex set
		int nb_components;					   ///< number of connected components
		

	public:
		// constructors and destructor
		Vertex_Set (Light_Graph * gs);																 	  ///< constructs an empty vertex set related to gs
		Vertex_Set (Light_Vector<vertex> element_set, Light_Graph * gs);	///< constructs a vertex set containing the vertices of element_set and related to gs
		Vertex_Set (Vertex_Set & s);			            							      ///< constructs a vertex set by copying the vertex set s
		Vertex_Set (const Vertex_Set & s);				           							///< constructs a vertex set by copying the vertex set s
		~Vertex_Set ();																			 							///< destructor
		
		// operator
		Vertex_Set & operator= (const Vertex_Set & s);       ///< operator =
		
		// iterators
		Light_Vector<vertex>::iterator begin();										 ///< returns an iterator referring to the first vertex of the vertex set
		Light_Vector<vertex>::iterator end();										 	 ///< returns an iterator referring to the position after the vertex of the vertex set
				
		// basic functions on vertex set
		int Size ();                         ///< returns the size of the vertex set
		bool Is_Element (vertex v);          ///< returns true if the vertex v belongs to the vertex set, false otherwise
		void Add_Vertex (vertex v);       	 ///< adds the vertex v to the current vertex set
		void Remove_Vertex (vertex v);     	 ///< removes the vertex v  the current vertex set
		bool Is_Connected(); 								 ///< returns true if the cluster has a single connected component, false otherwise
		void Merge (Vertex_Set * s);      	 ///< adds the vertex set s to the current vertex set
		void Change_Light_Graph (Light_Graph * gs);		///< replaces the current graphical structure g by gs
};


//----------------------------
// inline iterator definition
//----------------------------


inline Light_Vector<vertex>::iterator Vertex_Set::begin()
// returns an iterator referring to the first vertex of the vertex set
{
	return elements.begin();
}


inline Light_Vector<vertex>::iterator Vertex_Set::end()
// returns an iterator referring to the position after the vertex of the vertex set
{
	return elements.end();
}


//-----------------------------
// inline function definitions
//-----------------------------


inline int Vertex_Set::Size ()
{
	return size;
}


inline bool Vertex_Set::Is_Element (vertex v)
// returns true if the vertex v belongs to the vertex set, false otherwise
{
	return (v < is_element.size()) && (is_element [v]);
}


inline void Vertex_Set::Change_Light_Graph (Light_Graph * gs)
// replaces the current graphical structure g by gs
{
	g = gs;
	nb_edges = 0;
	nb_partial_edges = 0;
	nb_components = 0;
}

#endif
