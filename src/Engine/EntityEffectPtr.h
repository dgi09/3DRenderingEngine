#pragma once 
#include "Common.h"
#include "HeapPtr.h"
#include "EntityEffect.h"

class EXPORT EntityEffectPtr : public HeapPtr<EntityEffect>
{
public:
	EntityEffectPtr();
	EntityEffectPtr(unsigned int index);
	EntityEffectPtr(bool isNull);

	EntityEffect * Get();
	void Delete();
};