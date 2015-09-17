#include "BuffersCollectionPtr.h"
#include "BuffersCollection.h"
#include "Heap.h"

BuffersCollectionPtr::BuffersCollectionPtr(unsigned int index): HeapPtr(index)
{
	
}

BuffersCollectionPtr::BuffersCollectionPtr()
{

}

BuffersCollectionPtr::BuffersCollectionPtr(bool isNull) : HeapPtr(isNull)
{

}

BuffersCollection * BuffersCollectionPtr::Get()
{
	return Heap::GetPtr()->BuffersCollections.Get(index);
}

void BuffersCollectionPtr::Delete()
{
	Heap::GetPtr()->BuffersCollections.Get(index)->Destroy();
	Heap::GetPtr()->BuffersCollections.Delete(index);
}
