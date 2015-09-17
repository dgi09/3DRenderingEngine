#pragma once
#include <assimp/scene.h>
#include "StaticModel.h"


class StaticModelLoader
{
public:
	static StaticModel * GenerateStaticModel(const aiScene * scene);
};

