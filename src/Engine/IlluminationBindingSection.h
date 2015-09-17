#pragma  once 
#include "Common.h"
#include "IEffectBindingSection.h"

#include "Vector4.h"
#include "ConstantBufferPtr.h"

class EXPORT IlluminationBindingSection : public IEffectBindingSection
{
public:

	void Destroy();
	virtual void Init(DeviceDependableFactory * factory);

	virtual EffectFunctionality GetEffectFunctionality();

	void SetIlluminationInfo(ConstantBufferPtr infoBuffer);
	void SetDirLights(ConstantBufferPtr dirLightsBuffer);
	void SetGlobalAmbient(ConstantBufferPtr globalAmbientBuffer);

	void SetPointLight(ConstantBufferPtr pointLightBuffer);
};