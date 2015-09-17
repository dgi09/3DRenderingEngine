#pragma once 
#include "Effect.h"
#include "Common.h"
#include "EffectMask.h"
#include <vector>
#include "VertexShaderPtr.h"
#include "PixelShaderPtr.h"
#include "EffectBinder.h"
#include "IDestroyable.h"


class EXPORT IEffectBindingSection;
class EXPORT DeviceDependableFactory;
class EXPORT IInputLayout;

class EXPORT EntityEffect : public Effect
{
	EFFECTMASK mask;

	EffectBinder  binder;

	std::vector<IEffectBindingSection*> bindingSections;
public:
	void Init(DeviceDependableFactory * factory);
	void Destroy();

	EFFECTMASK GetMask();
	void SetMask(EFFECTMASK mask);


	void AddBindingSection(IEffectBindingSection * section);
	void SetUpBinder();

	EffectBinder * GetBinder();
};