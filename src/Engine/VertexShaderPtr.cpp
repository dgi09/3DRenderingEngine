#include "VertexShaderPtr.h"
#include "Heap.h"

VertexShaderPtr::VertexShaderPtr(unsigned int index) : HeapPtr(index)
{
}

VertexShaderPtr::VertexShaderPtr()
{

}

VertexShaderPtr::VertexShaderPtr(bool isNull) : HeapPtr(index)
{

}

VertexShader * VertexShaderPtr::Get()
{
	return Heap::GetPtr()->VertexShaders.Get(index);
}

void VertexShaderPtr::Delete()
{
	Heap::GetPtr()->VertexShaders.Get(index)->Destroy();
	Heap::GetPtr()->VertexShaders.Delete(index);
}
