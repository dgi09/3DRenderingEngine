#pragma  once
#include "Common.h"
#include "SamplerPtr.h"
#include "TexturePtr.h"
#include "ConstantBufferPtr.h"

#define MAXSAMPLERS 2
#define MAXTEXTURES 4
#define MAXCONSTANTBUFFERS 5

class EXPORT ShaderBindingInfo 
{
public:
	ShaderBindingInfo();

	unsigned int samplersCount;
	unsigned int texturesCount;
	unsigned int buffersCount;

	SamplerPtr samplers[MAXSAMPLERS];
	TexturePtr textures[MAXTEXTURES];
	ConstantBufferPtr buffers[MAXCONSTANTBUFFERS];

};