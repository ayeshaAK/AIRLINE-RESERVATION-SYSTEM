#pragma once

template <typename T>
class Vector
{
private:
	unsigned int size; //no of meaningful entries in array
	unsigned int capacity; //no of entries that can be made in the array
	T* array;
public:
	Vector(int capacity = 10) :size(0), capacity(capacity), array(new T[capacity]) {}
	Vector(T* a, unsigned int size) :size(0), capacity(size), array(new T[capacity])
	{
		for (unsigned int i = 0; i<size; i++)
		{
			addAtEnd(a[i]);
		}
	}
	Vector(const Vector<T>& obj)
	{
		array = NULL;
		*this = obj;
	}
	const Vector<T>& operator = (const Vector<T>& obj)
	{
		if (this == &obj)
			return *this;
		capacity = obj.capacity;
		size = obj.size;
		if (array) delete[]array;
		array = new T[capacity];
		for (unsigned int i = 0; i<size; i++)
		{
			array[i] = obj.array[i];
		}
		return *this;
	}
	bool isEmpty()
	{
		return !size;
	}
	void addAtEnd(T element)
	{
		if (size >= capacity)
		{
			T* temp = new T[capacity * 2];
			for (unsigned int i = 0; i<size; i++)
			{
				temp[i] = array[i];
			}
			if (array) delete[] array;
			array = temp;
			capacity *= 2;
		}
		array[size++] = element;
	}
	T& operator[] (unsigned int i) const
	{
		if (i<size)
			return array[i];
		cout << "out of bound error\n";
	}
	unsigned int getSize() {
		return size;
	}
	bool operator==(const Vector<T>& obj)
	{
		if (size != obj.size)
			return false;
		for (unsigned int i = 0; i<size; i++)
		{
			if (array[i] != obj.array[i])
				return false;
		}
		return true;
	}
	const T& removeLast()
	{
		size--;
		return array[size];
	}
	void clear()
	{
		size = 0;
	}
	bool operator<(const Vector<T>& obj) const 
	{
		for (unsigned int i = 0; i<size && i<obj.size; i++)
		{
			if (array[i]>obj.array[i])
				return false;
			else if (array[i]<obj.array[i])
				return true;
		}
		if (size<obj.size)
			return true;
		return false;
	}
	bool operator>(const Vector<T>& obj)const 
	{
		for (unsigned int i = 0; i<size && i<obj.size; i++)
		{
			if (array[i]<obj.array[i])
				return false;
			else if (array[i]>obj.array[i])
				return true;
		}
		if (size>obj.size)
			return true;
		return false;
	}
	bool remove(const T& obj)
	{
		unsigned int i = 0;
		for (;i<size; i++)
		{
			if (array[i] == obj)
				break;
		}
		if (i == size)
			return false; //object not found in array
		for (unsigned int j = i; j<size - 1; j++)
			array[j] = array[j + 1];
		size--;
		return true;
	}
	bool removeByIndex(unsigned int i)
	{
		if (i > size)
			return false;
		int k = 0;
		for (unsigned int j = 0; j<size; j++) {
			if (j != i) {
				array[k] = array[j];
				k++;
			}
		}
		size--;
		return true;
	}
	bool isPresent(const T& element) //gives the index at which element is present. if not present, returns -1
	{
		for (unsigned int i = 0; i<size; i++)
		{
			if (array[i] == element)
			{
				return true;
			}
		}
		return false;
	}
	~Vector()
	{
		if (array) delete[] array;
	}
};

template <typename T, typename U>
T& operator<<(T& o, Vector<U> array)
{
	for (unsigned int i = 0; i<array.getSize(); i++)
	{
		o << array[i];//<<endl;
	}
	o << endl;
	return o;
}
