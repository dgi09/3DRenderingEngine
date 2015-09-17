#include "Camera.h"
#include <DirectXMath.h>

using namespace DirectX;

void Camera::LookAt(float x,float y,float z)
{
	if(x != lookAt.x || y != lookAt.y || z != lookAt.z)
	{
		lookAt.x = x;
		lookAt.y = y;
		lookAt.z = z;

		requireViewMatrixRecalculation = true;
		isChanged = true;
	}
	

}

void Camera::LookAt(Vector3 val)
{
	LookAt(val.x,val.y,val.z);
}

CameraData * Camera::GetData()
{
	SetUpData();	
	return &shaderData;
}

void Camera::SetUpData()
{
	if(isPositionChanged || requireViewMatrixRecalculation)
	{
		
		XMVECTOR eyePos = XMVectorSet(position.x,position.y,position.z,0.0f);
		XMVECTOR look = XMVectorSet(lookAt.x,lookAt.y,lookAt.z,0.0f);
		XMVECTOR up = XMVectorSet(0.0f,1.0f,0.0f,0.0f);
		XMStoreFloat4x4(&shaderData.view,XMMatrixLookAtLH(eyePos,look,up));
		requireViewMatrixRecalculation = false;

		isPositionChanged = false;
		
	}

	if(requirePorjMatrixRecalculation)
	{
		XMStoreFloat4x4(&shaderData.projection,XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(fov),aspectRatio,nearDistance,farDistance));
		requirePorjMatrixRecalculation = false;
	}

}

	
void Camera::SetNearDistance(float val)
{
	if(val != nearDistance)
	{
		nearDistance = val;
		requirePorjMatrixRecalculation = true;
		isChanged = true;
	}
}

void Camera::SetFarDistance(float val)
{
	if(val != farDistance)
	{
		farDistance = val;
		requirePorjMatrixRecalculation = true;
		isChanged = true;
	}
}

void Camera::SetFOV(float val)
{
	if(val != fov)
	{
		fov = val;
		requirePorjMatrixRecalculation = true;
		isChanged = true;
	}
}

void Camera::SetAspectRatio(float val)
{
	if(val != aspectRatio)
	{
		aspectRatio = val;
		requirePorjMatrixRecalculation = true;
		isChanged = true;
	}
}

void Camera::Init()
{
	requireViewMatrixRecalculation = true;
	requirePorjMatrixRecalculation = true;
	isChanged = true;
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 0.0f;

	aspectRatio = 0.0f;
	fov = 45.0f;
	nearDistance = 1.0f;
	farDistance = 100.0f;
}

bool Camera::IsChanged()
{
	return isChanged || isPositionChanged;
}

void Camera::ChangeApplied()
{
	isChanged = false;
}

void Camera::CalcFrustrum()
{
	SetUpData();
	XMMATRIX view = XMLoadFloat4x4(&shaderData.view);
	XMMATRIX proj = XMLoadFloat4x4(&shaderData.projection);
	XMMATRIX viewProj = XMMatrixMultiply(view,proj);
	XMFLOAT4X4 res;
	XMStoreFloat4x4(&res,viewProj);

	frustrum.BuildFromViewProjMatrix(res);
}

Frustrum * Camera::GetFrustrum()
{
	return &frustrum;
}

Vector3 Camera::GetLookDirection()
{
	return lookAt - position;
}

Vector3 Camera::GetLookAt()
{
	return lookAt;
}

void Camera::CalcVectors()
{
	Vector3 lDir = GetLookDirection();
	XMVECTOR lookN = XMVector3Normalize(XMLoadFloat3((XMFLOAT3*)&lDir));
	XMVECTOR upN = XMVector3Normalize(XMVectorSet(0.0f,1.0f,0.0f,1.0f));
	
	XMVECTOR rN = XMVector3Cross(upN,lookN);
	upN = XMVector3Normalize(XMVector3Cross(lookN,rN));

	XMStoreFloat3((XMFLOAT3*)&upNormal,upN);
	XMStoreFloat3((XMFLOAT3*)&rightNormal,rN);
}

Vector3 Camera::GetUpNormal()
{
	return upNormal;
}

Vector3 Camera::GetRightNormal()
{
	return rightNormal;
}

