#include "SamplersCollection.h"
#include "Sampler.h"


void SamplersCollection::Bind(ShaderType shader)
{
	if(size > 0)
	{
		if(shader == VERTEX)
			GetContext()->VSSetSamplers(0,size,samplers);
		else 
			GetContext()->VSSetSamplers(0,size,samplers);
	}
	
}

void SamplersCollection::SetSize(unsigned int size)
{
	if(size > 0 && size <= MAX_SAMPLERS_IN_COLLECTION)
	{
		this->size = size;
	}
}

void SamplersCollection::Set(unsigned int index,Sampler * sampler)
{
	if(index >= 0 && index < size)
		samplers[index] = sampler->GetSamplerPointer();
}



SamplersCollection::SamplersCollection()
{
	size = 0;
}

void SamplersCollection::Clear()
{
	for(int i = 0;i < MAX_SAMPLERS_IN_COLLECTION;i++)
	{
		samplers[i] = nullptr;
	}
}
