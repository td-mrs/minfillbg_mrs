/// \file 
/// \brief Definitions related to the Light_Graph class

#ifndef LIGHT_GRAPH_H
#define LIGHT_GRAPH_H

#include <light_list.h>
#include <light_vector.h>

using namespace std;

typedef unsigned int vertex;      ///< the type allowing to represent vertices


class Light_Graph           /// This class allows to represent graphs with adjacency list
{
  protected :
 		unsigned int n;  									 	///< number of vertices
		unsigned int m;   							 		///< numer of edges
		Light_Vector<unsigned int> degree;  ///< the degree of each vertex

  	Light_Vector<Light_List<vertex> > adjacency_list;   ///< the adjacency list of the graph
		
	public :
	  // constructors and destructor
		Light_Graph ();       					 							///< constructs an empty graph with 0 vertex and 0 edge
		Light_Graph (Light_Graph & g);         				///< constructs an graph by copying the graph g
		~Light_Graph ();		 					  		  				///< destructor

		// operator
		Light_Graph & operator= (Light_Graph & g); 		///< operator =

    // iterators
		Light_List<vertex>::iterator Begin_Neighbor (vertex x); ///< returns an iterator referring to the first neighbor of the vertex x
		Light_List<vertex>::iterator End_Neighbor (vertex x);   ///< returns an iterator referring to the position after the last neighbor of the vertex x
    
    // basic operations or functions on graphs
		unsigned int N ();  								///< returns the number of vertices
		unsigned int M ();  								///< returns the number of edges
		unsigned int Degree (vertex x);   	///< returns the degree of the vertex x
		Light_Vector<unsigned int> & Degrees (); ///< returns the degree of for each vertex		
		void Init (int nb_vertices); 										///< initializes the graph with n vertices and 0 edge
		void Add_Vertex ();   													///< adds a vertex to the graph
		bool Is_Edge (vertex x, vertex y);   						///< returns true if {x,y} is an edge of the graph, false otherwise
		void Add_Edge (vertex elements[], int arity);  	///< adds the vertices of elements as a new edge of the graph if the value of arity is 2, otherwise adds these vertices as a new clique of the graph
		void Add_Edge (vertex x, vertex y);   					///< adds the edge {x,y} to the graph
		void Add_Edge_End (vertex x, vertex y); 				///< adds the edge {x,y} to the graph at the end of adjacency list
		void Remove_Edge (vertex x, vertex y); 				  ///< removes the edge {x,y} to the graph
    void Load_TW ();                                ///< reads the graphical structure from the file filename containing a graph instance (in TW format)
};


//-----------------------------
// inline function definitions
//-----------------------------

//-----------
// iterators
//-----------


inline Light_List<vertex>::iterator Light_Graph::Begin_Neighbor (vertex x)
// returns an iterator referring to the first neighbor of the vertex x
{
	return adjacency_list[x].begin();
}


inline Light_List<vertex>::iterator Light_Graph::End_Neighbor (vertex x)
// returns an iterator referring to the position after the last neighbor of the vertex x
{
	return adjacency_list[x].end();
}


//-----------------
// basic functions
//-----------------


inline unsigned int Light_Graph::N ()  
// return the number of vertices
{
	return n;
}


inline unsigned int Light_Graph::M ()
// return the number of edges
{
	return m;
}


inline unsigned int Light_Graph::Degree (vertex x)
// returns the degree of the vertex x
{
	return degree[x];
}


inline Light_Vector<unsigned int> & Light_Graph::Degrees ()
// returns the degree of for each vertex
{
	return degree;
}

#endif
