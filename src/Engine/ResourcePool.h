#pragma once 
#include "Common.h"

#include "ObjectPoolPattern_Animation.h"
#include "ObjectPoolPattern_Skeleton.h"
#include "ObjectPoolPattern_Texture.h"
#include "ObjectPoolPattern_Model.h"


#include "MeshPtr.h"
#include "AnimationPtr.h"
#include "SkeletonPtr.h"
#include "TexturePtr.h"
#include "ModelPtr.h"


template <class Key>
class EXPORT ResourcePool
{
	ObjectPoolPattern_Texture<Key> textures;
	ObjectPoolPattern_Skeleton<Key> skeletons;
	ObjectPoolPattern_Animation<Key> animations;
	ObjectPoolPattern_Model<Key> models;

public:
	~ResourcePool();

	// Textures
	void AddTexture(Key id,TexturePtr  texture);
	bool TextureExist(Key id);

	TexturePtr  GetTexture(Key id);

	void DeleteAllTextures();
	void DeleteTexture(Key id);

	void RefTexture(Key id);
	void DerefTexture(Key id);
	//----------------

	//Skeletons
	void AddSkeleton(Key id,SkeletonPtr  skeleton);
	bool SkeletonExist(Key id);

	SkeletonPtr GetSkeleton(Key id);

	void DeleteAllSkeletons();
	void DeleteSkeleton(Key id);

	void RefSkeleton(Key id);
	void DerefSkeleton(Key id);

	//---------------

	// Animations

	void AddAnimation(Key id,AnimationPtr animation);
	bool AnimationExist(Key id);

	AnimationPtr GetAnimation(Key id);

	void DeleteAllAnimations();
	void DeleteAnimation(Key id);

	void RefAnimation(Key id);
	void DerefAnimation(Key id);

	// ---------------

	void AddModel(Key id,ModelPtr model);
	bool ModelExist(Key id);

	ModelPtr GetModel(Key id);

	void DeleteAllModels();
	void DeleteModel(Key id);

	void RefModel(Key id);
	void DerefModel(Key id);

};

template <class Key>
void ResourcePool<Key>::DerefModel(Key id)
{
	models.DerefObject(id);
}

template <class Key>
void ResourcePool<Key>::RefModel(Key id)
{
	models.RefObject(id);
}

template <class Key>
void ResourcePool<Key>::DeleteModel(Key id)
{
	models.DeleteObject(id);
}

template <class Key>
void ResourcePool<Key>::DeleteAllModels()
{
	models.DeleteAllObjects();
}

template <class Key>
ModelPtr ResourcePool<Key>::GetModel(Key id)
{
	return models.GetResource(id);
}

template <class Key>
bool ResourcePool<Key>::ModelExist(Key id)
{
	return models.ObjectExist(id);
}

template <class Key>
void ResourcePool<Key>::AddModel(Key id,ModelPtr model)
{
	models.AddObject(id,model);
}

template<class Key>
ResourcePool<Key>::~ResourcePool()
{
	DeleteAllTextures();
	DeleteAllSkeletons();
	DeleteAllAnimations();
	DeleteAllModels();
}



template<class Key>
void ResourcePool<Key>::AddTexture(Key id,TexturePtr texture)
{

	textures.AddObject(id,texture);
}

template<class Key>
bool ResourcePool<Key>::TextureExist(Key id)
{
	return textures.ObjectExist(id);
}

template<class Key>
TexturePtr ResourcePool<Key>::GetTexture(Key id)
{
	return textures.GetResource(id);
}

template<class Key>
void ResourcePool<Key>::DeleteAllTextures()
{
	textures.DeleteAllObjects();	
}

template<class Key>
void ResourcePool<Key>::DeleteTexture(Key id)
{
	textures.DeleteObject(id);
}

template<class Key>
void ResourcePool<Key>::RefTexture(Key id)
{
	textures.RefObject(id);
}

template<class Key>
void ResourcePool<Key>::DerefTexture(Key id)
{
	textures.DerefObject(id);
}

template<class Key>
void ResourcePool<Key>::AddSkeleton(Key id,SkeletonPtr skeleton)
{
	skeletons.AddObject(id,skeleton);
}

template<class Key>
bool ResourcePool<Key>::SkeletonExist(Key id)
{
	return skeletons.ObjectExist(id);
}

template<class Key>
SkeletonPtr ResourcePool<Key>::GetSkeleton(Key id)
{
	return skeletons.GetResource(id);
}

template<class Key>
void ResourcePool<Key>::DeleteAllSkeletons()
{
	skeletons.DeleteAllObjects();
}

template<class Key>
void ResourcePool<Key>::DeleteSkeleton(Key id)
{
	skeletons.DeleteObject(id);
}

template<class Key>
void ResourcePool<Key>::RefSkeleton(Key id)
{
	skeletons.RefObject(id);
}

template<class Key>
void ResourcePool<Key>::DerefSkeleton(Key id)
{
	skeletons.DerefObject(id);
}

template<class Key>
void ResourcePool<Key>::AddAnimation(Key id,AnimationPtr animation)
{
	animations.AddObject(id,animation);
}

template<class Key>
bool ResourcePool<Key>::AnimationExist(Key id)
{
	return animations.ObjectExist(id);
}

template<class Key>
AnimationPtr ResourcePool<Key>::GetAnimation(Key id)
{
	return animations.GetResource(id);
}

template<class Key>
void ResourcePool<Key>::DeleteAllAnimations()
{
	animations.DeleteAllObjects();
}

template<class Key>
void ResourcePool<Key>::DeleteAnimation(Key id)
{
	animations.DeleteObject(id);
}

template<class Key>
void ResourcePool<Key>::RefAnimation(Key id)
{
	animations.RefObject(id);
}

template<class Key>
void ResourcePool<Key>::DerefAnimation(Key id)
{
	animations.DerefObject(id);
}
