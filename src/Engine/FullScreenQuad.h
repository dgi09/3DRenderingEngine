#pragma once 
#include "Common.h"
#include "VertexShaderPtr.h"

class DeviceDependableFactory;

class FullScreenQuad
{
	static VertexShaderPtr vs;
	static ID3D11Device * dev;
public:

	static void Init(DeviceDependableFactory * factory);
	static void SetVS(const char * code);
	static void SetDevice(ID3D11Device * device);
	static void BindVS();
	static void UnbindVS();
	static void Destroy();
	static void Draw();

};

