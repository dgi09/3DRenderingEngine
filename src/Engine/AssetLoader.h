#pragma once
#include "Common.h"
#include <string>
#include "SkeletonPtr.h"
#include "AnimationPtr.h"
#include "StaticMeshData.h"
#include "AnimatedMeshData.h"
#include "DeviceDependableFactory.h"
#include "ModelPtr.h"

class EXPORT AssetLoader
{
	static AssetLoader * ptr;
	StaticMeshData staticMeshData;
	AnimatedMeshData animatedMeshData;

	DeviceDependableFactory * factory;

public:
	
	static AssetLoader * GetPtr();
	static void Destroy();

	void SetFactory(DeviceDependableFactory * factory);


	ModelPtr  LoadStaticModel(std::string fileName);
    SkeletonPtr LoadSkeleton(std::string fileName);

	ModelPtr  LoadAnimatedModel(std::string fileName);
	AnimationPtr LoadAnimation(std::string fileName);
	
};

