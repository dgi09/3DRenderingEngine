#include "AssetLoader.h"
#include <fstream>
#include "StaticMeshData.h"
#include "Vertex.h"
#include "AnimatedMeshData.h"
#include "Skeleton.h"
#include "Animation.h"
#include "BoneAnimationData.h"
#include <stdio.h>
#include "Heap.h"
#include "Model.h"


AssetLoader * AssetLoader::ptr = nullptr;

ModelPtr AssetLoader::LoadStaticModel(std::string fileName)
{
	std::ifstream file(fileName.c_str(),std::ios::binary);

	if(file.is_open())
	{
		unsigned int number;
		file.read((char*)&number,sizeof(unsigned int));
		if(number != 0)
			return ModelPtr(true);

		unsigned int numberOfMeshes;
		file.read((char*)&numberOfMeshes,4);

		ModelPtr ptr(Heap::GetPtr()->Models.New());
		Model * model = ptr.Get();

		for(unsigned int iMesh = 0;iMesh < numberOfMeshes;iMesh++)
		{
			file.read((char*)&staticMeshData.numberOfVerts,sizeof(unsigned int));

			file.read((char*)staticMeshData.vertecies,sizeof(StaticVert) * staticMeshData.numberOfVerts);
			file.read((char*)&staticMeshData.numberOfIndecies,sizeof(unsigned int));

			file.read((char*)staticMeshData.indecies,sizeof(unsigned int) * staticMeshData.numberOfIndecies);

			for(int i = 0;i < staticMeshData.numberOfVerts;i++)
			{
				staticMeshData.position[i] = staticMeshData.vertecies[i].pos;
			}

			MeshPtr meshPtr = factory->CreateMesh();
			Mesh * mesh = meshPtr.Get();
			mesh->Init();

			mesh->InitVertexBuffer(staticMeshData.numberOfVerts * sizeof(StaticVert),sizeof(StaticVert),staticMeshData.vertecies);
			mesh->InitIndexBuffer(staticMeshData.numberOfIndecies,staticMeshData.indecies);
			mesh->InitPositionBuffer(staticMeshData.position);
			model->AddMesh(meshPtr);

		}
		
		file.close();

		return ptr;
	}
	else return ModelPtr(true);

}

SkeletonPtr AssetLoader::LoadSkeleton(std::string fileName)
{
	FILE * f;
	fopen_s(&f,fileName.c_str(),"rb");
	unsigned int number;
	fread_s(&number,4,4,1,f);
	if(number != 50)
	{
		fclose(f);
		return SkeletonPtr(true);
	}

	unsigned int meshesCount;
	fread_s(&meshesCount,4,4,1,f);

	int vertCount;
	int indCount;
	for(int i = 0;i < meshesCount;i++)
	{
		fread_s(&vertCount,4,4,1,f);

		fseek(f,(sizeof(AnimatedVert) * vertCount),SEEK_CUR);

		fread_s(&indCount,4,4,1,f);
		fseek(f,(4 * indCount),SEEK_CUR);
	}
	
	

	DirectX::XMFLOAT4X4 mat;
	SkeletonPtr ptr(Heap::GetPtr()->Skeletons.New());

	Skeleton * skeleton = ptr.Get();
	skeleton->Init();

	fread_s(&skeleton->globalInverse,64,64,1,f);
	fread_s(&skeleton->numberOfBones,4,4,1,f);

	skeleton->bones = new Bone[skeleton->numberOfBones];
	int index;
	for(int i = 0;i<skeleton->numberOfBones;i++)
	{
		skeleton->bones[i].name = "name";
		
		fread_s(&skeleton->bones[i].offsetMatrix,64,64,1,f);

		fread_s(&skeleton->bones[i].transformation,64,64,1,f);

		int childCount;
		fread_s(&childCount,4,4,1,f);
		if(childCount > 0)
		{
			for(int ch = 0;ch < childCount;ch++)
			{
				fread_s(&index,4,4,1,f);
				skeleton->bones[i].childIndexes.push_back(index);
			}
			
		}
	}
	fclose(f);

	return ptr;
}

