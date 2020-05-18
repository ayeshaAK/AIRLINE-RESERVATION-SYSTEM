#pragma once

template <typename T>
class ArrayBasedSet
{
	//a usual set, which returns false on insertion if the element already exists
	Vector<T> elements;
public:
	ArrayBasedSet() {}
	ArrayBasedSet(const ArrayBasedSet<T>& obj)
	{
		*this = obj;
	}
	const ArrayBasedSet<T>& operator=(const ArrayBasedSet<T>& obj)
	{
		if (this == &obj)
			return *this;
		elements = obj.elements;
		return *this;
	}
	void clear()
	{
		elements.clear();
	}
	bool addElement(const T& element)
	{
		int index = presentAt(element);       //presentAt returns -1 if the element does not exist
		if (index + 1)
		{
			return false;					//element already exist
		}
		else
		{
			elements.addAtEnd(element);
			return true;
		}
	}
	bool removeElement(T element)
	{
		return elements.remove(element);
	}
	bool removeByIndex(int index)
	{
		return elements.removeByIndex(index);
	}
	int presentAt(const T& element) //gives the index at which element is present. if not present, returns -1
	{
		for (unsigned int i = 0; i<elements.getSize(); i++)
		{
			if (elements[i] == element)
			{
				return i;
			}
		}
		return -1;
	}
	void display()
	{
		for (unsigned int i = 0; i<elements.getSize(); i++)
		{
			elements[i].display();
		}
		cout << endl;
	}
	unsigned int getSize()
	{
		return elements.getSize();
	}
	T& operator [] (unsigned int x)
	{
		if (x<elements.getSize())
			return elements[x];
		cout << "out of bound error\n";
	}
	~ArrayBasedSet() {}
};