#include "ModelHandler.h"

ModelHandler::ModelHandler(ModelPtr resource,unsigned int meshID,ResourcePool<unsigned int> * pool) : ResourceHandler(resource,meshID,pool)
{
	pool->RefModel(meshID);
}

ModelHandler::ModelHandler()
{

}

ModelHandler::ModelHandler(bool containsObject) : ResourceHandler(containsObject)
{

}


void ModelHandler::Destroy()
{
	if(containsObject)
	{
		pool->DerefModel(id);
	}

}