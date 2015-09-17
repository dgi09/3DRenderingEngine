#pragma once 
#include "Common.h"
#include "ResourceHandler.h"
#include "SkeletonPtr.h"

class EXPORT SkeletonHandler : public ResourceHandler<SkeletonPtr>
{
public:
	SkeletonHandler();
	SkeletonHandler(SkeletonPtr resource,unsigned int skeletonID,ResourcePool<unsigned int> * pool);
	SkeletonHandler(bool containsObject);
	void Destroy();
};