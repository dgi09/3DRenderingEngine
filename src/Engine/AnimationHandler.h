#pragma once 
#include "ResourceHandler.h"
#include "AnimationPtr.h"


class EXPORT AnimationHandler : public ResourceHandler<AnimationPtr>
{
public:
	AnimationHandler();
	AnimationHandler(AnimationPtr res,unsigned int animationID,ResourcePool<unsigned int> * pool);
	AnimationHandler(bool containsObject);
	void Destroy();
};