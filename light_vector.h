/// \file 
/// \brief Definitions related to the Light_Vector class

#ifndef LIGHT_VECTOR_H
#define LIGHT_VECTOR_H

using namespace std;

#include <light_iterator.h>

template <class T>
class Light_Vector		/// This class allows to represent vectors of elements (each element being of type T)
{
	protected:
		T * data;					///< the data of the vector
		int capacity;			///< the capacity of the vector		
		
	public:
		// constructors and destructor
		Light_Vector ();													///< constructs an empty vector
		Light_Vector (int n);											///< constructs a vector of size n
		Light_Vector (int n, T default_value);		///< constructs a vector of size n and initializes each element to default_value
		Light_Vector (Light_Vector<T> & v); 			///< constructs a vector by copying the vector v
		Light_Vector (const Light_Vector<T> & v); ///< constructs a vector by copying the vector v
		~Light_Vector ();			///< destructor
		
		// iterators
		typedef Light_Iterator<T> iterator;		///< type for iterators on vector
		Light_Vector<T>::iterator begin();		///< returns an iterator referring to the first element of the set
		Light_Vector<T>::iterator end();			///< returns an iterator referring to the position after the last element of the set

		
		// operators
		Light_Vector<T> & operator= (const Light_Vector<T> & v);	///< operator =
		T& operator[] (int n);																		///< operator []
		const T& operator[] (int n) const;												///< operator []
		
		// basic functions
		int get_capacity ();									///< returns the capacity of the vector
		void expand (int n);									///< expands the vector by adding n elements at the end of the vector
		void expand (int n, T default_value); ///< expands the vector by adding n elements at the end of the vector and initializes each new element to default_value
		void swap (int i, int j); 						///< swaps the values at indices i and j
		void push_back (T val);								///< adds the value val at this end of the vector
		void erase (T val);										///< removes the value val from the vector
};

#include "light_vector.tpp"

#endif

