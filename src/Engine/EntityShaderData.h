#pragma once 
#include "Common.h"
#include "ConstantBufferPtr.h"
#include <DirectXMath.h>
#include "Color.h"


class EXPORT DeviceDependableFactory;

class EXPORT EntityShaderData
{
	ConstantBufferPtr worldMatrixBuffer;

public:

	void Destroy();
	void Init(DeviceDependableFactory * factory);
	void FillWorldMatrixBuffer(DirectX::XMFLOAT4X4 & mat);


	ConstantBufferPtr GetWorldMatrixBuffer();
};
