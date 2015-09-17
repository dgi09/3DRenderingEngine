#include "Animation.h"
#include "Heap.h"
#include "AnimationPtr.h"


AnimationPtr Animation::Copy()
{
	AnimationPtr ptr(Heap::GetPtr()->Animations.New());

	Animation * anim = ptr.Get();
	anim->numberOfBoneChannels = numberOfBoneChannels;
	anim->duration = duration;
	anim->fps = fps;
	
	memcpy(anim->channelHaveData,channelHaveData,sizeof(bool) * numberOfBoneChannels);

	for(int i = 0;i<anim->numberOfBoneChannels;i++)
	{
		BoneAnimationData  & data = anim->channels[i];
		data.numberOfRotationKeys = channels[i].numberOfRotationKeys;
		data.numberOfTranslationKeys = channels[i].numberOfTranslationKeys;
		data.numberOfScalingKeys = channels[i].numberOfScalingKeys;

		data.rotationKeys = new RotationKey[data.numberOfRotationKeys];
		data.translationKeys = new TranslationKey[data.numberOfTranslationKeys];
		data.scalingKeys = new ScalingKey[data.numberOfScalingKeys];

		memcpy(data.rotationKeys,channels[i].rotationKeys,sizeof(RotationKey) * data.numberOfRotationKeys);
		memcpy(data.translationKeys,channels[i].translationKeys,sizeof(TranslationKey) * data.numberOfTranslationKeys);
		memcpy(data.scalingKeys,channels[i].scalingKeys,sizeof(ScalingKey) * data.numberOfScalingKeys);
	}

	return ptr;
}

void Animation::Init()
{
	
}

void Animation::Destroy()
{
	for(int i = 0;i < numberOfBoneChannels;i++)
		channels[i].Destroy();
}
