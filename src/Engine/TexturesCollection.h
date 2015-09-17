#pragma once 
#include "Common.h"
#include "DeviceDependable.h"
#include "ShaderType.h"

class EXPORT Texture;

#define MAX_TEXTURES_IN_COLLECTION 10

class EXPORT TexturesCollection : public DeviceDependable
{
	unsigned int size;
	ID3D11ShaderResourceView * views[MAX_TEXTURES_IN_COLLECTION];
public:
	TexturesCollection();
	void Bind(ShaderType shader);
	void Set(unsigned int index,Texture * texture);
	void SetSize(unsigned int size);
	void Clear();
};