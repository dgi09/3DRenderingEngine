#pragma once
#include "Common.h"
#include <d3d11.h>

class EXPORT DeviceDependable
{
	ID3D11Device *device;
	ID3D11DeviceContext * context;
public:
	void SetDevice(ID3D11Device * device);

protected:
	ID3D11Device * GetDevice();
	ID3D11DeviceContext * GetContext();

};

