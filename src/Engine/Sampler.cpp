#include "Sampler.h"

ID3D11SamplerState * Sampler::GetSamplerPointer()
{
	return sampler;
}


void Sampler::Bind(ShaderType shader)
{
	if(sampler != nullptr)
	{
		if(shader == VERTEX)	
			GetContext()->VSSetSamplers(0,1,&sampler);
		else 
			GetContext()->PSSetSamplers(0,1,&sampler);
	}
}

void Sampler::SetUp(SamplerDesc & desc)
{
	D3D11_SAMPLER_DESC sdesc;
	ZeroMemory(&sdesc,sizeof(D3D11_SAMPLER_DESC));
	sdesc.AddressU = GetDXAdressMode(desc.addressModeU);
	sdesc.AddressV = GetDXAdressMode(desc.addressModeV);
	sdesc.AddressW = GetDXAdressMode(desc.addressModeW);
	sdesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sdesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sdesc.MipLODBias = desc.LODBias;
	sdesc.MaxAnisotropy = 1.0f;
	sdesc.MinLOD = 0.0f;
	sdesc.MaxLOD = D3D11_FLOAT32_MAX;

	GetDevice()->CreateSamplerState(&sdesc,&sampler);
}

D3D11_TEXTURE_ADDRESS_MODE Sampler::GetDXAdressMode(SamplerAddressMode mode)
{
	if(mode == CLAMP)
		return D3D11_TEXTURE_ADDRESS_CLAMP;
	else return D3D11_TEXTURE_ADDRESS_WRAP;
}

void Sampler::Init()
{
	sampler = nullptr;
}

void Sampler::Destroy()
{
	if(sampler != nullptr)
		sampler->Release();
}
