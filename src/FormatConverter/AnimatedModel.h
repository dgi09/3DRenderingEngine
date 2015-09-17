#pragma once
#include "AnimVert.h"
#include "Skeleton.h"
#include <stdio.h>
#include "Mesh.h"
#include <vector>

class AnimatedModel
{
public:
	~AnimatedModel();
	std::vector<Mesh<AnimVert>> meshes;

	Skeleton skeleton;

	void Serialize(FILE * file);
};

