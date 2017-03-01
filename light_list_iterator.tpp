//--------------
// constructors
//--------------

template <class T>
Light_List_Iterator<T>::Light_List_Iterator ()
// constructs an empty iterator
{
	object = 0;
	current_pos = 0;
	prec_pos = 0;
}


template <class T>
Light_List_Iterator<T>::Light_List_Iterator (Light_List<T> * o, bool at_begin)
// constructs an iterator on the object o for which the current position is set to the first node of the list if at_begin is true, to 0 otherwise
{
	object = o;
	if (at_begin)
	{
		current_pos = o->first;
		prec_pos = 0;
	}
	else 
		{
			current_pos = 0;
			prec_pos = o->last;
		}
}


template <class T>
Light_List_Iterator<T>::Light_List_Iterator (const Light_List_Iterator<T> & iter)
// constructs an iterator by copying the iterator iter
{
	object = iter.object;
	current_pos = iter.current_pos;
	prec_pos = iter.prec_pos;
}


//-----------		
// operators
//-----------

template <class T>
inline Light_List_Iterator<T> & Light_List_Iterator<T>::operator= (const Light_List_Iterator<T> & iter)
// operator =
{
	if (this != &iter)
	{
		object = iter.object;
		current_pos = iter.current_pos;
		prec_pos = iter.prec_pos;
	}
	return *this;	
}


template <class T>
inline Light_List_Iterator<T> & Light_List_Iterator<T>::operator++ (int)
// operator ++
{
	if (current_pos != 0)
	{
		prec_pos = current_pos;
		current_pos =	current_pos->next;
	}
	return *this;
}


template <class T>
inline T & Light_List_Iterator<T>::operator* ()
// operator *
{
	if (current_pos != 0)
		return current_pos->value;
	else throw ("Error: no possible value for the iterator");
}


template <class T>
inline bool Light_List_Iterator<T>::operator== (const Light_List_Iterator<T> & iter)
// operator ==
{
	return ((object == iter.object) && (current_pos == iter.current_pos));
}


template <class T>
inline bool Light_List_Iterator<T>::operator!= (const Light_List_Iterator<T> & iter)
// operator !=
{
	return ((object != iter.object) || (current_pos != iter.current_pos));
}
