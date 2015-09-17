#include "AnimationController.h"
#include "Animation.h"

void AnimationController::AddAnimationState(unsigned int startFrame,unsigned int endFrame, PlayType playType,std::string name)
{
	Animation * anim = ptr.Get();

	AnimationState state;
	if(startFrame < 0)
		startFrame = 0;
	if(endFrame > anim->duration)
		endFrame = anim->duration;

	state.startTime = (float)startFrame;
	state.endTime = (float)endFrame;
	state.currentTime = state.startTime;
	state.playType = playType;
	states[name] = state;
}

void AnimationController::SetCurrentAnimationState(std::string name)
{
	currentState = &states[name];
	playFull = false;
}

void AnimationController::AddTime(float time)
{
	if(!playFull)
	{
		currentState->currentTime += time;
		if(currentState->playType == LOOP)
		{
			if(currentState->endTime < currentState->currentTime)
				currentState->currentTime = currentState->startTime;
		}
		else 
		{
			if(currentState->endTime < currentState->currentTime)
				currentState->currentTime = currentState->endTime;
		}
	}
	else 
	{
		currentTime += time;
		if(currentTime > ptr.Get()->duration)
			currentTime = 0.0f;
	}

}

void AnimationController::SetPlayType(PlayType type)
{
	currentState->playType = type;
}

void AnimationController::UpdateMatrixPallete(unsigned int boneIndex,DirectX::XMFLOAT4X4 & parent)
{
	DirectX::XMMATRIX animMatrix;
	DirectX::XMFLOAT4X4 animMatData;


	Skeleton * skeleton = skeletonPtr.Get();

	Animation * currentAnimation = ptr.Get();

	float time;
	if(playFull)
		time = currentTime;
	else time = currentState->currentTime;


	if(currentAnimation->channelHaveData[boneIndex])
		animMatData = currentAnimation->channels[boneIndex].GenerateMatrix(time);
	else animMatData = skeleton->bones[boneIndex].transformation;




	animMatrix = DirectX::XMLoadFloat4x4(&animMatData);

	DirectX::XMMATRIX pMatrix = XMLoadFloat4x4(&parent);
	DirectX::XMMATRIX gInverse = XMLoadFloat4x4(&skeleton->globalInverse);

	DirectX::XMMATRIX globalTranform = animMatrix * pMatrix;


	DirectX::XMMATRIX offSet = XMLoadFloat4x4(&skeleton->bones[boneIndex].offsetMatrix);
	DirectX::XMMATRIX final =  offSet * globalTranform *  gInverse;

	//final *= skeleton->globalInverse;
	DirectX::XMFLOAT4X4 fin;
	DirectX::XMStoreFloat4x4(&fin,XMMatrixTranspose(final));
	pallete.matrixes[boneIndex] = fin;

	DirectX::XMFLOAT4X4 gt;
	DirectX::XMStoreFloat4x4(&gt,globalTranform);
	for(int i = 0;i<skeleton->bones[boneIndex].childIndexes.size();i++)
	{
		UpdateMatrixPallete(skeleton->bones[boneIndex].childIndexes[i],gt);
	}
}

void AnimationController::Init(SkeletonPtr skeleton,AnimationHandler handler)
{
	this->skeletonPtr = skeleton;
	this->handler = handler;
	ptr = handler.Get();
	currentState = nullptr;
	currentTime = 0.0f;
}

void AnimationController::Destroy()
{
	handler.Destroy();
}

MatrixPallete & AnimationController::GetData()
{
	DirectX::XMFLOAT4X4 identity;
	DirectX::XMMATRIX iden = DirectX::XMMatrixIdentity();
	DirectX::XMStoreFloat4x4(&identity,iden);

	UpdateMatrixPallete(0,identity);
	return pallete;
}
