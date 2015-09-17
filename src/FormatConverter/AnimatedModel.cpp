#include "AnimatedModel.h"
#include <iostream>

void AnimatedModel::Serialize(FILE * file)
{

	unsigned int number = 50;
	fwrite(&number,4,1,file);
	unsigned int meshesCount = meshes.size();
	fwrite(&meshesCount,4,1,file);

	for(unsigned int i = 0;i < meshesCount;i++)
	{
		Mesh<AnimVert> & mesh = meshes[i];

		fwrite(&mesh.numberOfVerts,4,1,file);

		fwrite(&mesh.verts[0],sizeof(AnimVert),mesh.numberOfVerts,file);

		fwrite(&mesh.numberOfIndecies,4,1,file);
		fwrite(mesh.indecies,4,mesh.numberOfIndecies,file);
	}
	

	fwrite(&skeleton.globalInverse,64,1,file);
	int nOfBones = skeleton.bones.size();
	fwrite(&nOfBones,4,1,file);

	for(int i = 0;i < nOfBones;i++)
	{
		fwrite(&skeleton.bones[i].offsetMatix,64,1,file);
		fwrite(&skeleton.bones[i].bindTransform,64,1,file);


		fwrite(&skeleton.bones[i].childCount,4,1,file);
		if(skeleton.bones[i].childCount > 0)
		{
			fwrite(&skeleton.bones[i].child[0],4,skeleton.bones[i].childCount,file);
		}
	}
}

AnimatedModel::~AnimatedModel()
{
	

}
