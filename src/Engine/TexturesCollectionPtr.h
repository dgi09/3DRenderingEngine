#pragma once
#include "Common.h"
#include "TexturesCollection.h"
#include "HeapPtr.h"

class EXPORT TexturesCollectionPtr : public HeapPtr<TexturesCollection>
{
public:
	TexturesCollectionPtr();
	TexturesCollectionPtr(unsigned int index);
	TexturesCollectionPtr(bool isNull);
	TexturesCollection * Get();
	void Delete();
};

