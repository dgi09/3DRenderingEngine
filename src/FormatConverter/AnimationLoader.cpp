#include "AnimationLoader.h"
#include <assimp/anim.h>
#include <Windows.h>
#include <iostream>


Animation * AnimationLoader::LoadAnimation(AnimatedModel * model , const aiScene * scene)
{
	aiAnimation * anim = scene->mAnimations[0];
	Animation * animation = new Animation;
	animation->duration = anim->mDuration;
	animation->fps = anim->mTicksPerSecond;
	
	//std::cout << "duration : " << animation->duration << std::endl;

	animation->numOfBoneAnimDatas = model->skeleton.bones.size();
	animation->bonesData = new BoneAnimationData[animation->numOfBoneAnimDatas];
	animation->chanelsHaveData = new bool[animation->numOfBoneAnimDatas];
	ZeroMemory(animation->chanelsHaveData,sizeof(bool) * animation->numOfBoneAnimDatas);

	using namespace std;
	//cout << "Animated channels : "<<anim->mNumChannels << endl;

	for(int i = 0;i < anim->mNumChannels;i++)
	{
		if(model->skeleton.nameMap.count(anim->mChannels[i]->mNodeName.C_Str()) > 0)
		{
			
			int index = model->skeleton.nameMap[anim->mChannels[i]->mNodeName.C_Str()];
			animation->chanelsHaveData[index] = true;
			aiNodeAnim * channel = anim->mChannels[i];

			//cout << "Channel : " << channel->mNodeName.C_Str() <<endl;

			BoneAnimationData & data = animation->bonesData[index];

			data.numOfTranslationKeys = channel->mNumPositionKeys;
			data.numOfRotationKeys = channel->mNumRotationKeys;
			data.numberOfScaleKeys = channel->mNumScalingKeys;

			/*cout << "Pos key : "<< data.numOfTranslationKeys <<endl;
			cout << "Rot key : "<< data.numOfRotationKeys <<endl;
			cout << "Scale key : "<< data.numberOfScaleKeys <<endl;
			*/
			
			data.tKeys = new TranslationKeyFrame[data.numOfTranslationKeys];
			data.rKeys = new RotationKeyFrame[data.numOfRotationKeys];
			data.sKey = new ScaleKeyFrame[data.numberOfScaleKeys];

			//cout << "POS : " <<endl;

			for(int iTrans = 0;iTrans < data.numOfTranslationKeys;iTrans++)
			{
				data.tKeys[iTrans].time = channel->mPositionKeys[iTrans].mTime;
				memcpy(&data.tKeys[iTrans].val,&channel->mPositionKeys[iTrans].mValue,12);

				//cout << data.tKeys[iTrans].val.x << " " << data.tKeys[iTrans].val.y << " " << data.tKeys[iTrans].val.z << endl; 
			}

			//cout << " ROT :" <<endl;
			for(int iRot = 0;iRot < data.numOfRotationKeys;iRot++)
			{
				data.rKeys[iRot].time = channel->mRotationKeys[iRot].mTime;
				data.rKeys[iRot].val.x = channel->mRotationKeys[iRot].mValue.x;
				data.rKeys[iRot].val.y = channel->mRotationKeys[iRot].mValue.y;
				data.rKeys[iRot].val.z = channel->mRotationKeys[iRot].mValue.z;
				data.rKeys[iRot].val.w = channel->mRotationKeys[iRot].mValue.w;

				//cout << data.rKeys[iRot].val.x << " " <<data.rKeys[iRot].val.x << " " <<data.rKeys[iRot].val.z << " "<<data.rKeys[iRot].val.w <<endl;
			}

			//cout << "Scale :"<<endl;
			for(int iScale = 0;iScale < data.numberOfScaleKeys;iScale++)
			{
				data.sKey[iScale].time = channel->mScalingKeys[iScale].mTime;
				memcpy(&data.sKey[iScale].val,&channel->mScalingKeys[iScale].mValue,12);

				//cout << data.sKey[iScale].val.x << " " << data.sKey[iScale].val.y << " " << data.sKey[iScale].val.z << endl; 
			}

			//cout << "--------------------" <<endl;
		}
	}

	for(int i = 0;i < animation->numOfBoneAnimDatas;i++)
	{
		if(animation->chanelsHaveData[i] == false)
		{
			BoneAnimationData & data = animation->bonesData[i];
			data.numberOfScaleKeys = 0;
			data.numOfTranslationKeys = 0;
			data.numOfRotationKeys = 0;
		}
	}



	return animation;
}
