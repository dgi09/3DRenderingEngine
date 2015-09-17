#include "EffectBinder.h"
#include "DeviceDependableFactory.h"
#include "BuffersCollection.h"
#include "SamplersCollection.h"
#include "TexturesCollection.h"
#include "IEffectBindingSection.h"
#include "ShaderBindingInfo.h"



IEffectBindingSection * EffectBinder::GetBindingSectionByFunctionality(EffectFunctionality func)
{
	for(int i = 0;i<sections->size();i++)
	{
		if(sections->at(i)->GetEffectFunctionality() == func)
			return sections->at(i);
	}

	return nullptr;
}

void EffectBinder::BindAllSections()
{
	unsigned int vsCurrentTextureIndex = 0;
	unsigned int vsCurrentSamplerIndex = 0;
	unsigned int vsCurrentBufferIndex = 0;

	unsigned int psCurrentTextureIndex = 0;
	unsigned int psCurrentSamplerIndex = 0;
	unsigned int psCurrentBufferIndex = 0;

	vsBuffers.Clear();
	vsSamplers.Clear();
	vsTextures.Clear();

	psBuffers.Clear();
	psSamplers.Clear();
	psTextures.Clear();

	for(int i = 0;i < sections->size();i++)
	{
		IEffectBindingSection * section = sections->at(i);
		

		if(section->InVs())
		{
			ShaderBindingInfo * vsInfo = section->GetVSShaderBindingInfo();

			for(int iTexture = 0;iTexture < vsInfo->texturesCount;iTexture++)
			{
				if(!vsInfo->textures[iTexture].IsNull())
					vsTextures.Set(vsCurrentTextureIndex,vsInfo->textures[iTexture].Get());
				
				vsCurrentTextureIndex++;
			}

			for(int iSampler = 0;iSampler < vsInfo->samplersCount;iSampler++)
			{
				if(!vsInfo->samplers[iSampler].IsNull())
					vsSamplers.Set(vsCurrentSamplerIndex,vsInfo->samplers[iSampler].Get());
				
				vsCurrentSamplerIndex++;
			}

			for(int iBuffer = 0;iBuffer < vsInfo->buffersCount;iBuffer++)
			{
				if(!vsInfo->buffers[iBuffer].IsNull())
					vsBuffers.Set(vsCurrentBufferIndex,vsInfo->buffers[iBuffer].Get());
				
				vsCurrentBufferIndex++;
			}
		}

		
		if(section->InPS())
		{
			ShaderBindingInfo * psInfo = section->GetPSShaderBindingInfo();
			for(int iTexture = 0;iTexture < psInfo->texturesCount;iTexture++)
			{
				if(!psInfo->textures[iTexture].IsNull())
					psTextures.Set(psCurrentTextureIndex,psInfo->textures[iTexture].Get());
				
				psCurrentTextureIndex++;
			}

			for(int iSampler = 0;iSampler < psInfo->samplersCount;iSampler++)
			{
				if(!psInfo->samplers[iSampler].IsNull())
					psSamplers.Set(psCurrentSamplerIndex,psInfo->samplers[iSampler].Get());
				
				psCurrentSamplerIndex++;
			}

			for(int iBuffer = 0;iBuffer < psInfo->buffersCount;iBuffer++)
			{
				if(!psInfo->buffers[iBuffer].IsNull())
					psBuffers.Set(psCurrentBufferIndex,psInfo->buffers[iBuffer].Get());
				
				psCurrentBufferIndex++;
			}
		}

	}

	vsBuffers.Bind(VERTEX);
	vsSamplers.Bind(VERTEX);
	vsTextures.Bind(VERTEX);

	psBuffers.Bind(PIXEL);
	psSamplers.Bind(PIXEL);
	psTextures.Bind(PIXEL);


}

void EffectBinder::SetSections(std::vector<IEffectBindingSection*> * sections)
{
	this->sections = sections;
}

void EffectBinder::Init()
{
	unsigned int vsTexturesCount = 0;
	unsigned int vsSamplersCount = 0;
	unsigned int vsBuffersCount = 0;

	unsigned int psTexturesCount = 0;
	unsigned int psSamplersCount = 0;
	unsigned int psBuffersCount = 0;

	psBuffers = factory->CreateBuffersCollection();
	psSamplers = factory->CreateSamplersCollection();
	psTextures = factory->CreateTexturesCollection();

	vsBuffers = factory->CreateBuffersCollection();
	vsSamplers = factory->CreateSamplersCollection();
	vsTextures = factory->CreateTexturesCollection();


	for(int i = 0;i < sections->size();i++)
	{
		IEffectBindingSection * section = sections->at(i);
		if(section->GetVSShaderBindingInfo() != nullptr)
		{
			vsTexturesCount += section->GetVSShaderBindingInfo()->texturesCount;
			vsSamplersCount += section->GetVSShaderBindingInfo()->samplersCount;
			vsBuffersCount  += section->GetVSShaderBindingInfo()->buffersCount;
		}

		if(section->GetPSShaderBindingInfo() != nullptr)
		{
			psTexturesCount += section->GetPSShaderBindingInfo()->texturesCount;
			psSamplersCount += section->GetPSShaderBindingInfo()->samplersCount;
			psBuffersCount  += section->GetPSShaderBindingInfo()->buffersCount;
		}
	}

	vsTextures.SetSize(vsTexturesCount);
	vsSamplers.SetSize(vsSamplersCount);
	vsBuffers.SetSize(vsBuffersCount);

	psTextures.SetSize(psTexturesCount);
	psSamplers.SetSize(psSamplersCount);
	psBuffers.SetSize(psBuffersCount);
}

void EffectBinder::SetFactory(DeviceDependableFactory * factory)
{
	this->factory = factory;
}

void EffectBinder::Destroy()
{

}
