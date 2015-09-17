#pragma once 
#include "Common.h"
#include "IDestroyable.h"
#include <d3d11.h>

#include "DeviceDependable.h"

class ComputeShader : public DeviceDependable , public IDestroyable
{
	ID3D11ComputeShader * shader;
public:

	void Init();
	void LoadFromFile(const char * fileName , const char * entryPoint);
	void LoadFromString(const char * code,const char * entryPoint);
	void Destroy();

	void Bind();
	void Unbind();
	void Run(unsigned int x,unsigned int y,unsigned int z);
};