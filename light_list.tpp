#include <cstdlib>

//-----------------------------
// constructors and destructor
//-----------------------------

template <class T>
Light_List<T>::Light_List ()
// constructs an empty list
{
	first = 0;
	last = 0;
}


template <class T>
Light_List<T>::Light_List (Light_List<T> & l)
// constructs a list by copying the list v
{
	first = 0;
	last = 0;
	
	Node * q;
	q = l.first;
	
	Node * p;
	while (q != 0)
	{
		p = new Node;
		p->value = q->value; 
		p->next = 0;
		if (first == 0)
			first = p;
		else last->next = p;
		last = p;
		q = q->next;
	}
}


template <class T>
Light_List<T>::Light_List (const Light_List<T> & l)
// constructs a List by copying the list v
{
	first = 0;
	last = 0;
	
	Node * q;
	q = l.first;
	
	Node * p;
	while (q != 0)
	{
		p = new Node;
		p->value = q->value; 
		p->next = 0;
		if (first == 0)
			first = p;
		else last->next = p;
		last = p;
		q = q->next;
	}
}


template <class T>
Light_List<T>::~Light_List ()
// destructor
{
	Node * q = first;
	Node * p;
	
	while (q != 0)
	{
		p = q;
		q = q->next;
		delete p;
	}
}


//-----------
// operators
//-----------

template <class T>
Light_List<T> & Light_List<T>::operator= (const Light_List<T> & l)
// operator =
{
	if (this != &l)
	{
		// we remove the current list
		Node * q = first;
		Node * p;
		
		while (q != 0)
		{
			p = q;
			q = q->next;
			delete p;
		}
		first = 0;
		last = 0;
		
		// we build the new list by copying the list l
		q = l.first;
		
		while (q != 0)
		{
			p = new Node;
			p->value = q->value; 
			p->next = 0;
			if (first == 0)
				first = p;
			else last->next = p;
			last = p;
			q = q->next;
		}
	}
	return *this;
}


//-----------
// iterators
//-----------


template <class T>
inline typename Light_List<T>::iterator Light_List<T>::begin ()
// returns an iterator referring to the first node in the list
{
	return Light_List_Iterator<T> (this);
}

template <class T>
inline typename Light_List<T>::iterator Light_List<T>::end ()
// returns an iterator referring to the position after the last node of the list
{
	return Light_List_Iterator<T> (this,false);
}


//-----------------
// basic functions
//-----------------


template <class T>
inline bool Light_List<T>::empty ()
// returns true if the list is empty, false otherwise
{
	return first == 0;
}



template <class T>
inline void Light_List<T>::push_front (T t)
// adds the value t at the begin of the list
{
	Node * p = new Node;
	p->value = t; 
	p->next = first;
	first = p;
	if (last == 0)
		last = p;
}


template <class T>
inline void Light_List<T>::push_front (Light_List<T>::iterator iter)
// adds the element referred by the iterator iter at the begin of the list
{
	iter.current_pos->next = first;
	first = iter.current_pos;
	if (last == 0)
		last = iter.current_pos;
}


template <class T>
inline void Light_List<T>::push_back (T t)
// adds the value t at the end of the list
{
	Node * p = new Node;
	p->value = t; 
	p->next = 0;
	if (first == 0)
		first = p;
	else last->next = p;
	last = p;
}


template <class T>
inline void Light_List<T>::push_back (Light_List<T>::iterator iter)
// adds the element referred by the iterator iter at the end of the list
{
	iter.current_pos->next = 0;
	if (first == 0)
		first = iter.current_pos;
	else last->next = iter.current_pos;
	last = iter.current_pos;
}


template <class T>
void Light_List<T>::erase (Light_List<T>::iterator & iter)
// removes the element referred by the iterator iter
{
	if ((iter.object == this) && (iter.current_pos != 0))
	{
		Node * p = iter.current_pos;
		
		if (iter.prec_pos == 0)
		{
			first = first->next;
			if (first == 0)
				last = 0;
			iter.current_pos = first;
		}
		else
			{
				iter.prec_pos->next = p->next;
				iter.current_pos = p->next;
				
				if (last == p)
					last = iter.prec_pos;
			}
			delete p;
	}
}


template <class T>
void Light_List<T>::skip (Light_List<T>::iterator & iter)
// removes the element referred by the iterator iter from the list but does not destroy the objectvoid skip (Light_List<T>::iterator iter);			// removes the element referred by the iterator iter from the list but does not destroy the object
{
	if ((iter.object == this) && (iter.current_pos != 0))
	{
		Node * p = iter.current_pos;
		
		if (iter.prec_pos == 0)
		{
			first = first->next;
			if (first == 0)
				last = 0;
			iter.current_pos = first;
		}
		else
			{
				iter.prec_pos->next = p->next;
				iter.current_pos = p->next;
				
				if (last == p)
					last = iter.prec_pos;
			}
	}
	else throw ("PB");
}


template <class T>
void Light_List<T>::remove (T t)
// removes the element t from the list
{
	if (first != 0)
	{
		if (first->value == t)
		{
			// the value t corresponds to the first element of the list
			Node * p = first;
			first = first->next;
			if (first == 0)  last = 0;			// case where the removed node is the last and unique node of the list
			
			delete p; 
		}
		else
			{
				Node * p = first->next;
				Node * prev = first;
				while ((p != 0) && (p->value != t))
				{
					prev = p;
					p = p->next;
				}
				if (p != 0)
				{
					prev->next = p->next;
					if (p == last)  last = prev;		// case where the removed node is the last node of the list
						
					delete p;
				}
			}
	}
}


template <class T>
void Light_List<T>::clear ()
// removes all the elements of the list
{
	Node * q = first;
	Node * p;
	
	while (q != 0)
	{
		p = q;
		q = q->next;
		delete p;
	}
	
	first = 0;
	last = 0;
}
