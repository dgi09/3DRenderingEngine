#pragma once 
#include "Common.h"
#include "IEffectBindingSection.h"
#include "TexturePtr.h"
#include "Material.h"

class EXPORT MaterialBindingSection : public IEffectBindingSection
{
public:

	virtual void Init(DeviceDependableFactory * factory);

	virtual EffectFunctionality GetEffectFunctionality();

	void Destroy();

	void SetDiffuseMap(TexturePtr texture);
	void SetBumpMap(TexturePtr bumpMap);

	void SetMaterialData(MaterialData * data);
};