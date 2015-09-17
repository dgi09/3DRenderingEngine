#include "ResourceManager.h"
#include "ResourcePool.h"
#include "DeviceDependableFactory.h"
#include "Mesh.h"
#include "StaticMeshData.h"
#include "DeviceDependableFactory.h"
#include "TextureHandler.h"
#include "Texture.h"
#include "AssetLoader.h"
#include "AnimatedMeshData.h"
#include "SkeletonHandler.h"
#include "AnimationHandler.h"
#include "Animation.h"
#include "ModelHandler.h"

ResourceManager::ResourceManager(DeviceDependableFactory * factory)
{
	this->pool = new ResourcePool<unsigned int>();
	this->factory = factory;
}

ResourceManager::~ResourceManager(void)
{
	factory = nullptr;
	delete pool;
}


ModelHandler ResourceManager::GetStaticModel(std::string resID)
{
	unsigned int id = hasher(resID);
	if(pool->ModelExist(id))
	{
		ModelHandler handler(pool->GetModel(id),id,pool);
		return handler;
	}
	else 
	{
		ModelHandler handler(false);
		return handler;
	}
}

ModelHandler ResourceManager::GetStaticModelFromFile(std::string fileName,std::string resID)
{
	unsigned int id = hasher(resID);
	if(pool->ModelExist(id))
	{
		ModelHandler handler(pool->GetModel(id),id,pool);
		return handler;
	}
	else 
	{

		ModelPtr modelPtr = AssetLoader::GetPtr()->LoadStaticModel(fileName);
		if(modelPtr.IsNull())
		{
			ModelHandler handler(false);
			return handler;
		}

		return ModelHandler(modelPtr,id,pool);
	}
}


TextureHandler ResourceManager::GetTexture(std::string fileName)
{
	unsigned int id = hasher(fileName);
	if(pool->TextureExist(id))
	{
		TextureHandler handler(pool->GetTexture(id),id,pool);
		return handler;
	}
	else 
	{
		TexturePtr texturePtr = factory->CreateTexture();
		Texture * texture = texturePtr.Get();

		texture->LoadFromFile(fileName.c_str());
		pool->AddTexture(id,texturePtr);
		TextureHandler handler(texturePtr,id,pool);
		return handler;
	}
}


ModelHandler ResourceManager::GetAnimatedModelFromFile(std::string fileName,std::string resID)
{
	unsigned int id = hasher(resID);
	if(pool->ModelExist(id))
	{
		return ModelHandler(pool->GetModel(id),id,pool);
	}
	else 
	{
		ModelPtr modelPtr = AssetLoader::GetPtr()->LoadAnimatedModel(fileName);
		if(modelPtr.IsNull())
			return ModelHandler(false);

		pool->AddModel(id,modelPtr);

		return ModelHandler(modelPtr,id,pool);
	}
}

ModelHandler ResourceManager::GetAnimatedModel(std::string resID)
{
	unsigned int id = hasher(resID);
	if(pool->ModelExist(id))
	{
		return ModelHandler(pool->GetModel(id),id,pool);
	}
	else 
	{
		return ModelHandler(false);
	}
}

SkeletonHandler ResourceManager::GetSkeletonFromFile(std::string fileName,std::string resID)
{
	unsigned int id = hasher(resID);
	if(pool->SkeletonExist(id))
	{
		return SkeletonHandler(pool->GetSkeleton(id),id,pool);
		
	}
	else 
	{
		SkeletonPtr data = AssetLoader::GetPtr()->LoadSkeleton(fileName);
		if(data.IsNull())
			return SkeletonHandler(false);
		
		pool->AddSkeleton(id,data);

		return SkeletonHandler(data,id,pool);
		
	}
}

SkeletonHandler ResourceManager::GetSkeletonFromMemory(SkeletonPtr skeleton,std::string resID)
{
	unsigned int id = hasher(resID);
	if(pool->SkeletonExist(id))
	{
		return SkeletonHandler(pool->GetSkeleton(id),id,pool);
		
	}
	else 
	{
		if(skeleton.IsNull())
			return SkeletonHandler(false);


		SkeletonPtr res = skeleton.Get()->Copy();

		pool->AddSkeleton(id,res);

		return SkeletonHandler(res,id,pool);
	}
}

SkeletonHandler  ResourceManager::GetSkeleton(std::string resID)
{
	unsigned int id = hasher(resID);
	if(pool->SkeletonExist(id))
	{
		return SkeletonHandler(pool->GetSkeleton(id),id,pool);
	}
	else return SkeletonHandler(false);
}

AnimationHandler  ResourceManager::GetAnimationFromFile(std::string fileName,std::string resID)
{
	unsigned int id = hasher(resID);
	if(pool->AnimationExist(id))
	{
		return AnimationHandler(pool->GetAnimation(id),id,pool);
	}
	else
	{
		AnimationPtr anim = AssetLoader::GetPtr()->LoadAnimation(fileName);
		if(anim.IsNull())
			return AnimationHandler(false);

		AnimationHandler handler = GetAnimationFromMemory(anim,resID);

		return handler;
	}
}

AnimationHandler ResourceManager::GetAnimationFromMemory(AnimationPtr anim,std::string resID)
{
	unsigned int id = hasher(resID);
	if(pool->AnimationExist(id))
	{
		return AnimationHandler(pool->GetAnimation(id),id,pool);
	}
	else 
	{
		pool->AddAnimation(id,anim);
		return AnimationHandler(anim,id,pool);
	}
}

AnimationHandler  ResourceManager::GetAnimation(std::string resID)
{
	unsigned int id = hasher(resID);
	if(pool->AnimationExist(id))
	{
		return AnimationHandler(pool->GetAnimation(id),id,pool);
		
	}
	else return AnimationHandler(false);
}


