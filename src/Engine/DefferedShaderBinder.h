#pragma once 
#include "Common.h"
#include "DeviceDependable.h"
#include "DeviceDependableFactory.h"
#include "ConstantBufferPtr.h"
#include "SamplerPtr.h"

class EXPORT DefferedShaderBinder : public DeviceDependable
{
	ConstantBufferPtr gaBuffer;
	ConstantBufferPtr iiBuffer;
	ConstantBufferPtr dlBuffer;
	ConstantBufferPtr plBuffer;
	ConstantBufferPtr invViewProjBuffer;

	ID3D11Buffer * buffers[5];
public:
	void Bind();

	void SetGlobalAmbientBuffer(ConstantBufferPtr buffer);
	void SetIlluminationInfoBuffer(ConstantBufferPtr buffer);
	void SetDirLightsBuffer(ConstantBufferPtr buffer);
	void SetPointLightBuffer(ConstantBufferPtr buffer);
	void SetWorldPosRecBuffer(ConstantBufferPtr buffer);
};