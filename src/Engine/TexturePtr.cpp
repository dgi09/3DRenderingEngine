#include "TexturePtr.h"
#include "Heap.h"

TexturePtr::TexturePtr(unsigned int index) : HeapPtr(index)
{
}

TexturePtr::TexturePtr()
{

}

TexturePtr::TexturePtr(bool isNull) : HeapPtr(isNull)
{

}

Texture * TexturePtr::Get()
{
	return Heap::GetPtr()->Textures.Get(index);
}

void TexturePtr::Delete()
{
	Heap::GetPtr()->Textures.Get(index)->Destroy();
	Heap::GetPtr()->Textures.Delete(index);
}
