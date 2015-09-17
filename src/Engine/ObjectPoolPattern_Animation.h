#pragma once 
#include "Common.h"
#include "ObjectPoolPattern.h"
#include "Heap.h"
#include "AnimationPtr.h"

template <class Key>
class EXPORT ObjectPoolPattern_Animation : public ObjectPoolPattern<Key,AnimationPtr>
{
protected:
	void DeleteVal(AnimationPtr value);
};

template <class Key>
void ObjectPoolPattern_Animation<Key>::DeleteVal(AnimationPtr value)
{
	value.Delete();
}
