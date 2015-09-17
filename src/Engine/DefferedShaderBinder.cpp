#include "DefferedShaderBinder.h"

void DefferedShaderBinder::Bind()
{
	buffers[0] = gaBuffer.Get()->GetBufferPointer();
	buffers[1] = iiBuffer.Get()->GetBufferPointer();
	buffers[2] = dlBuffer.Get()->GetBufferPointer();
	buffers[3] = plBuffer.Get()->GetBufferPointer();
	buffers[4] = invViewProjBuffer.Get()->GetBufferPointer();


	GetContext()->PSSetConstantBuffers(0,5,buffers);
}

void DefferedShaderBinder::SetGlobalAmbientBuffer(ConstantBufferPtr buffer)
{
	gaBuffer = buffer;
}

void DefferedShaderBinder::SetIlluminationInfoBuffer(ConstantBufferPtr buffer)
{
	iiBuffer = buffer;
}

void DefferedShaderBinder::SetDirLightsBuffer(ConstantBufferPtr buffer)
{
	dlBuffer = buffer;
}

void DefferedShaderBinder::SetPointLightBuffer(ConstantBufferPtr buffer)
{
	plBuffer = buffer;
}

void DefferedShaderBinder::SetWorldPosRecBuffer(ConstantBufferPtr buffer)
{
	invViewProjBuffer = buffer;
}
