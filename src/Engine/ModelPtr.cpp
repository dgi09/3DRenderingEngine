#include "ModelPtr.h"
#include "Heap.h"

ModelPtr::ModelPtr()
{

}

ModelPtr::ModelPtr(unsigned int index) : HeapPtr(index)
{

}

ModelPtr::ModelPtr(bool isNull) : HeapPtr(isNull)
{

}

Model * ModelPtr::Get()
{
	return Heap::GetPtr()->Models.Get(index);
}

void ModelPtr::Delete()
{
	Heap::GetPtr()->Models.Get(index)->Destroy();
	Heap::GetPtr()->Models.Delete(index);
}
