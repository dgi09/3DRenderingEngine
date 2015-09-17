#pragma once 
#include "Common.h"
#include "Vector3.h"

struct EXPORT ScreenSpaceVert
{
	Vector3 pos;
	float u,v;
};

struct EXPORT StaticVert
{
	Vector3 pos;
	Vector3 normal;
	Vector3 tagent;
	float u,v;
};

struct EXPORT AnimatedVert
{
	Vector3 pos;
	Vector3 normal;
	Vector3 tangent;
	float u,v;

	float wights[4];
	unsigned int boneIndexes[4];
};