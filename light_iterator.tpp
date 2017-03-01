//--------------
// constructors
//--------------

template <class T>
Light_Iterator<T>::Light_Iterator ()
// constructs an empty iterator
{
	object = 0;
	current_pos = 0;
}


template <class T>
Light_Iterator<T>::Light_Iterator (Light_Vector<T> * o, int initial_pos)
// constructs an iterator on the object o for which the current pos is set to initial_pos
{
	object = o;
	current_pos = initial_pos;
}

template <class T>
Light_Iterator<T>::Light_Iterator (const Light_Iterator & iter)
// constructs an iterator by copying the iterator iter
{
	object = iter.object;
	current_pos = iter.current_pos;
}


//-----------
// operators
//-----------


template <class T>
inline Light_Iterator<T> & Light_Iterator<T>::operator= (const Light_Iterator<T> & iter)
// operator =
{
	if (this != &iter)
	{
		object = iter.object;
		current_pos = iter.current_pos;
	}
	return *this;
}


template <class T>
inline Light_Iterator<T> & Light_Iterator<T>::operator++ (int)
// operator ++
{
	current_pos++;
	return *this;
}


template <class T>
inline T & Light_Iterator<T>::operator* ()
// operator *
{
	return (*object)[current_pos];
}


template <class T>
inline bool Light_Iterator<T>::operator== (const Light_Iterator<T> & iter)
// operator ==
{
	return ((object == iter.object) && (current_pos == iter.current_pos));
}


template <class T>
inline bool Light_Iterator<T>::operator!= (const Light_Iterator<T> & iter)
// operator !=
{
	return ((object != iter.object) || (current_pos != iter.current_pos));
}
