#include "IEffectBindingSection.h"
#include "ShaderBindingInfo.h"
#include "DeviceDependableFactory.h"

ShaderBindingInfo * IEffectBindingSection::GetVSShaderBindingInfo()
{
	return &vsShader;
}

ShaderBindingInfo * IEffectBindingSection::GetPSShaderBindingInfo()
{
	return &psShader;
}

bool IEffectBindingSection::InVs()
{
	return inVS;
}

bool IEffectBindingSection::InPS()
{
	return inPS;
}


