#pragma once 
#include "Common.h"
#include "ResourceHandler.h"
#include "TexturePtr.h"

class EXPORT TextureHandler : public ResourceHandler<TexturePtr>
{
public:
	TextureHandler();
	TextureHandler(TexturePtr resource,unsigned int textureID,ResourcePool<unsigned int> * pool);
	TextureHandler(bool containsObject);
	void Destroy();
};
