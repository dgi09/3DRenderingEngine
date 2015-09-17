#pragma  once

#include "Common.h"
#include "EffectMask.h"
#include <vector>
#include <unordered_map>

class EXPORT EntityEffect;

class EXPORT EffectPool 
{
	std::unordered_map<EFFECTMASK,EntityEffect*> effects;
	std::vector<EntityEffect*> memory;
public:
	EffectPool();
	~EffectPool();

	EntityEffect * Get(EFFECTMASK mask);
	void Set(EFFECTMASK mask, EntityEffect * effect);
	bool Exist(EFFECTMASK mask);
	void DeleteAll();

};