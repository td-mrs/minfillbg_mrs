/// \file 
/// \brief Definitions related to the Light_List class

#ifndef LIGHT_LIST_H
#define LIGHT_LIST_H

using namespace std;

#include <light_list_iterator.h>

template <class T>
class Light_List						/// This class allows to represent lists of elements (each element being of type T)
{
	friend class Light_List_Iterator<T>;
	
	protected:
		typedef struct node			/// allows to represent chain lists
		{
			T value;							///< value of the node
			struct node * next;		///< pointer on the next node
		} Node;		///< type representing chain lists

		Node * first;			///< pointer on the first element of the list
		Node * last;			///< pointer on the first element of the list
		
		
	public:
		// constructors and destructor
		Light_List ();													///< constructs an empty list
		Light_List (Light_List<T> & l); 				///< constructs a list by copying the list v
		Light_List (const Light_List<T> & l); 	///< constructs a List by copying the list v
		~Light_List ();													///< destructor
		
		// operators
		Light_List<T> & operator= (const Light_List<T> & l);	///< operator =
		
		// iterators
		typedef Light_List_Iterator<T> iterator;		///< type for iterators on list
		Light_List<T>::iterator begin (); ///< returns an iterator referring to the first node in the list
		Light_List<T>::iterator end ();   ///< returns an iterator referring to the position after the last node of the list
		
		// basic functions
		bool empty ();																	///< returns true if the list is empty, false otherwise
		void push_front (T t);													///< adds the value t at the begin of the list
		void push_front (Light_List<T>::iterator iter);	///< adds the element referred by the iterator iter at the begin of the list
		void push_back (T t);														///< adds the value t at the end of the list
		void push_back (Light_List<T>::iterator iter);	///< adds the element referred by the iterator iter at the end of the list
		void erase (Light_List<T>::iterator & iter);		///< removes the element referred by the iterator iter and destroys the object
		void skip (Light_List<T>::iterator & iter);			///< removes the element referred by the iterator iter from the list but does not destroy the object
		void remove (T t);															///< removes the element t from the list
		void clear ();																	///< removes all the elements of the list
};


#include "light_list.tpp"

#endif

