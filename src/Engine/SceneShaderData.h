#pragma once 
#include "Common.h"
#include "ConstantBufferPtr.h"
#include "Vector4.h"

class EXPORT DeviceDependableFactory;
struct EXPORT CameraData;
class EXPORT IlluminationInfo;
struct EXPORT DLData;
class EXPORT PLData;

class EXPORT SceneShaderData
{
	ConstantBufferPtr cameraPtr;
	ConstantBufferPtr globalAmbiantPtr;
	ConstantBufferPtr illuminationInfoPtr;
	ConstantBufferPtr directionLightsPtr;
	ConstantBufferPtr pointLightsPtr;

public:
	

	void Destroy();
	void Init(DeviceDependableFactory * factory);

	void FillCameraBuffer(CameraData * camData);
	ConstantBufferPtr GetCameraBuffer();

	void FillGlobalAmbientBuffer(Vector4 & globalAmbient);
	ConstantBufferPtr GetGlbobalAmbientBuffer();

	void FillIlluminationInfoBuffer(IlluminationInfo * info);
	ConstantBufferPtr GetIlluminationInfoBuffer();

	void FillDirectionLightsBuffer(DLData * data);
	ConstantBufferPtr GetDirectionLightsBuffer();

	void FillPointLightsBuffer(PLData * data);
	ConstantBufferPtr GetPointLightsBuffer();

};
