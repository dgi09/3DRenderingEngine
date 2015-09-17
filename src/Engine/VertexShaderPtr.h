#pragma once
#include "Common.h"
#include "HeapPtr.h"
#include "VertexShader.h"


class EXPORT VertexShaderPtr : public HeapPtr<VertexShader>
{
public:
	VertexShaderPtr();
	VertexShaderPtr(unsigned int index);
	VertexShaderPtr(bool isNull);
	VertexShader * Get();
	void Delete();
};

