#pragma once
#include "Common.h"
#include "Vector4.h"
#include <DirectXMath.h>
#include "BoundingSphere.h"

class EXPORT Frustrum
{
	Vector4 planes[6];
public:
	void BuildFromViewProjMatrix(DirectX::XMFLOAT4X4 & mat);
	bool IsSphereIn(BoundingSphere & sphere);
};

