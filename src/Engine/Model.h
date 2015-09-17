#pragma once 
#include "Common.h"
#include "MeshPtr.h"
#include <vector>


class EXPORT Model
{
	std::vector<MeshPtr> meshes;
public:

	Model();
	~Model();

	void AddMesh(MeshPtr ptr);
	unsigned int GetNumberOfMeshes();
	MeshPtr GetMeshAt(unsigned int index);

	void Destroy();

};
