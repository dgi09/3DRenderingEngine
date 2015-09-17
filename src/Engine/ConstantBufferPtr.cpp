#include "ConstantBufferPtr.h"
#include "Heap.h"

ConstantBufferPtr::ConstantBufferPtr(unsigned int index) : HeapPtr(index)
{
	
}

ConstantBufferPtr::ConstantBufferPtr()
{

}

ConstantBufferPtr::ConstantBufferPtr(bool isNull) : HeapPtr(isNull)
{

}

ConstantBuffer * ConstantBufferPtr::Get()
{
	return Heap::GetPtr()->ConstantBuffers.Get(index);
}

void ConstantBufferPtr::Delete()
{
	Heap::GetPtr()->ConstantBuffers.Get(index)->Destroy();
	Heap::GetPtr()->ConstantBuffers.Delete(index);
}
