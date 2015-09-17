#pragma once 
#include "Common.h"
#include "BoneAnimationData.h"
#include "IDestroyable.h"
#include "Constants.h"

class EXPORT AnimationPtr;

class EXPORT Animation : public IDestroyable
{
public:

	void Init();
	void Destroy();

	
	AnimationPtr Copy(); 

	unsigned int fps;
	float duration;
	unsigned int numberOfBoneChannels;

	BoneAnimationData  channels[MAX_BONES];
	bool  channelHaveData[MAX_BONES];
};