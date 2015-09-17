#include "Sample.h"
#include "Pos_TexCoord_Layout.h"
#include "DeviceDependableFactory.h"
#include "Color.h"
#include "FullScreenQuad.h"

void Sample::Init(DeviceDependableFactory * factory)
{
	ps = factory->CreatePixelShader();
}

void Sample::SetDevice(ID3D11Device * device)
{
	this->device = device;
}

void Sample::Run(TexturePtr src,TexturePtr dst)
{
	Internal(src.Get()->GetShaderResourcePointer(),dst.Get()->GetRenderTargetPtr());
}

void Sample::Run(TexturePtr src,ID3D11RenderTargetView * dst)
{
	Internal(src.Get()->GetShaderResourcePointer(),dst);
}

void Sample::Internal(ID3D11ShaderResourceView * src,ID3D11RenderTargetView * dst)
{
	ID3D11DeviceContext * context;
	device->GetImmediateContext(&context);

	ps.Get()->Bind();

	context->OMSetRenderTargets(1,&dst,nullptr);
	Color c = Color::White();
	context->ClearRenderTargetView(dst,(float*)&c);
	

	context->PSSetShaderResources(0,1,&src);
	FullScreenQuad::BindVS();

	FullScreenQuad::Draw();

	FullScreenQuad::UnbindVS();

	ID3D11RenderTargetView * rtvNull = nullptr;
	ID3D11ShaderResourceView * srvNull = nullptr;

	context->OMSetRenderTargets(1,&rtvNull,nullptr);
	context->PSSetShaderResources(0,1,&srvNull);
}

void Sample::SetEffect(const char * p)
{
	ps.Get()->LoadFromString(p,strlen(p),"main");
}

void Sample::Destroy()
{
	ps.Delete();
}
