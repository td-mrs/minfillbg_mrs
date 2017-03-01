/// \file 
/// \brief Definitions related to the Light_Stack class

#ifndef LIGHT_STACK_H
#define LIGHT_STACK_H

using namespace std;

#include <light_vector.h>

template <class T>
class Light_Stack: public Light_Vector<T>		/// This class allows to represent stacks of elements (each element being of type T)
{
	protected:
		int top_index;				///< the index of the top of the stack
		
	public:
		// constructors
		Light_Stack ();				///< constructs an empty stack
		Light_Stack (int n);	///< constructs an empty stack with at most n elements
				
		// basic functions
		int size ();					///< returns the size of stack
		T top ();							///< returns the element at the top of the stack
		void push (T value);  ///< pushes the element value in the stack
		void pop (); 					///< removes the element at the top of the stack
		bool is_empty ();			///< returns true if the stack is empty, false otherwise
		void clear ();				///< removes all the elements of the stack
};

#include "light_stack.tpp"

#endif

