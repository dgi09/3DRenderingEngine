#pragma once 

#include "Common.h"
#include "HeapPtr.h"
#include "ComputeShader.h"


class EXPORT ComputeShaderPtr : public HeapPtr<ComputeShader>
{
public:
	ComputeShaderPtr();
	ComputeShaderPtr(unsigned int index);
	ComputeShaderPtr(bool isNull);
	ComputeShader * Get();
	void Delete();
};