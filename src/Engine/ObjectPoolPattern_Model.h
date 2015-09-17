#pragma once 
#include "Common.h"
#include "ObjectPoolPattern.h"
#include "Heap.h"
#include "ModelPtr.h"

template <class Key>
class EXPORT ObjectPoolPattern_Model : public ObjectPoolPattern<Key,ModelPtr>
{
protected:
	void DeleteVal(ModelPtr value);
};

template <class Key>
void ObjectPoolPattern_Model<Key>::DeleteVal(ModelPtr value)
{
	value.Delete();
}