#pragma once 
#include "ObjectPool.h"
#include "Scene.h"

template <class T>
class SceneObjectPtr
{
	unsigned int index;
	ObjectPool<T> * pool;
	bool isNull;
public:
	SceneObjectPtr();
	SceneObjectPtr(unsigned int index,ObjectPool<T> * pool);
	SceneObjectPtr(bool isNull);

	T * Get();
	bool IsNull();

	bool operator==(SceneObjectPtr<T> & obj);
protected:
	friend class Scene;
	unsigned int GetIndex();
};

template <class T>
bool SceneObjectPtr<T>::operator==(SceneObjectPtr<T> & obj)
{
	return obj.index == index;
}

template <class T>
bool SceneObjectPtr<T>::IsNull()
{
	return isNull;
}

template <class T>
unsigned int SceneObjectPtr<T>::GetIndex()
{
	return index;
}

template <class T>
T * SceneObjectPtr<T>::Get()
{
	return pool->Get(index);
}

template <class T>
SceneObjectPtr<T>::SceneObjectPtr(bool isNull)
{
	this->isNull = isNull;
}

template <class T>
SceneObjectPtr<T>::SceneObjectPtr(unsigned int index,ObjectPool<T> * pool)
{
	isNull = false;
	this->index = index;
	this->pool = pool;
}

template <class T>
SceneObjectPtr<T>::SceneObjectPtr()
{

}
