#pragma once
#include "BoneAnimationData.h"
#include <stdio.h>


class Animation
{
public:
	float duration;
	float fps;

	unsigned int numOfBoneAnimDatas;
	BoneAnimationData * bonesData;
	bool * chanelsHaveData;

	void Serialize(FILE * file);
	~Animation();
};

