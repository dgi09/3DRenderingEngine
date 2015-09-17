#pragma once 
#include "Common.h"
#include "DeviceDependable.h"
#include "ShaderType.h"


class EXPORT Sampler;

#define MAX_SAMPLERS_IN_COLLECTION 10
class EXPORT SamplersCollection : public DeviceDependable
{
	ID3D11SamplerState * samplers[MAX_SAMPLERS_IN_COLLECTION];
	unsigned int size;
public:
	
	SamplersCollection();
	void Bind(ShaderType shader);
	void SetSize(unsigned int size);
	void Set(unsigned int index,Sampler * sampler);
	void Clear();
};