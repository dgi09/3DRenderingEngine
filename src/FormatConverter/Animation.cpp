#include "Animation.h"



void Animation::Serialize(FILE * file)
{
	int number = 2;
	fwrite(&number,4,1,file);
	fwrite(&duration,4,1,file);
	fwrite(&fps,4,1,file);
	fwrite(&numOfBoneAnimDatas,4,1,file);
	fwrite(chanelsHaveData,sizeof(bool),numOfBoneAnimDatas,file);

	for(int i = 0;i<numOfBoneAnimDatas;i++)
	{
		BoneAnimationData & data = bonesData[i];
		fwrite(&data.numOfTranslationKeys,4,1,file);
		fwrite(data.tKeys,sizeof(TranslationKeyFrame),data.numOfTranslationKeys,file);
		fwrite(&data.numOfRotationKeys,4,1,file);
		fwrite(data.rKeys,sizeof(RotationKeyFrame),data.numOfRotationKeys,file);
		fwrite(&data.numberOfScaleKeys,4,1,file);
		fwrite(data.sKey,sizeof(ScaleKeyFrame),data.numberOfScaleKeys,file);

	}
}

Animation::~Animation()
{
	delete bonesData;
}
