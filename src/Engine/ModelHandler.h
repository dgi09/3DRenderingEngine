#pragma  once 
#include "ResourceHandler.h"
#include "ModelPtr.h"

class EXPORT ModelHandler : public ResourceHandler<ModelPtr>
{
public:
	ModelHandler();
	ModelHandler(ModelPtr resource,unsigned int modelID,ResourcePool<unsigned int> * pool);
	ModelHandler(bool containsObject);
	void Destroy();
};