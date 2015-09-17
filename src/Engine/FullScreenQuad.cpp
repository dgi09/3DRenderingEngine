#include "FullScreenQuad.h"
#include "Vertex.h"
#include "DeviceDependableFactory.h"
#include "Mesh.h"

VertexShaderPtr FullScreenQuad::vs = VertexShaderPtr(true);
ID3D11Device * FullScreenQuad::dev = nullptr;

void FullScreenQuad::Init(DeviceDependableFactory * factory)
{
	vs = factory->CreateVertexShader();

}

void FullScreenQuad::Draw()
{
	ID3D11DeviceContext * context;
	dev->GetImmediateContext(&context);

	UINT val = 0;
	ID3D11Buffer * vbNull = nullptr;

	context->IASetVertexBuffers(0,1,&vbNull,&val,&val);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	context->Draw(3,0);
}

void FullScreenQuad::Destroy()
{
	vs.Delete();
}

void FullScreenQuad::SetVS(const char * code)
{
	vs.Get()->LoadFromString(code,strlen(code),"main",nullptr);
}

void FullScreenQuad::BindVS()
{
	vs.Get()->Bind();
}

void FullScreenQuad::UnbindVS()
{
	vs.Get()->Unbind();
}

void FullScreenQuad::SetDevice(ID3D11Device * device)
{
	dev = device;
}


