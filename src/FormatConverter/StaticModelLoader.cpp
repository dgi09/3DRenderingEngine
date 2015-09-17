#include "StaticModelLoader.h"

StaticModel * StaticModelLoader::GenerateStaticModel(const aiScene * scene)
{
	StaticModel * model = new StaticModel();

	unsigned int meshesCount = scene->mNumMeshes;
	model->meshes.resize(meshesCount);
	for(unsigned int iMesh = 0;iMesh < meshesCount;iMesh++)
	{
		aiMesh * mesh = scene->mMeshes[iMesh];
		Mesh<StaticVert> & m = model->meshes[iMesh];

		unsigned int numberOfVerts = mesh->mNumVertices;
		m.numberOfVerts = numberOfVerts;

		m.verts = new StaticVert[mesh->mNumVertices];

		for(int i = 0;i<mesh->mNumVertices;i++)
		{
			m.verts[i].position.x = mesh->mVertices[i].x;
			m.verts[i].position.y = mesh->mVertices[i].y;
			m.verts[i].position.z = mesh->mVertices[i].z;

			memcpy(&m.verts[i].normal,&mesh->mNormals[i],12);

			if(mesh->HasTangentsAndBitangents())
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
	

	return model;
}
