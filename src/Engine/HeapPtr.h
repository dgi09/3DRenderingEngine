#pragma once 
#include "Common.h"

template <class T>
class EXPORT HeapPtr
{
protected:
	unsigned int index;
	bool isNull;
public:
	HeapPtr(unsigned int index);
	HeapPtr();
	HeapPtr(bool isNull);

	bool IsNull();
	virtual T * Get() = 0;

	virtual void Delete() = 0;

	bool operator==(HeapPtr<T> & cmp);
};

template <class T>
bool HeapPtr<T>::operator==(HeapPtr<T> & cmp)
{
	return index == cmp.index;
}



template <class T>
bool HeapPtr<T>::IsNull()
{
	return isNull;
}

template <class T>
HeapPtr<T>::HeapPtr(bool isNull)
{
	this->isNull = isNull;
}

template <class T>
HeapPtr<T>::HeapPtr()
{

}

template <class T>
HeapPtr<T>::HeapPtr(unsigned int index)
{
	this->index = index;
	isNull = false;
}