ModelPtr AssetLoader::LoadAnimatedModel(std::string fileName)
{
	FILE * f = nullptr;
	fopen_s(&f,fileName.c_str(),"rb");
	if(f != nullptr)
	{
		unsigned int number;
		fread_s(&number,4,4,1,f);
		if(number != 50)
		{
			fclose(f);
			return ModelPtr(true);
		}

		unsigned int meshesCount;
		fread_s(&meshesCount,4,4,1,f);

		ModelPtr ptr(Heap::GetPtr()->Models.New());
		Model * model = ptr.Get();

		for(unsigned int iMesh = 0;iMesh < meshesCount;iMesh++)
		{
			fread_s(&animatedMeshData.numOfVerts,4,4,1,f);

			fread_s(animatedMeshData.verts,sizeof(AnimatedVert) * animatedMeshData.numOfVerts,sizeof(AnimatedVert),animatedMeshData.numOfVerts,f);
			fread_s(&animatedMeshData.numOfIndecies,4,4,1,f);

			fread_s(animatedMeshData.indecies,sizeof(unsigned int) * animatedMeshData.numOfIndecies, 4 ,animatedMeshData.numOfIndecies,f);

			for(int i = 0;i < animatedMeshData.numOfVerts;i++)
			{
				animatedMeshData.positions[i] = animatedMeshData.verts[i].pos;
			}

			MeshPtr meshPtr = factory->CreateMesh();
			Mesh * mesh = meshPtr.Get();
			mesh->Init();
			mesh->InitVertexBuffer(animatedMeshData.numOfVerts * sizeof(AnimatedVert),sizeof(AnimatedVert),animatedMeshData.verts);
			mesh->InitIndexBuffer(animatedMeshData.numOfIndecies,animatedMeshData.indecies);
			mesh->InitPositionBuffer(animatedMeshData.positions);
			model->AddMesh(meshPtr);

		}
		

		fclose(f);

		return ptr;
	}
	else return nullptr;
}

AnimationPtr AssetLoader::LoadAnimation(std::string fileName)
{
	FILE * f = nullptr;
	fopen_s(&f,fileName.c_str(),"rb");
	unsigned int number;
	fread_s(&number,4,4,1,f);
	if(number != 2)
		return AnimationPtr(true);

	float dur;
	float fps;
	unsigned int numOfBones;

	fread_s(&dur,4,4,1,f);
	fread_s(&fps,4,4,1,f);
	fread_s(&numOfBones,4,4,1,f);
	
	if(numOfBones > MAX_BONES)
		return AnimationPtr(true);

	AnimationPtr ptr(Heap::GetPtr()->Animations.New());
	Animation * anim = ptr.Get();
	anim->Init();
	anim->duration = dur;
	anim->fps = fps;
	anim->numberOfBoneChannels = numOfBones;


	fread_s(anim->channelHaveData,sizeof(bool) * anim->numberOfBoneChannels,sizeof(bool),anim->numberOfBoneChannels,f);
    DirectX::XMFLOAT3 tempVec;
	DirectX::XMFLOAT4 tempQuat;

	for(int i = 0;i< anim->numberOfBoneChannels;i++)
	{
		BoneAnimationData & data = anim->channels[i];
		fread_s(&data.numberOfTranslationKeys,4,4,1,f);
		data.translationKeys = new TranslationKey[data.numberOfTranslationKeys];

		for(int t = 0;t < data.numberOfTranslationKeys;t++)
		{
			fread_s(&data.translationKeys[t].time,4,4,1,f);
			fread_s(&data.translationKeys[t].val,12,12,1,f);
		}

		
		fread_s(&data.numberOfRotationKeys,4,4,1,f);
		data.rotationKeys = new RotationKey[data.numberOfRotationKeys];

		for(int r = 0;r < data.numberOfRotationKeys;r++)
		{
			fread_s(&data.rotationKeys[r].time,4,4,1,f);
			fread_s(&data.rotationKeys[r].val,16,16,1,f);
		}

		fread_s(&data.numberOfScalingKeys,4,4,1,f);
		data.scalingKeys = new ScalingKey[data.numberOfScalingKeys];

		for(int s = 0;s < data.numberOfScalingKeys;s++)
		{
			fread_s(&data.scalingKeys[s].time,4,4,1,f);
			fread_s(&data.scalingKeys[s].val,12,12,1,f);
		}

	}
	fclose(f);

	return ptr;
}

AssetLoader * AssetLoader::GetPtr()
{
	if(ptr == nullptr)
		ptr = new AssetLoader;

	return ptr;
}

void AssetLoader::Destroy()
{

	if(ptr != nullptr)
		delete ptr;
}

void AssetLoader::SetFactory(DeviceDependableFactory * factory)
{
	this->factory = factory;
}


