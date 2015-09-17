#include "TexturesCollectionPtr.h"
#include "Heap.h"

TexturesCollectionPtr::TexturesCollectionPtr(unsigned int index) :  HeapPtr(index)
{
}

TexturesCollectionPtr::TexturesCollectionPtr()
{

}

TexturesCollectionPtr::TexturesCollectionPtr(bool isNull) : HeapPtr(isNull)
{
}

TexturesCollection * TexturesCollectionPtr::Get()
{
	return Heap::GetPtr()->TexturesCollections.Get(index);
}

void TexturesCollectionPtr::Delete()
{
	Heap::GetPtr()->TexturesCollections.Get(index)->Destroy();
	Heap::GetPtr()->TexturesCollections.Delete(index);
}
