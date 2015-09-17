#pragma once
#include "Common.h"
#include "HeapPtr.h"
#include "BuffersCollection.h"


class EXPORT BuffersCollectionPtr : public HeapPtr<BuffersCollection>
{
public:
	BuffersCollectionPtr();
	BuffersCollectionPtr(unsigned int index);
	BuffersCollectionPtr(bool isNull);
	BuffersCollection * Get();
	void Delete();
};

