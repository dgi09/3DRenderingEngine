#include "EntityShaderData.h"
#include "DeviceDependableFactory.h"
#include "ConstantBuffer.h"

void EntityShaderData::Init(DeviceDependableFactory * factory)
{
	worldMatrixBuffer = factory->CreateConstantBuffer();
	ConstantBuffer * buffer = worldMatrixBuffer.Get();
	buffer->InitBuffer(sizeof(DirectX::XMFLOAT4X4));
}

void EntityShaderData::FillWorldMatrixBuffer(DirectX::XMFLOAT4X4 & mat)
{
	worldMatrixBuffer.Get()->FillBuffer((void*)&mat);
}

ConstantBufferPtr EntityShaderData::GetWorldMatrixBuffer()
{
	return worldMatrixBuffer;
}

void EntityShaderData::Destroy()
{
	worldMatrixBuffer.Delete();
	
}
