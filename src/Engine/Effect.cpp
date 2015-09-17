#include "Effect.h"
#include "DeviceDependableFactory.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "IInputLayout.h"

void Effect::LoadVertexShaderFromString(const char * data,unsigned int lenght,IInputLayout * layout)
{
	vShader.Get()->LoadFromString(data,lenght,"main",layout);
}

void Effect::LoadPixelShaderFromString(const char * data,unsigned int lenght)
{
	pShader.Get()->LoadFromString(data,lenght,"main");
}

void Effect::Apply()
{
	vShader.Get()->Bind();
	pShader.Get()->Bind();
}


void Effect::Init(DeviceDependableFactory * factory)
{
	vShader = factory->CreateVertexShader();
	pShader = factory->CreatePixelShader();
}

void Effect::Destroy()
{
	vShader.Delete();
	pShader.Delete();
}