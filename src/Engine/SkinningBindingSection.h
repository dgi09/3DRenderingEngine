#pragma once 
#include "Common.h"
#include "IEffectBindingSection.h"
#include "MatrixPallete.h"
#include "ConstantBufferPtr.h"


class EXPORT SkinningBindingSection : public IEffectBindingSection
{
public:
	virtual void Init(DeviceDependableFactory * factory);

	virtual EffectFunctionality GetEffectFunctionality();

	void BindPallete(ConstantBufferPtr pallete);

	void Destroy();

};