#pragma once 
#include "Common.h"
#include "EntityBase.h"

class EXPORT StaticEntity : public EntityBase
{
public:
	virtual void Draw(EffectBinder * binder);
};