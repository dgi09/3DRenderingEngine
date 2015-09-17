#include "StaticModel.h"

void StaticModel::Serialize(std::ofstream & file)
{
	int number = 0;
	file.write((const char*)&number,4);
	unsigned int meshCount = meshes.size();

	file.write((const char*)&meshCount,4);

	for(unsigned int i = 0;i < meshCount;i++)
	{
		Mesh<StaticVert> & mesh = meshes[i];
		file.write((const char*)&mesh.numberOfVerts,4);
		file.write((const char*)mesh.verts,sizeof(StaticVert) * mesh.numberOfVerts);
		file.write((const char*)&mesh.numberOfIndecies,4);
		file.write((const char*)mesh.indecies,4 * mesh.numberOfIndecies);
	}
}

StaticModel::~StaticModel()
{
	
}
