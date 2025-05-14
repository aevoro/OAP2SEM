#include "heap.h"
#include <iostream>
#include <iomanip>
void AAA::print()
{
	std::cout << x;
}
namespace heap
{
	Heap create(int maxsize, CMP(*f)(void*, void*))
	{
		return *(new Heap(maxsize, f));
	}
	int Heap::left(int ix) {
		return (2 * ix + 1 < size) ? (2 * ix + 1) : -1;
	}

	int Heap::right(int ix) {
		return (2 * ix + 2 < size) ? (2 * ix + 2) : -1;
	}
	int Heap::parent(int ix)
	{
		return (ix + 1) / 2 - 1;
	}
	void Heap::swap(int i, int j)
	{
		void* buf = storage[i];
		storage[i] = storage[j];
		storage[j] = buf;
	}
	void Heap::heapify(int ix)
	{
		int l = left(ix);
		int r = right(ix);
		int largest = ix;

		if (l != -1 && isGreat(storage[l], storage[largest])) {
			largest = l;
		}
		if (r != -1 && isGreat(storage[r], storage[largest])) {
			largest = r;
		}

		if (largest != ix) {
			swap(ix, largest);
			heapify(largest);
		}
	}
	void Heap::insert(void* x)
	{
		if (!isFull()) {
			int i = size;
			storage[size++] = x;
			while (i > 0 && isGreat(storage[i], storage[parent(i)])) {
				swap(i, parent(i));
				i = parent(i);
			}
		}
	}
	void* Heap::extractMax()
	{
		void* rc = nullptr;
		if (!isEmpty())
		{
			rc = storage[0];
			storage[0] = storage[size - 1];
			size--;
			heapify(0);
		} return rc;
	}

	int Heap::height(int index = 0) {
		if (index >= size || index == -1) return 0;
		return 1 + std::max(height(left(index)), height(right(index)));
	}

	void Heap::scan(int i) const
	{
		int probel = 20;
		std::cout << '\n';
		if (size == 0)
			std::cout << "Куча пуста";
		for (int u = 0, y = 0; u < size; u++)
		{
			std::cout << std::setw(probel + 10) << std::setfill(' ');
			((AAA*)storage[u])->print();
			if (u == y)
			{
				std::cout << '\n';
				if (y == 0)
					y = 2;
				else
					y += y * 2;
			}
			probel /= 2;
		}
		std::cout << '\n';
	}

	void Heap::extractMin() {
		if (isEmpty()) {
			std::cout << "Куча пуста!" << std::endl;
			return;
		}
		int minIdx = size / 2;
		for (int i = minIdx + 1; i < size; ++i) {
			if (isLess(storage[i], storage[minIdx])) {
				minIdx = i;
			}
		}

		swap(minIdx, size - 1);
		size--;
		heapify(minIdx);
	}

	void Heap::extractI(int i) {
		if (i < 0 || i >= size) return;

		swap(i, size - 1);
		size--;
		heapify(i);
		while (i > 0 && isGreat(storage[i], storage[parent(i)])) {
			swap(i, parent(i));
			i = parent(i); 
		}
	}

	void Heap::unionHeap(Heap& other)
	{
		for (int i = 0; i < other.size && size < maxSize; ++i)
		{
			insert(other.storage[i]);
		}
		other.size = 0;
	}
}
