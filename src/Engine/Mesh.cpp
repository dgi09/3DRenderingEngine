#include "Mesh.h"

void Mesh::Draw()
{
	ID3D11DeviceContext * context = GetContext();
	unsigned int offset = 0;
	context->IASetVertexBuffers(0,1,&vertexBuffer,&stride,&offset);
	context->IASetPrimitiveTopology(topology);

	context->Draw(numberOfVerts,0);
}

void Mesh::InitVertexBuffer(unsigned int dataSize, unsigned int stride,void * data)
{

	D3D11_BUFFER_DESC desc;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.ByteWidth = dataSize;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.Usage = D3D11_USAGE_DYNAMIC;

	D3D11_SUBRESOURCE_DATA d;
	d.pSysMem = data;

	numberOfVerts = dataSize/stride;
	this->stride = stride;
	GetDevice()->CreateBuffer(&desc,&d,&vertexBuffer);
}

void Mesh::InitIndexBuffer(unsigned int numberIndecies,unsigned int * data)
{
	D3D11_BUFFER_DESC desc;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.ByteWidth = numberIndecies * 4;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA d;
	d.pSysMem = data;

	this->numberOfIndecies = numberIndecies;
	GetDevice()->CreateBuffer(&desc,&d,&indexBuffer);
}

void Mesh::DrawIndexed()
{
	ID3D11DeviceContext * context = GetContext();
	unsigned int offset = 0;
	context->IASetVertexBuffers(0,1,&vertexBuffer,&stride,&offset);
	context->IASetIndexBuffer(indexBuffer,DXGI_FORMAT_R32_UINT,0);
	context->IASetPrimitiveTopology(topology);

	context->DrawIndexed(numberOfIndecies,0,0);
}

int Mesh::GetNumberOfVerts()
{
	return numberOfVerts;
}

void * Mesh::LockVerts()
{
	D3D11_MAPPED_SUBRESOURCE  sub;
	ZeroMemory(&sub,sizeof(D3D11_MAPPED_SUBRESOURCE));
	HRESULT res = GetContext()->Map(vertexBuffer,0,D3D11_MAP_WRITE_DISCARD,0,&sub);
	return sub.pData;
	
}

void Mesh::UnlockVerts()
{
	GetContext()->Unmap(vertexBuffer,0);
}

void Mesh::Init()
{
	vertexBuffer = nullptr;
	indexBuffer = nullptr;
	numberOfVerts = 0;
	numberOfIndecies = 0;
	SetPrimitveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}

void Mesh::Destroy()
{
	if(vertexBuffer != nullptr)
		vertexBuffer->Release();

	if(indexBuffer != nullptr)
		indexBuffer->Release();
}

void Mesh::InitPositionBuffer(Vector3 * buffer)
{

	//to do
	memcpy(positionsBuffer,buffer,MAX_VERTS * sizeof(Vector3));
}

Vector3 * Mesh::GetPoistions()
{
	return positionsBuffer;
	//to do 
}

void Mesh::DrawInstanced(unsigned int numberOfInstanes)
{
	ID3D11DeviceContext * context = GetContext();

	unsigned int offset = 0;
	context->IASetVertexBuffers(0,1,&vertexBuffer,&stride,&offset);
	context->IASetPrimitiveTopology(topology);

	context->DrawInstanced(numberOfVerts,numberOfInstanes,0,0);
}

void Mesh::SetPrimitveTopology(D3D11_PRIMITIVE_TOPOLOGY topology)
{
	this->topology = topology;
}
