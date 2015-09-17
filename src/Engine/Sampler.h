#pragma once
#include "Common.h"
#include "DeviceDependable.h"
#include "ShaderType.h"
#include "IDestroyable.h"

enum EXPORT SamplerAddressMode
{
	WRAP,
	CLAMP
};


struct EXPORT SamplerDesc 
{
	SamplerAddressMode addressModeV;
	SamplerAddressMode addressModeU;
	SamplerAddressMode addressModeW;
	float LODBias;
};

class EXPORT Sampler : public DeviceDependable , public IDestroyable
{
	ID3D11SamplerState * sampler;
	
public:

	void Init();
	void Destroy();

	ID3D11SamplerState * GetSamplerPointer();

	void SetUp(SamplerDesc & desc);
	
	void Bind(ShaderType shader);

private:
	D3D11_TEXTURE_ADDRESS_MODE GetDXAdressMode(SamplerAddressMode mode);
};

