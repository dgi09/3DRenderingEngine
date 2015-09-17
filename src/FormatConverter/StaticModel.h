#pragma once
#include <fstream>
#include "StaticVert.h"
#include "Mesh.h"
#include <vector>

class StaticModel
{
public:
	std::vector<Mesh<StaticVert>> meshes;

	void Serialize(std::ofstream & file);
	~StaticModel();
};

