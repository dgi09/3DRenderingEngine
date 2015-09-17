#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/ProgressHandler.hpp>
#include <assimp/postprocess.h>
#include <fstream>
#include "StaticModel.h"
#include "StaticModelLoader.h"
#include "AnimatedModel.h"
#include "AnimatedModelLoader.h"
#include "Animation.h"
#include "AnimationLoader.h"
#include <stdio.h>
#include <string>

using namespace std;


string getFileName(string full)
{
	int dotPos,firstLetterPos;

	dotPos = full.find_last_of('.');

	for(int i = dotPos-1;i >= 0;i--)
	{
		if(full[i] == '\\')
		{
			firstLetterPos = i;
			break;
		}
	}

	string name = "";
	for(int i = firstLetterPos + 1;i <= dotPos-1;i++)
	{
		name += full[i];
	}
	return name;
}

std::string getExtention(std::string full)
{
	int dotPos = full.find_last_of('.');

	string ext = "";
	for(int i = dotPos + 1;i < full.size();i++)
	{
		ext += full[i];
	}

	return ext;
}

int main(int argc, char *argv[])
{
	if(argc < 2)
		 return 0;
	
	
	std::string arg = argv[1];

	std::string name = getFileName(arg);


	Assimp::Importer importer;
	const aiScene * scene = importer.ReadFile(arg,aiProcess_Triangulate | aiProcess_ConvertToLeftHanded | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices | aiProcess_FindInvalidData);
	if(scene->HasMeshes())
	{

		bool animated = false;
		for(int i = 0;i < scene->mNumMeshes;i++)
		{
			aiMesh * mesh = scene->mMeshes[i];
			if(mesh->HasBones())
			{
				animated = true;
				break;
			}
		}
		
		
			if(!animated)
			{
				StaticModel * model = StaticModelLoader::GenerateStaticModel(scene);
				std::ofstream file(name + ".smodel",std::ios::binary);
				model->Serialize(file);

				file.close();
				delete model;
			}
			else 
			{
				AnimatedModel * model = AnimatedModelLoader::LoadAnimatedModel(scene);
				string fullName = name + ".amodel";
				FILE * file = fopen(fullName.c_str(),"wb");
				model->Serialize(file);
				fclose(file);

				if(scene->HasAnimations())
				{

					Animation * anim = AnimationLoader::LoadAnimation(model,scene);
					fullName = name + ".anim";
					FILE * f = fopen(fullName.c_str(),"wb");
					anim->Serialize(f);
					fclose(f);
					delete anim;
				}
				delete model;
			}
		

	}
	return 0;
}