#pragma once 
#include "Common.h"
#include "EntityBase.h"
#include "MatrixPallete.h"
#include "SkeletonHandler.h"
#include "AnimationHandler.h"
#include "ConstantBufferPtr.h"
#include "AnimationController.h"
#include <vector>
#include <unordered_map>
#include "MatrixPallete.h"

class EXPORT ResourceManager;
class EXPORT DeviceDependableFactory;

class EXPORT AnimatedEntity : public EntityBase
{
	SkeletonHandler  skeletonHandler;
	ConstantBufferPtr palleteBuffer;

	std::vector<AnimationController> animations;

	AnimationController * currentAnimController;
	MatrixPallete bindPosePallete;
public:
	void Init(ModelHandler model,SkeletonHandler skeleton,ResourceManager * resMgr, DeviceDependableFactory * factory);
	void Destroy();

	void Draw(EffectBinder * binder);
	AnimationController * LoadAnimationFromFile(std::string fileName,std::string id);
	void SetCurrentAnimationController(AnimationController * controller);
protected:
	void BindAnimationData(EffectBinder * binder);
	void FillBindPosePallete(unsigned int boneIndex,DirectX::XMFLOAT4X4 & parent);
	void Skin();
	
};