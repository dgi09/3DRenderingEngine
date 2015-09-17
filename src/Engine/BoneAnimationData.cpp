#include "BoneAnimationData.h"

BoneAnimationData::BoneAnimationData()
{
	translationKeys = nullptr;
	rotationKeys = nullptr;
	scalingKeys = nullptr;
}

BoneAnimationData::~BoneAnimationData()
{
	
}

DirectX::XMFLOAT4X4 BoneAnimationData::GenerateMatrix(float time)
{
	DirectX::XMMATRIX m;
	DirectX::XMMATRIX translationMatrix = DirectX::XMMatrixTranslationFromVector(XMLoadFloat3(&GetTranslationValue(time)));
	DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationQuaternion(XMLoadFloat4(&GetRotationValue(time)));
	DirectX::XMMATRIX scaleMatrix = DirectX::XMMatrixScalingFromVector(XMLoadFloat3(&GetScalingValue(time)));

	m = scaleMatrix * rotationMatrix * translationMatrix;
	DirectX::XMFLOAT4X4 res;
	DirectX::XMStoreFloat4x4(&res,m);
	return res;
}

DirectX::XMFLOAT3 BoneAnimationData::GetTranslationValue(float time)
{
	if(time <= translationKeys[0].time)
		return translationKeys[0].val;

	if(time >= translationKeys[numberOfTranslationKeys-1].time)
		return translationKeys[numberOfTranslationKeys-1].val;

	
	int tIndex;
	for(int i = 0;i < numberOfTranslationKeys;i++)
	{
		if(translationKeys[i].time >= time)
		{
			tIndex = i;
			break;
		}
	}

	float coef = (time - translationKeys[tIndex-1].time) / (translationKeys[tIndex].time - translationKeys[tIndex-1].time);

	DirectX::XMVECTOR v1 = XMLoadFloat3(&translationKeys[tIndex-1].val);
	DirectX::XMVECTOR v2 = XMLoadFloat3(&translationKeys[tIndex].val);
	DirectX::XMVECTOR res = DirectX::XMVectorLerp(v1,v2,coef);
	DirectX::XMFLOAT3 r;
	DirectX::XMStoreFloat3(&r,res);
	return r;
}

DirectX::XMFLOAT4 BoneAnimationData::GetRotationValue(float time)
{
	if(time <= rotationKeys[0].time)
		return rotationKeys[0].val;

	if(time >= rotationKeys[numberOfRotationKeys-1].time)
		return rotationKeys[numberOfRotationKeys-1].val;

	int rIndex;
	for(int i = 0;i < numberOfRotationKeys;i++)
	{
		if(rotationKeys[i].time >= time)
		{
			rIndex = i;
			break;
		}
	}

	float coef = (time - rotationKeys[rIndex-1].time) / (rotationKeys[rIndex].time - rotationKeys[rIndex-1].time);
	DirectX::XMVECTOR v1 = XMLoadFloat4(&rotationKeys[rIndex-1].val);
	DirectX::XMVECTOR v2 = XMLoadFloat4(&rotationKeys[rIndex].val);
	DirectX::XMVECTOR res = DirectX::XMQuaternionNormalize(DirectX::XMQuaternionSlerp(v1,v2,coef));
	DirectX::XMFLOAT4 r;
	DirectX::XMStoreFloat4(&r,res);

	return r;
}

DirectX::XMFLOAT3 BoneAnimationData::GetScalingValue(float time)
{
	if(time <= scalingKeys[0].time)
		return scalingKeys[0].val;

	if(time >= scalingKeys[numberOfScalingKeys-1].time)
		return scalingKeys[numberOfScalingKeys-1].val;

	int sIndex;
	for(int i = 0;i < numberOfScalingKeys;i++)
	{
		if(scalingKeys[i].time >= time)
		{
			sIndex = i;
			break;
		}
	}

	float coef = (time - scalingKeys[sIndex-1].time) / (scalingKeys[sIndex].time - scalingKeys[sIndex-1].time);

	DirectX::XMVECTOR v1 = XMLoadFloat3(&scalingKeys[sIndex-1].val);
	DirectX::XMVECTOR v2 = XMLoadFloat3(&scalingKeys[sIndex].val);
	DirectX::XMVECTOR res = DirectX::XMVectorLerp(v1,v2,coef);
	DirectX::XMFLOAT3 r;
	DirectX::XMStoreFloat3(&r,res);

	return r;
}

void BoneAnimationData::Destroy()
{
	if(translationKeys != nullptr)
		delete[] translationKeys;

	if(rotationKeys != nullptr)
		delete[] rotationKeys;

	if(scalingKeys != nullptr)
		delete[] scalingKeys;
}
