#pragma once 
#include "Common.h"
#include "Bone.h"
#include <DirectXMath.h>
#include "IDestroyable.h"


class EXPORT SkeletonPtr;
class EXPORT Skeleton : public IDestroyable
{
public:
	void Init();
	void Destroy();
	unsigned int numberOfBones;
	Bone * bones;
	DirectX::XMFLOAT4X4 globalInverse;
	SkeletonPtr Copy();
};