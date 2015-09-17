#include "SceneShaderData.h"
#include "DeviceDependableFactory.h"
#include "CameraData.h"
#include "IlluminationInfo.h"
#include "PLData.h"
#include "DLData.h"
#include "Constants.h"
#include "ConstantBuffer.h"

void SceneShaderData::Destroy()
{
	cameraPtr.Delete();
	globalAmbiantPtr.Delete();
	illuminationInfoPtr.Delete();
	directionLightsPtr.Delete();
	pointLightsPtr.Delete();
}

void SceneShaderData::Init(DeviceDependableFactory * factory)
{
	cameraPtr = factory->CreateConstantBuffer();
	globalAmbiantPtr = factory->CreateConstantBuffer();
	illuminationInfoPtr = factory->CreateConstantBuffer();
	directionLightsPtr = factory->CreateConstantBuffer();
	pointLightsPtr = factory->CreateConstantBuffer();

	ConstantBuffer * buffer = cameraPtr.Get();
	buffer->InitBuffer(sizeof(CameraData));

	buffer = globalAmbiantPtr.Get();
	buffer->InitBuffer(sizeof(Vector4));

	buffer = illuminationInfoPtr.Get();
	buffer->InitBuffer(sizeof(IlluminationInfo));

	buffer = directionLightsPtr.Get();
	buffer->InitBuffer(sizeof(DLData) * MAX_DIRECTIONAL_LIGHTS);

	buffer = pointLightsPtr.Get();
	buffer->InitBuffer(sizeof(PLData) * MAX_POINT_LIGHTS);
}

void SceneShaderData::FillCameraBuffer(CameraData * camData)
{
	cameraPtr.Get()->FillBuffer(camData);
}

ConstantBufferPtr SceneShaderData::GetCameraBuffer()
{
	return cameraPtr;
}

void SceneShaderData::FillGlobalAmbientBuffer(Vector4 & globalAmbient)
{
	globalAmbiantPtr.Get()->FillBuffer(&globalAmbient);
}

ConstantBufferPtr SceneShaderData::GetGlbobalAmbientBuffer()
{
	return globalAmbiantPtr;
}

void SceneShaderData::FillIlluminationInfoBuffer(IlluminationInfo * info)
{
	illuminationInfoPtr.Get()->FillBuffer(info);
}

ConstantBufferPtr SceneShaderData::GetIlluminationInfoBuffer()
{
	return illuminationInfoPtr;
}

void SceneShaderData::FillDirectionLightsBuffer(DLData * data)
{
	directionLightsPtr.Get()->FillBuffer(data);
}

ConstantBufferPtr SceneShaderData::GetDirectionLightsBuffer()
{
	return directionLightsPtr;
}

void SceneShaderData::FillPointLightsBuffer(PLData * data)
{
	pointLightsPtr.Get()->FillBuffer(data);
}

ConstantBufferPtr SceneShaderData::GetPointLightsBuffer()
{
	return pointLightsPtr;
}
