/// \file 
/// \brief Definitions related to the Light_List_Iterator class

#ifndef LIGHT_LIST_ITERATOR_H
#define LIGHT_LIST_ITERATOR_H

using namespace std;

template <class T>
class Light_List;

template <class T>
class Light_List_Iterator			/// This class allows to represent iterators on lists of elements (each element being of type T)
{
	friend class Light_List<T>;
	
	protected:
		Light_List<T> * object;		///< the object to which the iterator is related
		typename Light_List<T>::Node * current_pos;					///< the current position in the object
		typename Light_List<T>::Node * prec_pos;						///< the position preceding the the current position in the object, 0 if the current position corresponds to the first element in the list
		
	public:
		// constructors
		Light_List_Iterator ();											///< constructs an empty iterator
		Light_List_Iterator (Light_List<T> * o, bool at_begin=true);		///< constructs an iterator on the object o for which the current position is set to the first node of the list if at_begin is true, to 0 otherwise
		Light_List_Iterator (const Light_List_Iterator<T> & iter);			///< constructs an iterator by copying the iterator iter
		
				
		// operators
		Light_List_Iterator<T> & operator= (const Light_List_Iterator<T> & iter);	///< operator =
		Light_List_Iterator<T> & operator++ (int);							///< operator ++
		T & operator* ();																				///< operator *
		bool operator== (const Light_List_Iterator<T> & iter);	///< operator ==
		bool operator!= (const Light_List_Iterator<T> & iter);	///< operator !=

};

#include "light_list_iterator.tpp"

#endif

