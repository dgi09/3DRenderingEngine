#pragma  once 

#include "Common.h"
#include "RotationKey.h"
#include "TranslationKey.h"
#include "ScalingKey.h"
#include <DirectXMath.h>

class EXPORT BoneAnimationData
{
public:
	BoneAnimationData();
	~BoneAnimationData();

	unsigned int numberOfTranslationKeys;
	unsigned int numberOfRotationKeys;
	unsigned int numberOfScalingKeys;

	TranslationKey * translationKeys;
	RotationKey * rotationKeys;
	ScalingKey * scalingKeys;

	DirectX::XMFLOAT4X4 GenerateMatrix(float time);	
	void Destroy();

private:
	DirectX::XMFLOAT3 GetTranslationValue(float time);
	DirectX::XMFLOAT4 GetRotationValue(float time);
	DirectX::XMFLOAT3 GetScalingValue(float time);
};