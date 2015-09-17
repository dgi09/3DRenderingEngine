#pragma once

#include "Common.h"
#include <d3d11.h>

struct EXPORT LayoutDescription
{
	D3D11_INPUT_ELEMENT_DESC * elements;
	unsigned int numberOfElements;
};