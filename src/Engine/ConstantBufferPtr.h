#pragma once
#include "Common.h"
#include "HeapPtr.h"
#include "ConstantBuffer.h"


class EXPORT ConstantBufferPtr : public HeapPtr<ConstantBuffer>
{
public:
	ConstantBufferPtr();
	ConstantBufferPtr(unsigned int index);
	ConstantBufferPtr(bool isNull);
	ConstantBuffer * Get();
	void Delete();
};

