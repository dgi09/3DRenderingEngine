#include "ComputeShaderPtr.h"
#include "Heap.h"

ComputeShaderPtr::ComputeShaderPtr(unsigned int index) : HeapPtr(index)
{
}

ComputeShaderPtr::ComputeShaderPtr()
{

}

ComputeShaderPtr::ComputeShaderPtr(bool isNull) : HeapPtr(index)
{

}

ComputeShader * ComputeShaderPtr::Get()
{
	return Heap::GetPtr()->ComputeShaders.Get(index);
}

void ComputeShaderPtr::Delete()
{
	Heap::GetPtr()->ComputeShaders.Get(index)->Destroy();
	Heap::GetPtr()->ComputeShaders.Delete(index);
}