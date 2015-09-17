#pragma once 
#include "Common.h"
#include "ObjectPoolPattern.h"
#include "Heap.h"
#include "TexturePtr.h"

template <class Key>
class EXPORT ObjectPoolPattern_Texture : public ObjectPoolPattern<Key,TexturePtr>
{
protected:
	void DeleteVal(TexturePtr value);
};

template <class Key>
void ObjectPoolPattern_Texture<Key>::DeleteVal(TexturePtr value)
{
	value.Delete();
}
