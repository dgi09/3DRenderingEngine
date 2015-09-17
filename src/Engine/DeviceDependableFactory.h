#pragma once
#include "Common.h"
#include <d3d11.h>
#include "MeshPtr.h"
#include "VertexShaderPtr.h"
#include "PixelShaderPtr.h"
#include "TexturePtr.h"
#include "SamplerPtr.h"
#include "ConstantBufferPtr.h"
#include "BuffersCollection.h"
#include "SamplersCollection.h"
#include "TexturesCollection.h"
#include "ComputeShaderPtr.h"

class EXPORT DeviceDependableFactory
{
	ID3D11Device * device;
public:
	DeviceDependableFactory(ID3D11Device * device);
	~DeviceDependableFactory(void);

	MeshPtr CreateMesh();
	VertexShaderPtr  CreateVertexShader();
	PixelShaderPtr  CreatePixelShader();
	ComputeShaderPtr CreateComputeShader();
	TexturePtr  CreateTexture();
	SamplerPtr CreateSampler();
	ConstantBufferPtr CreateConstantBuffer();

	BuffersCollection CreateBuffersCollection();
	SamplersCollection CreateSamplersCollection();
	TexturesCollection CreateTexturesCollection();
};

