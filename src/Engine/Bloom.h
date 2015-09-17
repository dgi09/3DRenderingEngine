#pragma once 
#include "Common.h"
#include "ComputeShaderPtr.h"
#include "TexturePtr.h"

class DeviceDependableFactory;

class EXPORT Bloom 
{
	ComputeShaderPtr shader;
	ID3D11Device * device;

	unsigned int dispatchSizeX;
	unsigned int dispatchSizeY;

	ID3D11RenderTargetView * target;
public:

	void Init(DeviceDependableFactory * factory);
	void Destroy();
	void SetDevice(ID3D11Device * device);
	void SetShader(const char * cs);
	void SetSize(unsigned int width,unsigned int height);

	void Run(TexturePtr src,TexturePtr dst);
	

};
