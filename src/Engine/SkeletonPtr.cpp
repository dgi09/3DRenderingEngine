#include "SkeletonPtr.h"
#include "Heap.h"

SkeletonPtr::SkeletonPtr(unsigned int index) : HeapPtr(index)
{
}

SkeletonPtr::SkeletonPtr()
{

}

SkeletonPtr::SkeletonPtr(bool isNull) : HeapPtr(isNull)
{

}

Skeleton * SkeletonPtr::Get()
{
	return Heap::GetPtr()->Skeletons.Get(index);
}

void SkeletonPtr::Delete()
{
	Heap::GetPtr()->Skeletons.Get(index)->Destroy();

	Heap::GetPtr()->Skeletons.Delete(index);
}
