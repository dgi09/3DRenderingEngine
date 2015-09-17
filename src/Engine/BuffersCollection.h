#pragma once 
#include "Common.h"
#include "DeviceDependable.h"
#include "ShaderType.h"

class EXPORT ConstantBuffer;

#define MAX_BUFFERS_IN_COLLECTION 10

class EXPORT BuffersCollection : public DeviceDependable
{
	ID3D11Buffer * buffers[MAX_BUFFERS_IN_COLLECTION];
	unsigned int size;
public:
	BuffersCollection();
	void SetSize(unsigned int size);
	void Bind(ShaderType shader);
	void Set(unsigned int index,ConstantBuffer * buffer);
	void Clear();
};