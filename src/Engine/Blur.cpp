#include "Blur.h"
#include "IInputLayout.h"
#include "Pos_TexCoord_Layout.h"
#include "Texture.h"
#include "Color.h"
#include "FullScreenQuad.h"


void Blur::Init(DeviceDependableFactory * factory)
{
	csH = factory->CreateComputeShader();
	csV = factory->CreateComputeShader();
}

void Blur::RunHorizontal(TexturePtr src,TexturePtr dst)
{
	IntRunHorizontal(src.Get()->GetShaderResourcePointer(),dst.Get()->GetUnorderedView());
}

void Blur::RunHorizontal(TexturePtr src,ID3D11UnorderedAccessView * dst)
{
	IntRunHorizontal(src.Get()->GetShaderResourcePointer(),dst);
}

void Blur::SetDevice(ID3D11Device * device)
{
	dev = device;
}

void Blur::IntRunHorizontal(ID3D11ShaderResourceView * src,ID3D11UnorderedAccessView * dest)
{
	ID3D11DeviceContext * context;
	dev->GetImmediateContext(&context);
	
	ID3D11ShaderResourceView * srvNull = nullptr;
	ID3D11UnorderedAccessView * uavNull = nullptr;

	csH.Get()->Bind();

	context->CSSetShaderResources(0,1,&src);
	context->CSSetUnorderedAccessViews(0,1,&dest,nullptr);

	
	csH.Get()->Run(dispatchSizeX,dispatchSizeY,1);
	


	context->CSSetShaderResources(0,1,&srvNull);
	context->CSSetUnorderedAccessViews(0,1,&uavNull,nullptr);
	csH.Get()->Unbind();
}

void Blur::IntRunVertical(ID3D11ShaderResourceView * src,ID3D11UnorderedAccessView * dst)
{
	ID3D11DeviceContext * context;
	dev->GetImmediateContext(&context);

	ID3D11ShaderResourceView * srvNull = nullptr;
	ID3D11UnorderedAccessView * uavNull = nullptr;

	csV.Get()->Bind();

	context->CSSetShaderResources(0,1,&src);
	context->CSSetUnorderedAccessViews(0,1,&dst,nullptr);

	
	csV.Get()->Run(dispatchSizeX,dispatchSizeY,1);
	


	context->CSSetShaderResources(0,1,&srvNull);
	context->CSSetUnorderedAccessViews(0,1,&uavNull,nullptr);
	csV.Get()->Unbind();
}



void Blur::SetHorizonatlBlurEffect(const char * c)
{
	csH.Get()->LoadFromString(c,"main");
}

void Blur::SetVerticalBlurEffect(const char * c)
{
	csV.Get()->LoadFromString(c,"main");
}

void Blur::Destroy()
{
	csV.Delete();
	csH.Delete();

}

void Blur::RunVertical(TexturePtr src,TexturePtr dst)
{
	IntRunVertical(src.Get()->GetShaderResourcePointer(),dst.Get()->GetUnorderedView());
}

void Blur::RunVertical(TexturePtr src,ID3D11UnorderedAccessView * dst)
{
	IntRunVertical(src.Get()->GetShaderResourcePointer(),dst);
}

void Blur::SetSize(unsigned int width,unsigned int height)
{
	if(width % 10 == 0)
		dispatchSizeX = width / 10;
	else dispatchSizeX = width / 10 + (10 - width % 10);

	if(height % 10 == 0)
		dispatchSizeY = height / 10;
	else dispatchSizeY = height / 10 + (10 - height % 10);
}





