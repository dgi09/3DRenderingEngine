#include "SkinningBindingSection.h"
#include "ShaderBindingInfo.h"
#include "DeviceDependableFactory.h"
#include "Constants.h"

#include <DirectXMath.h>


void SkinningBindingSection::Init(DeviceDependableFactory * factory)
{
	inVS = true;
	inPS = false;
	vsShader.buffersCount = 1;

	vsShader.buffers[0] = ConstantBufferPtr(true);
}

EffectFunctionality SkinningBindingSection::GetEffectFunctionality()
{
	return SKINNING;
}


void SkinningBindingSection::BindPallete(ConstantBufferPtr pallete)
{
	vsShader.buffers[0] = pallete;
}

void SkinningBindingSection::Destroy()
{
}
