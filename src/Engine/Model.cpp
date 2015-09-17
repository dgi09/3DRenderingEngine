#include "Model.h"

void Model::AddMesh(MeshPtr ptr)
{
	meshes.push_back(ptr);
}

unsigned int Model::GetNumberOfMeshes()
{
	return meshes.size();
}

MeshPtr Model::GetMeshAt(unsigned int index)
{
	if(index >= 0 && index < meshes.size())
		return meshes[index];
	else return nullptr;
}

void Model::Destroy()
{
	for(unsigned int i = 0;i < meshes.size();i++)
	{
		meshes[i].Delete();
	}
}

Model::Model()
{

}

Model::~Model()
{

}
