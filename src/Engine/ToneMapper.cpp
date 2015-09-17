#include "ToneMapper.h"
#include "DeviceDependableFactory.h"
#include "FullScreenQuad.h"

void ToneMapper::Init(DeviceDependableFactory * factory)
{
	shader = factory->CreatePixelShader();

}

void ToneMapper::SetDevice(ID3D11Device * device)
{
	this->device = device;
}

void ToneMapper::SetShaderCode(const char * code)
{
	shader.Get()->LoadFromString(code,strlen(code),"main");

}

void ToneMapper::Destroy()
{
	shader.Delete();
}

void ToneMapper::Run(TexturePtr src,TexturePtr dst)
{
	IntRun(src.Get()->GetShaderResourcePointer(),dst.Get()->GetRenderTargetPtr());
}

void ToneMapper::Run(TexturePtr src,ID3D11RenderTargetView * dst)
{
	IntRun(src.Get()->GetShaderResourcePointer(),dst);
}

void ToneMapper::IntRun(ID3D11ShaderResourceView * src,ID3D11RenderTargetView * dst)
{
	ID3D11DeviceContext * context;
	device->GetImmediateContext(&context);

	ID3D11ShaderResourceView * srvNull[2] = {nullptr,nullptr};
	ID3D11RenderTargetView * rtvNull = nullptr;

	shader.Get()->Bind();
	FullScreenQuad::BindVS();

	ID3D11ShaderResourceView * srcSrv[2] = {src,bloomTexture.Get()->GetShaderResourcePointer()};


	context->PSSetShaderResources(0,2,srcSrv);
	context->OMSetRenderTargets(1,&dst,nullptr);

	FullScreenQuad::Draw();

	context->PSSetShaderResources(0,2,srvNull);
	context->OMSetRenderTargets(1,&rtvNull,nullptr);

}

void ToneMapper::SetBloomTexture(TexturePtr txt)
{
	bloomTexture = txt;
}


