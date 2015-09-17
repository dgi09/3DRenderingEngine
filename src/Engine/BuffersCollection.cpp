#include "BuffersCollection.h"
#include "ConstantBuffer.h"

void BuffersCollection::Bind(ShaderType shader)
{
	if(size > 0)
	{
		if(shader == VERTEX)
			GetContext()->VSSetConstantBuffers(0,size,buffers);
		else 
			GetContext()->PSSetConstantBuffers(0,size,buffers);
	}
}


void BuffersCollection::Set(unsigned int index,ConstantBuffer * buffer)
{
	if(index < size && index >= 0)
	{
		buffers[index] = buffer->GetBufferPointer();
	}
}


BuffersCollection::BuffersCollection()
{
	size = 0;
}

void BuffersCollection::SetSize(unsigned int size)
{
	if(size <= MAX_BUFFERS_IN_COLLECTION)
		this->size = size;
}

void BuffersCollection::Clear()
{
	for(int i = 0;i < MAX_BUFFERS_IN_COLLECTION;i++)
	{
		buffers[i] = nullptr;
	}
}
