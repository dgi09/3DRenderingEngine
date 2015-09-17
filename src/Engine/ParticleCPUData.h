#pragma once 

#include "Common.h"
#include "Vector3.h"

struct EXPORT ParticleCPUData
{
	Vector3 velocity;
	float currentLifeTime;
	float size;
	float lifeTime;
};