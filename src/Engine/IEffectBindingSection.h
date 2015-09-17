#pragma once 
#include "Common.h"
#include "EffectFunctionality.h"
#include "IDestroyable.h"
#include "ShaderBindingInfo.h"

class EXPORT DeviceDependableFactory;


class EXPORT IEffectBindingSection : public IDestroyable
{
protected:
	ShaderBindingInfo vsShader;
	ShaderBindingInfo psShader;

	bool inVS;
	bool inPS;

public:

	ShaderBindingInfo * GetVSShaderBindingInfo();
	ShaderBindingInfo * GetPSShaderBindingInfo();

	bool InVs();
	bool InPS();

	virtual void Init(DeviceDependableFactory * factory) = 0;
	virtual void Destroy() = 0;
	virtual EffectFunctionality GetEffectFunctionality() = 0;
};
