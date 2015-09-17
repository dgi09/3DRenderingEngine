#include "AnimatedModelLoader.h"
#include "AnimVert.h"
#include "assimp/anim.h"
#include "Windows.h"


int AnimatedModelLoader::currentBoneIndex = 0;

AnimatedModel * AnimatedModelLoader::LoadAnimatedModel(const aiScene * scene)
{
	AnimatedModel * model = new AnimatedModel();
	unsigned int meshCount = scene->mNumMeshes;

	model->meshes.resize(meshCount);

	for(unsigned int iMesh = 0;iMesh < meshCount;iMesh++)
	{
		Mesh<AnimVert> & m = model->meshes[iMesh];
		aiMesh * mesh = scene->mMeshes[iMesh];


		unsigned int numberOfVerts = mesh->mNumVertices;
		m.numberOfVerts = numberOfVerts;

		m.verts = new AnimVert[mesh->mNumVertices];

		for(int i = 0;i<mesh->mNumVertices;i++)
		{

			ZeroMemory(m.verts[i].wights,4 * sizeof(float));
			ZeroMemory(m.verts[i].boneIndexes,4 * sizeof(unsigned int));

			m.verts[i].pos.x = mesh->mVertices[i].x;
			m.verts[i].pos.y = mesh->mVertices[i].y;
			m.verts[i].pos.z = mesh->mVertices[i].z;

			memcpy(&m.verts[i].normal,&mesh->mNormals[i],12);
			memcpy(&m.verts[i].tangent,&mesh->mTangents[i],12);

			if(mesh->HasTextureCoords(0))
			{
				m.verts[i].uv.x = mesh->mTextureCoords[0][i].x;
				m.verts[i].uv.y = mesh->mTextureCoords[0][i].y;
			}
			else 
			{
				m.verts[i].uv.x = 0.0f;
				m.verts[i].uv.y = 0.0f;
			}

		}

		unsigned int numberOfInd = mesh->mNumFaces * 3;
		m.numberOfIndecies = numberOfInd;

		m.indecies = new unsigned int[numberOfInd];

		for(int i = 0;i<mesh->mNumFaces;i++)
		{
			for(int j = 0;j< mesh->mFaces[i].mNumIndices;j++)
			{
				m.indecies[i * 3 +j] = mesh->mFaces[i].mIndices[j];
			}
		}

	}
	

	aiMesh * fm = nullptr;
	for(unsigned int i = 0;i < scene->mNumMeshes;i++)
	{
		if(scene->mMeshes[i]->HasBones())
		{
			fm = scene->mMeshes[i];
			break;
		}
	}

	aiNode * c = scene->mRootNode->FindNode(fm->mBones[0]->mName);
	while(c->mParent->mParent != nullptr)
	{
		c = c->mParent;
	}

	aiNode * meshNode = scene->mRootNode->FindNode(fm->mName);

	model->skeleton.globalInverse = scene->mRootNode->mTransformation.Inverse().Transpose();
	int numberOfBones = GetNumberOFBones(c);
	model->skeleton.bones.resize(numberOfBones + 1);

	BuildSkeleton(&model->skeleton,c);

	for(unsigned int iMesh = 0;iMesh < meshCount;iMesh++)
	{
		aiMesh * mesh = scene->mMeshes[iMesh];

		for(int i = 0;i < mesh->mNumBones;i++)
		{
			aiBone * bone = mesh->mBones[i];
			aiNode * n = scene->mRootNode->FindNode(bone->mName);

			unsigned int index = model->skeleton.nameMap[bone->mName.C_Str()];

			Bone & b = model->skeleton.bones[index];
			b.offsetMatix = bone->mOffsetMatrix.Transpose();
		}
	}
	


	for(unsigned int iMesh = 0;iMesh < meshCount;iMesh++)
	{
		Mesh<AnimVert> & m = model->meshes[iMesh];
		aiMesh * mesh = scene->mMeshes[iMesh];

		unsigned int * currentWI = new unsigned int[m.numberOfVerts];
		ZeroMemory(currentWI,sizeof(unsigned int) * m.numberOfVerts);

		for(int i = 0;i < mesh->mNumBones;i++)
		{
			aiBone * bone = mesh->mBones[i];
			for(int j = 0;j< bone->mNumWeights;j++)
			{
				unsigned int vertIt = bone->mWeights[j].mVertexId;
				unsigned int index = model->skeleton.nameMap[bone->mName.C_Str()];
				m.verts[vertIt].wights[currentWI[vertIt]] = bone->mWeights[j].mWeight;
				m.verts[vertIt].boneIndexes[currentWI[vertIt]] = index;
				currentWI[vertIt]++;
			}
		}

		delete currentWI;
	}
	
	return model;
}

void AnimatedModelLoader::BuildSkeleton(Skeleton * sk,aiNode * node)
{
	
	Bone * b = &sk->bones[AnimatedModelLoader::currentBoneIndex];
	b->bindTransform = node->mTransformation.Transpose();
	b->name = node->mName.C_Str();
	b->childCount = node->mNumChildren;

	sk->nameMap[b->name] = AnimatedModelLoader::currentBoneIndex;
	AnimatedModelLoader::currentBoneIndex++;
	int currentChild = 0;
	for(int i = 0;i < node->mNumChildren;i++)
	{
		unsigned int chIndex = AnimatedModelLoader::currentBoneIndex;
		b->child[currentChild] = chIndex;
		currentChild++;
		BuildSkeleton(sk,node->mChildren[i]);
	}
}

int AnimatedModelLoader::GetNumberOFBones(aiNode * node)
{
	int bones = node->mNumChildren;
	for(int i = 0;i<node->mNumChildren;i++)
	{
		bones += GetNumberOFBones(node->mChildren[i]);
	}
	return bones;
}

void AnimatedModelLoader::Skel(aiNode * node,aiMatrix4x4 * par)
{
	node->mTransformation = *par * node->mTransformation;
	for(int i = 0;i<node->mNumChildren;i++)
	{
		Skel(node->mChildren[i],&node->mTransformation);
	}
}
