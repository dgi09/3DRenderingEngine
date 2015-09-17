#pragma once 
#include "Common.h"
#include "SkeletonPtr.h"
#include "AnimationPtr.h"
#include "AnimationHandler.h"
#include <vector>
#include <string>
#include <unordered_map>
#include "MatrixPallete.h"
#include <DirectXMath.h>

class EXPORT AnimatedEntity;

enum EXPORT PlayType
{
	LOOP,
	ONCE
};

struct EXPORT AnimationState
{
	float startTime;
	float endTime;
	PlayType playType;
	float currentTime;
};

class EXPORT AnimationController
{
	AnimationHandler handler;
	SkeletonPtr skeletonPtr;
	MatrixPallete pallete;
	AnimationPtr ptr;

	AnimationState * currentState;

	bool playFull;
	float currentTime;

	std::unordered_map<std::string , AnimationState> states;
public:

	void AddAnimationState(unsigned int startFrame,unsigned int endFrame, PlayType playType,std::string name);
	void SetCurrentAnimationState(std::string name);
	void AddTime(float time);
	void SetPlayType(PlayType type);
protected:
	friend class AnimatedEntity;

	void UpdateMatrixPallete(unsigned int boneIndex,DirectX::XMFLOAT4X4 & parent);

	void Init(SkeletonPtr skeleton,AnimationHandler handler);
	void Destroy();
	MatrixPallete & GetData();
};