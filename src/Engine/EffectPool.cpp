#include "EffectPool.h"
#include "EntityEffect.h"

EffectPool::EffectPool()
{

}

EffectPool::~EffectPool()
{
	DeleteAll();
}

EntityEffect * EffectPool::Get(EFFECTMASK mask)
{
	if(Exist(mask))
		return effects[mask];
	else return nullptr;
}

void EffectPool::Set(EFFECTMASK mask, EntityEffect * effect)
{
	memory.push_back(effect);
	effects[mask] = effect;
}

bool EffectPool::Exist(EFFECTMASK mask)
{
	if(effects.count(mask))
		return true;
	else return false;
}

void EffectPool::DeleteAll()
{
	for(std::vector<EntityEffect*>::iterator it = memory.begin();it != memory.end();++it)
	{
		if((*it) != nullptr)
			delete (*it);
	}

	memory.clear();
}
