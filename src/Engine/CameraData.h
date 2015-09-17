#pragma once
#include "Common.h"
#include <DirectXMath.h>

struct EXPORT CameraData
{
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 projection;
};