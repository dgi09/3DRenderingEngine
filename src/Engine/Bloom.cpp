#include "Bloom.h"
#include "DeviceDependableFactory.h"
#include "Texture.h"

void Bloom::Init(DeviceDependableFactory * factory)
{
	shader = factory->CreateComputeShader();
}

void Bloom::SetDevice(ID3D11Device * device)
{
	this->device = device;
}

void Bloom::SetShader(const char * cs)
{
	shader.Get()->LoadFromString(cs,"main");

}

void Bloom::Run(TexturePtr src,TexturePtr dst)
{
	ID3D11DeviceContext * context;
	device->GetImmediateContext(&context);

	shader.Get()->Bind();
	ID3D11ShaderResourceView * srvNull = nullptr;
	ID3D11UnorderedAccessView * uavNull = nullptr;

	ID3D11ShaderResourceView * srcSrv = src.Get()->GetShaderResourcePointer();
	context->CSSetShaderResources(0,1,&srcSrv);

	ID3D11UnorderedAccessView * dstUav = dst.Get()->GetUnorderedView();
	context->CSSetUnorderedAccessViews(0,1,&dstUav,nullptr);

	shader.Get()->Run(dispatchSizeX,dispatchSizeY,1);

	context->CSSetShaderResources(0,1,&srvNull);
	context->CSSetUnorderedAccessViews(0,1,&uavNull,nullptr);

	shader.Get()->Unbind();
}

void Bloom::Destroy()
{
	shader.Delete();
}

void Bloom::SetSize(unsigned int width,unsigned int height)
{
	if(width % 10 == 0)
		dispatchSizeX = width / 10;
	else dispatchSizeX = width / 10 + (10 - width % 10);
	
	if(height % 10 == 0)
		dispatchSizeY = height / 10;
	else dispatchSizeY = height / 10 + (10 - height % 10);
}

