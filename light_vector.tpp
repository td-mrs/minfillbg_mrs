#include <cstdlib>

//-----------------------------
// constructors and destructor
//-----------------------------

template <class T>
Light_Vector<T>::Light_Vector ()
// constructs an empty vector
{
	capacity = 0;
	data = 0;
}


template <class T>
Light_Vector<T>::Light_Vector (int n)
// constructs a vector of capacity n
{
	capacity = n;
	data = new T [n];
}
	

template <class T>
Light_Vector<T>::Light_Vector (int n, T default_value)
// constructs a vector of capacity n and initializes each element to default_value
{
	capacity = n;
	data = new T [n];
	for (int i = 0; i < n; i++)
		data[i] = default_value;
}


template <class T>
Light_Vector<T>::Light_Vector (Light_Vector<T> & v)
// constructs a vector by copying the vector v
{
	capacity = v.capacity;
	data = new T [capacity];
	
	for (int i = 0; i < capacity; i++)
		data[i] = v.data[i];
}


template <class T>
Light_Vector<T>::Light_Vector (const Light_Vector<T> & v)
// constructs a vector by copying the vector v
{
	capacity = v.capacity;
	data = new T [capacity];
	
	for (int i = 0; i < capacity; i++)
		data[i] = v.data[i];
}


template <class T>
Light_Vector<T>::~Light_Vector ()
// destructor
{
	delete [] data;
}


//-----------
// iterators
//-----------


template <class T>
inline Light_Iterator<T> Light_Vector<T>::begin()
// returns an iterator referring to the first element of the set
{
	return Light_Iterator<T> (this);
}


template <class T>
inline Light_Iterator<T> Light_Vector<T>::end()
// returns an iterator referring to the position after the last element of the set
{
	return Light_Iterator<T> (this,capacity);
}


//-----------
// operators
//-----------


template <class T>
Light_Vector<T> & Light_Vector<T>::operator= (const Light_Vector<T> & v)
// operator =
{
	if (this != &v)
	{
		if (capacity != v.capacity)
		{
			delete [] data;
			capacity = v.capacity;
			data = new T [capacity];
		}
		
		for (int i = 0; i < capacity; i++)
			data[i] = v.data[i];
	}
	return *this;
}


template <class T>
inline T& Light_Vector<T>::operator[](int n)
// operator []
{
	return data[n];
}


template <class T>
inline const T& Light_Vector<T>::operator[] (int n) const
// operator []
{
	return data[n];
}


//-----------------
// basic functions
//-----------------

template <class T>
inline int Light_Vector<T>::get_capacity ()
// returns the capacity of the vector
{
	return capacity;
}


template <class T>
void Light_Vector<T>::expand (int n)
// expands the vector by adding n elements at the end of the vector
{
	if (n > 0)
	{
		T * old_data = data;
		data = new T [capacity+n];
		for (int i = 0; i < capacity; i++)
			data[i] = old_data[i];
		
		delete [] old_data;
		
		capacity += n;
	}
}


template <class T>
void Light_Vector<T>::expand (int n, T default_value)
// expands the vector by adding n elements at the end of the vector and initializes each new element to default_value
{
	if (n > 0)
	{
		T * old_data = data;
		
		data = new T [capacity+n];
		for (int i = 0; i < capacity; i++)
			data[i] = old_data[i];

		for (int i = 0; i < n; i++)
			data[i+capacity] = default_value;
		
		delete [] old_data;
		
		capacity += n;
	}
}


template <class T>
void Light_Vector<T>::swap (int i, int j)
// swaps the values at indices i and j
{
	T tmp = data[i];;
	data[i] = data[j];
	data[j] = tmp;
}


template <class T>
void Light_Vector<T>::push_back (T val)
// adds the value val at this end of the vector
{
	expand (1);
	data[capacity-1] = val;
}


template <class T>
void Light_Vector<T>::erase (T val)
// removes the value val from the vector
{
	int i = 0;
	
	while ((i < capacity) && (data[i] != val))
		i++;
	
	if (i < capacity)
	{
		capacity--;
		while (i < capacity)
		{
			data[i] = data[i+1];
			i++;
		}
	}
}
