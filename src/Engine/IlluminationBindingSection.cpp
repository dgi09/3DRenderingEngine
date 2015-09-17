#include "IlluminationBindingSection.h"
#include "Constants.h"
#include "ShaderBindingInfo.h"
#include "DeviceDependableFactory.h"
#include "IlluminationInfo.h"
#include "ConstantBuffer.h"
#include "DLData.h"
#include "PLData.h"


#define  AMBIENT_BUFFER 0
#define  INFO_BUFFER 1
#define  DIR_LIGHTS_BUFFER 2
#define  POINT_LIGHT_BUFFER 3

void IlluminationBindingSection::Init(DeviceDependableFactory * factory)
{

	inPS = true;
	inVS = false;

	
	psShader.buffersCount = 4;
	psShader.buffers[INFO_BUFFER] = ConstantBufferPtr(true);
	psShader.buffers[DIR_LIGHTS_BUFFER] = ConstantBufferPtr(true);
	psShader.buffers[AMBIENT_BUFFER] = ConstantBufferPtr(true);

	psShader.buffers[POINT_LIGHT_BUFFER] = ConstantBufferPtr(true);

}

EffectFunctionality IlluminationBindingSection::GetEffectFunctionality()
{
	return ILLUMINATION;
}

void IlluminationBindingSection::SetIlluminationInfo(ConstantBufferPtr infoBuffer)
{
	psShader.buffers[INFO_BUFFER] = infoBuffer;
}

void IlluminationBindingSection::SetDirLights(ConstantBufferPtr dirLightsBuffer)
{
	psShader.buffers[DIR_LIGHTS_BUFFER] = dirLightsBuffer;
}

void IlluminationBindingSection::SetGlobalAmbient(ConstantBufferPtr globalAmbientBuffer)
{
	psShader.buffers[AMBIENT_BUFFER] = globalAmbientBuffer;
}

void IlluminationBindingSection::SetPointLight(ConstantBufferPtr pointLightsBuffer)
{
	psShader.buffers[POINT_LIGHT_BUFFER] = pointLightsBuffer;
}

void IlluminationBindingSection::Destroy()
{

}
