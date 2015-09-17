#pragma once
#include "DeviceDependable.h"
#include "IDestroyable.h"

#include <d3d11.h>


class EXPORT IInputLayout;

class EXPORT VertexShader :public DeviceDependable , public IDestroyable
{
	ID3D11VertexShader * shader;
	ID3D11InputLayout * layout;
public:
	void LoadFromFile(const char * fileName, const char * entryPoint, IInputLayout * layout);

	void LoadFromString(const char * data, unsigned int lenght,const char * entryPoint,IInputLayout * layout);
	void Bind();
	void Unbind();

	void Init();
	void Destroy();

};

