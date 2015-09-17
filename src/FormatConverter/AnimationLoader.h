#pragma once

#include "AnimatedModel.h"
#include <assimp/scene.h>
#include "Animation.h"


class AnimationLoader
{
public:
	static Animation * LoadAnimation(AnimatedModel * model , const aiScene * scene); 
};

