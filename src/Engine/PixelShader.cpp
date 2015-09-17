#include "PixelShader.h"
#include <string>
#include <fstream>
#include <streambuf>
#include <D3Dcompiler.h>
#include <D3DX11.h>
#include <fstream>


void PixelShader::Bind()
{
	GetContext()->PSSetShader(shader,nullptr,0);
}

void PixelShader::LoadFromFile(const char * fileName , const char * entryPoint)
{
	
	std::ifstream t(fileName);
	std::string str((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	LoadFromString(str.c_str(),str.size(),entryPoint);

	
}

void PixelShader::LoadFromString(const char * data,unsigned int lenght,const char * entryPoint)
{
	ID3DBlob * blob = nullptr;

	HRESULT res = D3DCompile(data,lenght,nullptr,nullptr,nullptr,entryPoint,"ps_5_0",D3DCOMPILE_ENABLE_STRICTNESS,0,&blob,nullptr);

	GetDevice()->CreatePixelShader(blob->GetBufferPointer(),blob->GetBufferSize(),nullptr,&shader);


	blob->Release();
}

void PixelShader::Destroy()
{
	if(shader != nullptr)
		shader->Release();
}

void PixelShader::Init()
{
	shader = nullptr;
}
