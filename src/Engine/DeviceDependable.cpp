#include "DeviceDependable.h"


ID3D11Device * DeviceDependable::GetDevice()
{
	return device;
}

ID3D11DeviceContext * DeviceDependable::GetContext()
{
	if(context == nullptr)
	{
		device->GetImmediateContext(&context);
	}

	return context;
}

void DeviceDependable::SetDevice(ID3D11Device * device)
{
	this->device = device;
	this->context = nullptr;
}
