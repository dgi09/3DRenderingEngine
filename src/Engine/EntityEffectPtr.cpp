#include "EntityEffectPtr.h"
#include "Heap.h"

EntityEffectPtr::EntityEffectPtr()
{

}

EntityEffectPtr::EntityEffectPtr(unsigned int index) : HeapPtr(index)
{

}

EntityEffectPtr::EntityEffectPtr(bool isNull) : HeapPtr(isNull)
{

}


EntityEffect * EntityEffectPtr::Get()
{
	return Heap::GetPtr()->EntityEffects.Get(index);
}

void EntityEffectPtr::Delete()
{
	Heap::GetPtr()->EntityEffects.Get(index)->Destroy();
	Heap::GetPtr()->EntityEffects.Delete(index);
}
