/// \file 
/// \brief Definitions related to the Light_Iterator class

#ifndef LIGHT_ITERATOR_H
#define LIGHT_ITERATOR_H

using namespace std;

template <class T>
class Light_Vector;

template <class T>
class Light_Iterator						/// This class allows to represent iterators on vectors of elements (each element being of type T)
{
	protected:
		Light_Vector<T> * object;		///< the object to which the iterator is related
		int current_pos;						///< the current position in the object
		
		
	public:
		// constructors
		Light_Iterator ();				///< constructs an empty iterator
		Light_Iterator (Light_Vector<T> * o, int initial_pos=0);	///< constructs an iterator on the object o for which the current pos is set to initial_pos
		Light_Iterator (const Light_Iterator<T> & iter);					///< constructs an iterator by copying the iterator iter
		
				
		// operators
		Light_Iterator<T> & operator= (const Light_Iterator<T> & iter);	///< operator =
		Light_Iterator<T> & operator++ (int);							///< operator ++
		T & operator* ();																	///< operator *
		bool operator== (const Light_Iterator<T> & iter);	///< operator ==
		bool operator!= (const Light_Iterator<T> & iter);	///< operator !=
};

#include "light_iterator.tpp"

#endif

