#pragma once 

#include "Common.h"
#include <stdio.h>

template <class T>
class EXPORT ObjectPool 
{
	unsigned int size;
	T * mem;
	bool * used;
	unsigned int allocatedObjects;
public:
	ObjectPool();
	~ObjectPool();

	void Allocate(unsigned int size);
	unsigned int New();
	void Delete(unsigned int index);
	void DeleteAll();
	T * Get(unsigned int index);

private:
	void Resize(unsigned int size);
};

template <class T>
void ObjectPool<T>::DeleteAll()
{
	for(int i = 0;i < size;i++)
	{
		used[i] = false;
	}
}


template <class T>
ObjectPool<T>::~ObjectPool()
{
	if(mem != nullptr)
		delete[] mem;

	if(used != nullptr)
		delete[] used;
}

template <class T>
ObjectPool<T>::ObjectPool()
{
	mem = nullptr;
	used = nullptr;
	allocatedObjects = 0;
}

template <class T>
void ObjectPool<T>::Resize(unsigned int size)
{
	T * memTemp = new T[size];
	bool * usedTemp = new bool[size];

	for(int i = 0; i < size;i++)
	{
		if(i < this->size)
			usedTemp[i] = true;
		else usedTemp[i] = false;
	}

	memcpy(memTemp,mem,sizeof(T) * this->size);
	memcpy(usedTemp,used,sizeof(bool) * this->size);

	delete[] mem;
	delete[] used;
	mem = memTemp;
	used = usedTemp;

	this->size = size;
}

template <class T>
T * ObjectPool<T>::Get(unsigned int index)
{
	return &mem[index];
}

template <class T>
void ObjectPool<T>::Delete(unsigned int index)
{
	used[index] = false;
}

template <class T>
unsigned int ObjectPool<T>::New()
{
	if(allocatedObjects == size)
		Resize(size * 2);

	for(int i = 0 ;i < size;i++)
	{
		if(used[i] == false)
		{
			used[i] = true;
			allocatedObjects++;
			return i;
		}
	}

	return -1;
}

template <class T>
void ObjectPool<T>::Allocate(unsigned int size)
{

	this->size = size;
	mem = new T[size];
	used = new bool[size];

	memset(used,0,sizeof(bool) * size);
}
