#pragma once 
#include "Common.h"
#include "ObjectPoolPattern.h"
#include "Heap.h"
#include "SkeletonPtr.h"

template <class Key>
class EXPORT ObjectPoolPattern_Skeleton : public ObjectPoolPattern<Key,SkeletonPtr>
{
protected:
	void DeleteVal(SkeletonPtr value);
};

template <class Key>
void ObjectPoolPattern_Skeleton<Key>::DeleteVal(SkeletonPtr value)
{
	value.Delete();
}
