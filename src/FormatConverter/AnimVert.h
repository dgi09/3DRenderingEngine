#pragma once 
#include "Vector.h"

struct AnimVert
{
	Vector3 pos;
	Vector3 normal;
	Vector3 tangent;
	Vector2 uv;
	float wights[4];
	unsigned int boneIndexes[4];
};
