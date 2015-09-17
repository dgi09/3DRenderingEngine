#pragma once 
#include "Common.h"
#include "Vector3.h"

struct EXPORT ParticleGPUData 
{
	Vector3 worldPos;
	float size;
	float opacityFactor;
	float padding[3];
};