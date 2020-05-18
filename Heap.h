#pragma once

#include "Vector.h"

template <typename T>
class Heap
{
public:
	Heap(bool ismin = false) : ismin(ismin), length(0) {}

	Heap(const Vector<T> &d, const bool ismin = true) : ismin(ismin),
		data(d),
		length(d.getSize())
	{
		for (int i = length / 2 - 1; i >= 0; i--)
			fix_down(i);
	}

	Heap &push(const T &t)
	{
		length++;
		if (length <= data.getSize())
			data[length - 1] = t;
		else
			data.addAtEnd(t);
		fix_up(length - 1);

		return *this;
	}

	Heap &pop()
	{
		swap(data[0], data[--length]);
		fix_down(0);
		return *this;
	}

	const T& top()
	{
		return data[0];
	}

	static void sort(Vector<T> &d, bool reversed = false)
	{
		Heap<T> h(d, reversed);
		for (int i = 0; i < d.getSize(); i++) {
			d[i] = h.top();
			h.pop();
		}
	}

	int size()
	{
		return length;
	}
private:
	bool ismin;
	Vector<T> data;
	int length;
	bool greater(const T& t1, const T& t2)
	{
		if (ismin)
			return t1 < t2;
		else
			return t1 > t2;
	}

	static int left(int i) { return 2 * i + 1; }
	static int right(int i) { return 2 * i + 2; }
	static int parent(int i) { return (i - 1) / 2; }

	void fix_up(int i)
	{
		for (int j = parent(i); (j >= 0) && greater(data[j], data[i]); i = j, j = parent(i))
			swap(data[i], data[j]);
	}

	void fix_down(int i)
	{
		T tmp = data[i];
		int j = left(i);

		while (j < length) {
			if (j + 1 < length && greater(data[j], data[j + 1])) j++;

			if (greater(tmp, data[j])) {
				data[i] = data[j];
				i = j;
				j = left(i);
			}
			else {
				break;
			}
		}
		data[i] = tmp;
	}
};