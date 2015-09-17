#include "DeviceDependableFactory.h"
#include "Mesh.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Texture.h"
#include "Sampler.h"
#include "ConstantBuffer.h"
#include "BuffersCollection.h"
#include "SamplersCollection.h"
#include "TexturesCollection.h"
#include "Heap.h"

DeviceDependableFactory::DeviceDependableFactory(ID3D11Device * device)
{
	this->device = device;
}


DeviceDependableFactory::~DeviceDependableFactory(void)
{
	device = nullptr;
}

MeshPtr DeviceDependableFactory::CreateMesh()
{
	MeshPtr ptr(Heap::GetPtr()->Meshes.New());
	Mesh * m = ptr.Get();
	m->Init();
	m->SetDevice(device);

	return ptr;
}

VertexShaderPtr DeviceDependableFactory::CreateVertexShader()
{
	VertexShaderPtr ptr(Heap::GetPtr()->VertexShaders.New());
	
	VertexShader * shader = ptr.Get();

	shader->Init();
	shader->SetDevice(device);

	return ptr;
}

PixelShaderPtr DeviceDependableFactory::CreatePixelShader()
{
	
	PixelShaderPtr ptr(Heap::GetPtr()->PixelShaders.New());

	PixelShader * ps = ptr.Get();
	ps->Init();
	ps->SetDevice(device);

	return ptr;
}

TexturePtr DeviceDependableFactory::CreateTexture()
{
	TexturePtr ptr(Heap::GetPtr()->Textures.New());
	Texture * t = ptr.Get();
	t->Init();
	t->SetDevice(device);
	return ptr;
}

SamplerPtr DeviceDependableFactory::CreateSampler()
{
	SamplerPtr ptr(Heap::GetPtr()->Samplers.New());
	Sampler * s = ptr.Get();
	s->Init();
	s->SetDevice(device);
	
	return ptr;
}

ConstantBufferPtr DeviceDependableFactory::CreateConstantBuffer()
{
	ConstantBufferPtr ptr(Heap::GetPtr()->ConstantBuffers.New());
	ConstantBuffer * cb = ptr.Get();
	cb->Init();
	cb->SetDevice(device);
	return ptr;
}

BuffersCollection DeviceDependableFactory::CreateBuffersCollection()
{
	BuffersCollection buffers;
	buffers.SetDevice(device);
	return buffers;
}

SamplersCollection DeviceDependableFactory::CreateSamplersCollection()
{
	SamplersCollection sc;
	sc.SetDevice(device);
	return sc;
}

TexturesCollection DeviceDependableFactory::CreateTexturesCollection()
{
	
	TexturesCollection tc;
	tc.SetDevice(device);
	return tc;
}

ComputeShaderPtr DeviceDependableFactory::CreateComputeShader()
{
	ComputeShaderPtr ptr(Heap::GetPtr()->ComputeShaders.New());
	ComputeShader * cs = ptr.Get();
	cs->Init();
	cs->SetDevice(device);

	return ptr;
}
