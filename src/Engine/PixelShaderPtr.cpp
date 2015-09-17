#include "PixelShaderPtr.h"
#include "Heap.h"

PixelShaderPtr::PixelShaderPtr(unsigned int index) : HeapPtr(index)
{

}

PixelShaderPtr::PixelShaderPtr()
{

}

PixelShaderPtr::PixelShaderPtr(bool isNull) : HeapPtr(isNull)
{

}

PixelShader * PixelShaderPtr::Get()
{
	return Heap::GetPtr()->PixelShaders.Get(index);
}

void PixelShaderPtr::Delete()
{
	Heap::GetPtr()->PixelShaders.Get(index);
	Heap::GetPtr()->PixelShaders.Delete(index);
}
