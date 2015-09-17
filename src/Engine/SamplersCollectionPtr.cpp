#include "SamplersCollectionPtr.h"
#include "Heap.h"

SamplersCollectionPtr::SamplersCollectionPtr(unsigned int index) : HeapPtr(index)
{
}

SamplersCollectionPtr::SamplersCollectionPtr()
{

}

SamplersCollectionPtr::SamplersCollectionPtr(bool isNull) : HeapPtr(isNull)
{

}

SamplersCollection * SamplersCollectionPtr::Get()
{
	return Heap::GetPtr()->SamplersCollections.Get(index);
}

void SamplersCollectionPtr::Delete()
{
	Heap::GetPtr()->SamplersCollections.Get(index)->Destroy();
	Heap::GetPtr()->SamplersCollections.Delete(index);
}
