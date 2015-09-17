#include "ConstantBuffer.h"

void ConstantBuffer::InitBuffer(unsigned int lenght)
{
	D3D11_BUFFER_DESC desc;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = lenght;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	this->lenght = lenght;

	GetDevice()->CreateBuffer(&desc,nullptr,&buffer);
}

void ConstantBuffer::InitBuffer(unsigned int lenght,void * data)
{

	D3D11_BUFFER_DESC desc;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = lenght;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.Usage = D3D11_USAGE_DYNAMIC;

	D3D11_SUBRESOURCE_DATA sdata;
	sdata.pSysMem = data;

	this->lenght = lenght;
	GetDevice()->CreateBuffer(&desc,&sdata,&buffer);
}

void ConstantBuffer::FillBuffer(void * data)
{
	D3D11_MAPPED_SUBRESOURCE  sub;
	ZeroMemory(&sub,sizeof(D3D11_MAPPED_SUBRESOURCE));
	HRESULT res = GetContext()->Map(buffer,0,D3D11_MAP_WRITE_DISCARD,0,&sub);
	memcpy(sub.pData,data,lenght);
	GetContext()->Unmap(buffer,0);
}

void ConstantBuffer::FillBuffer(void * data,unsigned int size)
{
	D3D11_MAPPED_SUBRESOURCE  sub;
	ZeroMemory(&sub,sizeof(D3D11_MAPPED_SUBRESOURCE));
	HRESULT res = GetContext()->Map(buffer,0,D3D11_MAP_WRITE_DISCARD,0,&sub);
	if(res == S_OK)
	{
		memcpy(sub.pData,data,size);
		GetContext()->Unmap(buffer,0);
	}
	
}

ID3D11Buffer * ConstantBuffer::GetBufferPointer()
{
	return buffer;
}

void ConstantBuffer::Init()
{
	lenght = 0;
	buffer = nullptr;
}

void ConstantBuffer::Destroy()
{
	if(buffer != nullptr)
	{
		buffer->Release();
		buffer = nullptr;
	}
}
