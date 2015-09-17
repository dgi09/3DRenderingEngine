#include "SkeletonHandler.h"
#include "ResourcePool.h"


SkeletonHandler::SkeletonHandler(SkeletonPtr resource,unsigned int skeletonID,ResourcePool<unsigned int> * pool) : ResourceHandler(resource,skeletonID,pool)
{
	pool->RefSkeleton(skeletonID);
}

SkeletonHandler::SkeletonHandler()
{

}

SkeletonHandler::SkeletonHandler(bool containsObject) : ResourceHandler(containsObject)
{

}

void SkeletonHandler::Destroy()
{
	if(containsObject)
	pool->DerefSkeleton(id);
}
