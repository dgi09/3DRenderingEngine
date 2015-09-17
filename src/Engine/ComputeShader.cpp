#include "ComputeShader.h"
#include <string>
#include <fstream>
#include <streambuf>
#include <D3Dcompiler.h>
#include <D3DX11.h>
#include <fstream>
#include "FileLoader.h"


void ComputeShader::LoadFromFile(const char * fileName , const char * entryPoint)
{	
	std::string code = FileLoader::GetAllText(fileName);
	LoadFromString(code.c_str(),entryPoint);
}

void ComputeShader::Destroy()
{
	if(shader != nullptr)
		shader->Release();
}

void ComputeShader::Bind()
{
	GetContext()->CSSetShader(shader,nullptr,0);
}

void ComputeShader::Run(unsigned int x,unsigned int y,unsigned int z)
{
	GetContext()->Dispatch(x,y,z);
}

void ComputeShader::Unbind()
{
	GetContext()->CSSetShader(nullptr,nullptr,0);
}

void ComputeShader::Init()
{
	shader = nullptr;
}

void ComputeShader::LoadFromString(const char * code,const char * entryPoint)
{
	ID3DBlob * blob = nullptr;

	HRESULT res = D3DCompile(code,strlen(code),nullptr,nullptr,nullptr,entryPoint,"cs_5_0",0,0,&blob,nullptr);

	GetDevice()->CreateComputeShader(blob->GetBufferPointer(),blob->GetBufferSize(),nullptr,&shader);

	blob->Release();
}
