#include "AnimationHandler.h"

AnimationHandler::AnimationHandler(AnimationPtr res,unsigned int animationID,ResourcePool<unsigned int> * pool) : ResourceHandler(res,animationID,pool)
{
	pool->RefAnimation(animationID);
}

AnimationHandler::AnimationHandler()
{

}

AnimationHandler::AnimationHandler(bool containsObject) : ResourceHandler(containsObject)
{

}


void AnimationHandler::Destroy()
{
	if(containsObject)
		pool->DerefAnimation(id);
}
