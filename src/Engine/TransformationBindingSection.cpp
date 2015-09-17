#include "TransformationBindingSection.h"
#include "EffectFunctionality.h"
#include "DeviceDependableFactory.h"

#include <DirectXMath.h>

EffectFunctionality TransformationBindingSection::GetEffectFunctionality()
{
	return TRANSFORMATION;
}

void TransformationBindingSection::Init(DeviceDependableFactory * factory)
{

	inPS = false;
	inVS = true;

	vsShader.buffersCount = 2;

	//first buffer is transformation  , second buffer is camera data

	
	vsShader.buffers[0] = ConstantBufferPtr(true);
	vsShader.buffers[1] = ConstantBufferPtr(true);
}

void TransformationBindingSection::SetWorldMatrix(ConstantBufferPtr matrixBuffer)
{
	vsShader.buffers[0] = matrixBuffer;

}

void TransformationBindingSection::SetCameraData(ConstantBufferPtr buffer)
{
	vsShader.buffers[1] = buffer;
}

void TransformationBindingSection::Destroy()
{
	
}
