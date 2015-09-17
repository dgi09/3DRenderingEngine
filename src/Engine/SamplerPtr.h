#pragma once
#include "Common.h"
#include "HeapPtr.h"
#include "Sampler.h"

class EXPORT SamplerPtr : public HeapPtr<Sampler>
{
public:
	SamplerPtr();
	SamplerPtr(unsigned int index);
	SamplerPtr(bool isNull);
	Sampler * Get();
	void Delete();
};

