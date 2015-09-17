#pragma once
#include "Common.h"
#include "HeapPtr.h"
#include "SamplersCollection.h"


class EXPORT SamplersCollectionPtr : public HeapPtr<SamplersCollection>
{
public:
	SamplersCollectionPtr();
	SamplersCollectionPtr(unsigned int index);
	SamplersCollectionPtr(bool isNull);
	SamplersCollection * Get();
	void Delete();
};

