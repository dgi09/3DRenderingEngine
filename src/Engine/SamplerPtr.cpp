#include "SamplerPtr.h"
#include "Heap.h"

SamplerPtr::SamplerPtr(unsigned int index) : HeapPtr(index)
{
}

SamplerPtr::SamplerPtr()
{

}

SamplerPtr::SamplerPtr(bool isNull) : HeapPtr(isNull)
{

}

Sampler * SamplerPtr::Get()
{
	return Heap::GetPtr()->Samplers.Get(index);
}

void SamplerPtr::Delete()
{
	Heap::GetPtr()->Samplers.Get(index)->Destroy();

	Heap::GetPtr()->Samplers.Delete(index);
}
