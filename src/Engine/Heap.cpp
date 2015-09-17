#include "Heap.h"

Heap * Heap::ptr = nullptr;

Heap * Heap::GetPtr()
{
	if(ptr == nullptr)
		ptr = new Heap;

	return ptr;
}

void Heap::Free()
{
	if(ptr != nullptr)
		delete ptr;
}

