#pragma once 
#include "Common.h"
#include "HeapPtr.h"
#include "PixelShader.h"

class EXPORT PixelShaderPtr : public HeapPtr<PixelShader> 
{
public:
	PixelShaderPtr();
	PixelShaderPtr(unsigned int index);
	PixelShaderPtr(bool isNull);
	PixelShader * Get();
	void Delete();
};