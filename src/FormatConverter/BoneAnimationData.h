#pragma once 
#include "Vector.h"
struct TranslationKeyFrame
{
	float time;
	Vector3 val;
};

struct RotationKeyFrame
{
	float time;
	Vector4 val;
};

struct ScaleKeyFrame
{
	float time;
	Vector3 val;
};
struct BoneAnimationData
{
	unsigned int numOfTranslationKeys;
	TranslationKeyFrame * tKeys;
	unsigned int numOfRotationKeys;
	RotationKeyFrame * rKeys;
	unsigned int numberOfScaleKeys;
	ScaleKeyFrame * sKey;
};