#include "TexturesCollection.h"
#include "Texture.h"

void TexturesCollection::Bind(ShaderType shader)
{
	if(size > 0)
	{
		if(shader == VERTEX)
			GetContext()->VSSetShaderResources(0,size,views);
		else 
			GetContext()->PSSetShaderResources(0,size,views);
	}
}

void TexturesCollection::Set(unsigned int index,Texture * texture)
{
	if(index < size && index >= 0)
		views[index] = texture->GetShaderResourcePointer();
}

void TexturesCollection::SetSize(unsigned int size)
{
	if(size > 0 && size <= MAX_TEXTURES_IN_COLLECTION)
	{
		this->size = size;
	}
}

TexturesCollection::TexturesCollection()
{
	size = 0;
}

void TexturesCollection::Clear()
{
	for(int i = 0;i < MAX_TEXTURES_IN_COLLECTION;i++)
	{
		views[i] = nullptr;
	}
}

