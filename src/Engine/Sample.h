#pragma once 
#include "Common.h"
#include "TexturePtr.h"
#include "PixelShaderPtr.h"

class DeviceDependableFactory;

class EXPORT Sample 
{
	PixelShaderPtr ps;
	ID3D11Device * device;

public:
	void Init(DeviceDependableFactory * factory);
	void SetDevice(ID3D11Device * device);

	void SetEffect(const char * p);
	void Destroy();

	void Run(TexturePtr src,TexturePtr dst);
	void Run(TexturePtr src,ID3D11RenderTargetView * dst);

private:

	void Internal(ID3D11ShaderResourceView * src,ID3D11RenderTargetView * dst);
};
