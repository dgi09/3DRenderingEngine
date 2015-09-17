#pragma once 
#include "Common.h"
#include "ObjectPool.h"
#include "Mesh.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Texture.h"
#include "Sampler.h"
#include "BuffersCollection.h"
#include "TexturesCollection.h"
#include "SamplersCollection.h"
#include "Animation.h"
#include "Skeleton.h"
#include "EntityEffect.h"
#include "ConstantBuffer.h"
#include "Model.h"
#include "ComputeShader.h"

class EXPORT Heap 
{
	static Heap * ptr;

public:
	
	static Heap * GetPtr();
	static void Free();

	ObjectPool<Mesh> Meshes;
	ObjectPool<VertexShader> VertexShaders;
	ObjectPool<PixelShader> PixelShaders;
	ObjectPool<ComputeShader> ComputeShaders;
	ObjectPool<Texture> Textures;
	ObjectPool<Sampler> Samplers;
	ObjectPool<ConstantBuffer> ConstantBuffers;
	
	ObjectPool<Animation> Animations;
	ObjectPool<Skeleton> Skeletons;
	ObjectPool<EntityEffect> EntityEffects;

	ObjectPool<Model> Models;
};