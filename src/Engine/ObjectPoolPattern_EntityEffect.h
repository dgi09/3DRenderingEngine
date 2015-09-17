#pragma once 
#include "Common.h"
#include "ObjectPoolPattern.h"
#include "Heap.h"
#include "EntityEffectPtr.h"

template <class Key>
class EXPORT ObjectPoolPattern_EntityEffect : public ObjectPoolPattern<Key,EntityEffectPtr>
{
protected:
	void DeleteVal(EntityEffectPtr value);
};

template <class Key>
void ObjectPoolPattern_EntityEffect<Key>::DeleteVal(EntityEffectPtr value)
{
	value.Delete();
}
