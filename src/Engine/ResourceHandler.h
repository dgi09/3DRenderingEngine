#pragma once 
#include "Common.h"
#include "ResourcePool.h"


template <class T>
class EXPORT ResourceHandler
{
protected:
	T resource;
	ResourcePool<unsigned int> * pool;
	unsigned int id;
	bool containsObject;
public:
	ResourceHandler();
	ResourceHandler(T res,unsigned int id,ResourcePool<unsigned int> * pool);
	ResourceHandler(bool containsObject);
	virtual void Destroy() = 0;
	T Get();
	bool ContainsObject();
};

template <class T>
ResourceHandler<T>::ResourceHandler()
{

}

template <class T>
bool ResourceHandler<T>::ContainsObject()
{
	return containsObject;
}

template <class T>
ResourceHandler<T>::ResourceHandler(bool containsObject)
{
	this->containsObject = containsObject;
}

template <class T>
ResourceHandler<T>::ResourceHandler(T  res,unsigned int id,ResourcePool<unsigned int> * pool)
{
	resource = res;
	this->id = id;
	this->pool = pool;
	containsObject = true;
}

template <class T>
T ResourceHandler<T>::Get()
{
	return resource;
}