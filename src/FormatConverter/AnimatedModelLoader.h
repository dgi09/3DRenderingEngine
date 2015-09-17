#pragma once
#include <assimp/scene.h>
#include "AnimatedModel.h"

class AnimatedModelLoader
{
	static int currentBoneIndex;
public:
	static AnimatedModel * LoadAnimatedModel(const aiScene * scene);
	static void BuildSkeleton(Skeleton * sk,aiNode * node);
	static int GetNumberOFBones(aiNode * node);
	static void Skel(aiNode * node,aiMatrix4x4 * par);
};

