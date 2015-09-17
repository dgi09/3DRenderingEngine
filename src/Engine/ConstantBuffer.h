#pragma once
#include "Common.h"
#include "DeviceDependable.h"
#include "IDestroyable.h"

class EXPORT ConstantBuffer : public DeviceDependable , public IDestroyable
{
	ID3D11Buffer * buffer;
	unsigned int lenght;
public:

	void InitBuffer(unsigned int lenght);
	void InitBuffer(unsigned int lenght,void * data);
	void FillBuffer(void * data);
	void FillBuffer(void * data,unsigned int size);

	ID3D11Buffer * GetBufferPointer();

	void Init();
	void Destroy();
};

