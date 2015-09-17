#include "Texture.h"
#include <stdio.h>
#include <D3DX11.h>


void Texture::LoadFromFile(const char * fileName)
{
	D3DX11CreateTextureFromFileA(GetDevice(),fileName,nullptr,nullptr,(ID3D11Resource**)&texture,nullptr);
	fromFile = true;
}

ID3D11ShaderResourceView * Texture::GetShaderResourcePointer()
{
	if(shaderResource == nullptr)
	{
		CreateResourceView();
	}

	return shaderResource;
}

void Texture::Bind(ShaderType shaderType)
{
	if(shaderResource == nullptr)
	{
		CreateResourceView();
	}

	if(shaderType == VERTEX)
		GetContext()->VSSetShaderResources(0,1,&shaderResource);
	else 
		GetContext()->PSSetShaderResources(0,1,&shaderResource);
}

void Texture::CreateResourceView()
{
	if(texture != nullptr)
	{
		if(!fromFile)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC sr_desc;
			if(usage == DEPTH_BUFFER)
				sr_desc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
			else sr_desc.Format = format;


			sr_desc.ViewDimension  = D3D11_SRV_DIMENSION_TEXTURE2D;
			sr_desc.Texture2D.MostDetailedMip = 0;
			sr_desc.Texture2D.MipLevels  = -1;

			GetDevice()->CreateShaderResourceView(texture,&sr_desc,&shaderResource);
		}
		else 
			GetDevice()->CreateShaderResourceView(texture,nullptr,&shaderResource);
		
	}
}

void Texture::Init()
{
	fromFile = false;
	texture = nullptr;
	shaderResource = nullptr;
	target = nullptr;
	depthView = nullptr;
	uav = nullptr;
}

void Texture::Destroy()
{
	if(shaderResource != nullptr)
		shaderResource->Release();

	if(target != nullptr)
		target->Release();

	if(texture != nullptr)
		texture->Release();

	if(depthView != nullptr)
		depthView->Release();

	if(uav != nullptr)
		uav->Release();
}

void Texture::InitTexture(unsigned int width,unsigned int height , TextureUsage usage ,DXGI_FORMAT format,int MipLevels)
{
	D3D11_TEXTURE2D_DESC textureDesc;
	
	// Initialize the render target texture description.
	ZeroMemory(&textureDesc, sizeof(textureDesc));

	if(MipLevels == -1)
	{
		UINT numLevels = 1;
		UINT w = width;
		UINT h = height;

		while(w > 1 && h > 1)
		{
			w = max(w / 2, 1);
			h = max(h / 2, 1);
			++numLevels;
		}

		MipLevels = numLevels;
	}


	textureDesc.Width = width;
	textureDesc.Height = height;
	textureDesc.MipLevels = MipLevels;
	textureDesc.ArraySize = 1;
	textureDesc.Format = format;

	this->format = format;
	this->usage = usage;

	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | (int)usage;
	textureDesc.CPUAccessFlags = 0;

	

	if(MipLevels != 1)
		textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;
	else textureDesc.MiscFlags = 0;

	HRESULT res = GetDevice()->CreateTexture2D(&textureDesc,nullptr,&texture);
}

ID3D11RenderTargetView * Texture::GetRenderTargetPtr()
{
	if(target == nullptr)
		CreateTargetView();

	return target;
}

void Texture::CreateTargetView()
{
	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	ZeroMemory(&renderTargetViewDesc,sizeof(D3D11_RENDER_TARGET_VIEW_DESC));

	renderTargetViewDesc.Format = format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	HRESULT res = GetDevice()->CreateRenderTargetView(texture,&renderTargetViewDesc,&target);
}

ID3D11DepthStencilView * Texture::GetDepthBufferPtr()
{
	if(depthView == nullptr)
		CreateDepthBuffer();

	return depthView;
}

ID3D11UnorderedAccessView * Texture::GetUnorderedView()
{
	if(uav == nullptr)
		CreateUnorderedView();
	return uav;
}

void Texture::CreateDepthBuffer()
{
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory( &descDSV, sizeof(descDSV) );
	descDSV.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;

	GetDevice()->CreateDepthStencilView(texture,&descDSV,&depthView);

}



void Texture::GenerateMips()
{
	GetContext()->GenerateMips(GetShaderResourcePointer());
}

void Texture::CreateUnorderedView()
{
	D3D11_UNORDERED_ACCESS_VIEW_DESC desc;
	ZeroMemory(&desc,sizeof(D3D11_UNORDERED_ACCESS_VIEW_DESC));

	desc.Format = format;
	desc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipSlice = 0;

	GetDevice()->CreateUnorderedAccessView(texture,&desc,&uav);
}
