//--------------
// constructors
//--------------

template <class T>
Light_Stack<T>::Light_Stack ()
// constructs an empty stack
{
	top_index = -1;
}


template <class T>
Light_Stack<T>::Light_Stack (int n) : Light_Vector<T> (n)
// constructs an empty stack with at most n elements
{
	top_index = -1;
}


		
//-----------------
// basic functions
//-----------------


template <class T>
inline int Light_Stack<T>::size ()
// returns the size of stack
{
	return top_index+1;
}


template <class T>
inline T Light_Stack<T>::top ()
// returns the element at the top of the stack
{
	return Light_Stack::data[top_index];
}


template <class T>
inline void Light_Stack<T>::push (T value)
// pushes the element value in the stack
{
	top_index++;
	Light_Stack::data[top_index] = value;
}


template <class T>
inline void Light_Stack<T>::pop ()
// removes the element at the top of the stack
{
	top_index--;
}


template <class T>
inline bool Light_Stack<T>::is_empty ()
// returns true if the stack is empty, false otherwise
{
	return top_index == -1;
}


template <class T>
inline void Light_Stack<T>::clear ()
// removes all the elements of the stack
{
	top_index = -1;
}
