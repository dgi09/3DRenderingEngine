#include "Skeleton.h"
#include "Heap.h"
#include "SkeletonPtr.h"

SkeletonPtr Skeleton::Copy()
{
	SkeletonPtr ptr(Heap::GetPtr()->Skeletons.New());

	Skeleton * n = ptr.Get();

	n->numberOfBones = this->numberOfBones;
	n->bones = new Bone[n->numberOfBones];
	n->globalInverse = globalInverse;
	memcpy(n->bones,this->bones,sizeof(Bone) * n->numberOfBones);
	return ptr;
}

void Skeleton::Init()
{
	bones = nullptr;
}

void Skeleton::Destroy()
{
	if(bones != nullptr)
		delete[] bones;
}
