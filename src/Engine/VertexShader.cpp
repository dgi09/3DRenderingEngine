#include "VertexShader.h"
#include "D3Dcompiler.h"
#include <string>
#include <fstream>
#include <streambuf>
#include "LayoutDescription.h"
#include "IInputLayout.h"


void VertexShader::LoadFromFile(const char * fileName, const char * entryPoint, IInputLayout * layout)
{
	
	std::ifstream t(fileName);
	std::string str((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());
	
	LoadFromString(str.c_str(),str.size(),entryPoint,layout);
	
}

void VertexShader::LoadFromString(const char * data, unsigned int lenght,const char * entryPoint,IInputLayout * layout)
{
	ID3DBlob * blob = nullptr;
	HRESULT res = D3DCompile(data,lenght,nullptr,nullptr,nullptr,entryPoint,"vs_5_0",D3DCOMPILE_ENABLE_STRICTNESS,0,&blob,nullptr);
	GetDevice()->CreateVertexShader(blob->GetBufferPointer(),blob->GetBufferSize(),nullptr,&shader);

	if(layout != nullptr)
	{
		LayoutDescription * desc = layout->GetDescription();
		HRESULT r = GetDevice()->CreateInputLayout(desc->elements,desc->numberOfElements,blob->GetBufferPointer(),blob->GetBufferSize(),&this->layout);
	}
	
	blob->Release();
}

void VertexShader::Bind()
{
	ID3D11DeviceContext * context = GetContext();
	context->VSSetShader(shader,nullptr,0);
	context->IASetInputLayout(layout);
}

void VertexShader::Init()
{
	shader = nullptr;
	layout = nullptr;
}

void VertexShader::Destroy()
{
	if(shader != nullptr)
		shader->Release();


	if(layout != nullptr)
		layout->Release();
}

void VertexShader::Unbind()
{
	ID3D11DeviceContext * context = GetContext();
	ID3D11VertexShader * vsNull = nullptr;

	context->VSSetShader(vsNull,nullptr,0);
}


