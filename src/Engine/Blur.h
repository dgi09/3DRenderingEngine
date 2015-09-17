#pragma once 
#include "Common.h"
#include "TexturePtr.h"
#include "DeviceDependableFactory.h"
#include <d3d11.h>
#include "ComputeShaderPtr.h"

class EXPORT Blur
{
	ComputeShaderPtr csV;
	ComputeShaderPtr csH;

	ID3D11Device * dev;
	
	unsigned int dispatchSizeX,dispatchSizeY;

	ConstantBufferPtr bufferPixelSize;
public:

	void Init(DeviceDependableFactory * factory);
	void Destroy();


	void SetDevice(ID3D11Device * device);
	void SetSize(unsigned int width,unsigned int height);


	void SetHorizonatlBlurEffect(const char * c);
	void SetVerticalBlurEffect(const char * c);


	void RunHorizontal(TexturePtr src,TexturePtr dst);
	void RunHorizontal(TexturePtr src,ID3D11UnorderedAccessView * dst);

	void RunVertical(TexturePtr src,TexturePtr dst);
	void RunVertical(TexturePtr src,ID3D11UnorderedAccessView * dst);

private:
	void IntRunHorizontal(ID3D11ShaderResourceView * src,ID3D11UnorderedAccessView * dest);
	void IntRunVertical(ID3D11ShaderResourceView * src,ID3D11UnorderedAccessView * dst);
};