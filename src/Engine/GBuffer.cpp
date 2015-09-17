#include "GBuffer.h"
#include "Texture.h"
#include "Sampler.h"

void GBuffer::Init(int windowW, int windowH, DeviceDependableFactory * factory)
{
	Texture * t;

	textures[DIFFUSE] = factory->CreateTexture();
	t = textures[DIFFUSE].Get();
	t->InitTexture(windowW,windowH,RENDER_TARGET,DXGI_FORMAT_R8G8B8A8_UNORM,-1);

	textures[NORMAL] = factory->CreateTexture();
	t = textures[NORMAL].Get();
	t->InitTexture(windowW,windowH,RENDER_TARGET,DXGI_FORMAT_R11G11B10_FLOAT);

	textures[SPEC_EMMISIVE] = factory->CreateTexture();
	t = textures[SPEC_EMMISIVE].Get();
	t->InitTexture(windowW,windowH,RENDER_TARGET,DXGI_FORMAT_R8G8B8A8_UNORM);



	textures[DEPTH] = factory->CreateTexture();
	t = textures[DEPTH].Get();
	t->InitTexture(windowW,windowH,DEPTH_BUFFER,DXGI_FORMAT_R24G8_TYPELESS);

}

void GBuffer::Clear(Color diffuseColor)
{
	float color[4] = {0.0f,0.0f,0.0f,1.0f};
	GetContext()->ClearRenderTargetView(textures[DIFFUSE].Get()->GetRenderTargetPtr(),color);

	GetContext()->ClearDepthStencilView(textures[DEPTH].Get()->GetDepthBufferPtr(),D3D11_CLEAR_DEPTH,1.0f,0.0f);

}

void GBuffer::BindToOM()
{
	for(int i = 0;i < 3;i++)
	{
		views[i] = textures[i].Get()->GetRenderTargetPtr();
	}

	GetContext()->OMSetRenderTargets(3,views,textures[DEPTH].Get()->GetDepthBufferPtr());
}

void GBuffer::Destroy()
{
	for(int i = 0;i < 4;i++)
	{
		textures[i].Get()->Destroy();
	}
}

void GBuffer::BindToPS()
{
	ID3D11ShaderResourceView * SRVs[4];
	for(int i = 0;i < 4;i++)
	{
		SRVs[i] = textures[i].Get()->GetShaderResourcePointer();
	}

	GetContext()->PSSetShaderResources(0,4,SRVs);

}

TexturePtr GBuffer::GetDiffuseTexture()
{
	return textures[DIFFUSE];
}

void GBuffer::UnbindFromPS()
{
	ID3D11ShaderResourceView * srvNull[4] = {nullptr,nullptr,nullptr,nullptr};
	GetContext()->PSSetShaderResources(0,4,srvNull);
}

TexturePtr GBuffer::GetDepthTexture()
{
	return textures[DEPTH];
}
