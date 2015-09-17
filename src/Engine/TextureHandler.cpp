#include "TextureHandler.h"
#include "ResourcePool.h"
#include "Texture.h"

TextureHandler::TextureHandler(TexturePtr resource,unsigned int textureID,ResourcePool<unsigned int> * pool) : ResourceHandler(resource,textureID,pool)
{
	pool->RefTexture(id);
}

TextureHandler::TextureHandler()
{

}

TextureHandler::TextureHandler(bool containsObject) : ResourceHandler(containsObject)
{

}


void TextureHandler::Destroy()
{
	if(containsObject)
	pool->DerefTexture(id);
}

