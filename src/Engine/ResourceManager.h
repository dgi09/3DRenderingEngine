#pragma once
#include "Common.h"
#include <string>
#include "AnimationHandler.h"
#include "SkeletonHandler.h"
#include "TextureHandler.h"
#include "ResourcePool.h"
#include <unordered_map>
#include "ModelHandler.h"


class EXPORT StaticMeshData;
class EXPORT AnimatedMeshData;
class EXPORT SkeletonHandler;
class EXPORT DeviceDependableFactory;
class EXPORT MeshHandler;
class EXPORT TextureHandler;
class EXPORT Skeleton;
class EXPORT AnimationHandler;
class EXPORT Animation;

class EXPORT ResourceManager
{
	ResourcePool<unsigned int> * pool;
	DeviceDependableFactory * factory;
	std::hash<std::string> hasher;
public:
	ResourceManager(DeviceDependableFactory * factory);
	~ResourceManager(void);

	
	ModelHandler GetStaticModel(std::string resID);
	ModelHandler GetStaticModelFromFile(std::string fileName,std::string resID);

	TextureHandler GetTexture(std::string fileName);

	ModelHandler GetAnimatedModelFromFile(std::string fileName,std::string resID);
	ModelHandler GetAnimatedModel(std::string resID);

	SkeletonHandler GetSkeletonFromFile(std::string fileName,std::string resID);
	SkeletonHandler GetSkeletonFromMemory(SkeletonPtr skeleton,std::string resID);
	SkeletonHandler GetSkeleton(std::string resID);

	AnimationHandler GetAnimationFromFile(std::string fileName,std::string resID);
	AnimationHandler GetAnimationFromMemory(AnimationPtr anim,std::string resID);
	AnimationHandler GetAnimation(std::string resID);

};
