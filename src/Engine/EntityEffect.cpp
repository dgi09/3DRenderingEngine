#include "EntityEffect.h"

#include "IInputLayout.h"
#include "IEffectBindingSection.h"
#include "EffectBinder.h"


EFFECTMASK EntityEffect::GetMask()
{
	return mask;
}

void EntityEffect::SetMask(EFFECTMASK mask)
{
	this->mask = mask;
}


void EntityEffect::AddBindingSection(IEffectBindingSection * section)
{
	bindingSections.push_back(section);
}

EffectBinder * EntityEffect::GetBinder()
{
	return &binder;
}

void EntityEffect::SetUpBinder()
{
	binder.SetSections(&bindingSections);
	binder.Init();
}

void EntityEffect::Init(DeviceDependableFactory * factory)
{
	Effect::Init(factory);
	mask = 0;

	binder.SetFactory(factory);
}

void EntityEffect::Destroy()
{

	Effect::Destroy();

	binder.Destroy();

	bindingSections.clear();
}
