#include "FPSCameraController.h"
#include "Camera.h"
#include <dinput.h>
#include <DirectXMath.h>

using namespace DirectX;


void FPSCameraController::SetCamera(CameraPtr camera)
{
	cam = camera;
	drag = true;
}

void FPSCameraController::Update(InputManager & input)
{
	Camera * camera = cam.Get();

	if(input.KeyPressed(DIK_UPARROW) || input.KeyPressed(DIK_DOWNARROW) || input.KeyPressed(DIK_LEFTARROW)
		|| input.KeyPressed(DIK_RIGHTARROW))
	{

		Vector3 lookNormal  = camera->GetLookDirection().Normalize();
		

		lookNormal = lookNormal * movementSpeed;

		Vector3 rightNormal = camera->GetRightNormal() * movementSpeed;

		Vector3 camPos,camLookAt;
		camPos = camera->GetPosition();
		camLookAt = camera->GetLookAt();

		if(input.KeyPressed(DIK_UPARROW))
		{
			
			camPos = camPos + lookNormal;
			camLookAt = camLookAt + lookNormal;
		}
		if(input.KeyPressed(DIK_DOWNARROW))
		{
			lookNormal = lookNormal * -1;

			camPos = camPos + lookNormal;
			camLookAt = camLookAt + lookNormal;
		}

		if(input.KeyPressed(DIK_LEFTARROW))
		{
			rightNormal = rightNormal * -1;

			camPos = camPos + rightNormal;
			camLookAt = camLookAt + rightNormal;
		}
		if(input.KeyPressed(DIK_RIGHTARROW))
		{
			camPos = camPos + rightNormal;
			camLookAt = camLookAt + rightNormal;
		}

		camera->SetPosition(camPos);
		camera->LookAt(camLookAt);
	}

	if(input.MouseButtonDown(B_RIGHT) && !drag)
	{
		drag = true;
		lastMouseX = input.GetMouseX();
		lastMouseY = input.GetMouseY();
	}
	
	if(!input.MouseButtonDown(B_RIGHT))
	{
		drag = false;
	}
	

	if(drag && input.MouseMove())
	{
		int offSetX = input.GetMouseX() - lastMouseX;
		int offSetY = input.GetMouseY() - lastMouseY;

		Vector3 lat = camera->GetLookDirection();
		Vector3 camPos = camera->GetPosition();
		Vector3 rightN = camera->GetRightNormal();
		Vector3 upN = camera->GetUpNormal();

		XMVECTOR lookAt = XMLoadFloat3((XMFLOAT3*)&lat);
		XMVECTOR upV = XMLoadFloat3((XMFLOAT3*)&upN);
		XMVECTOR right = XMLoadFloat3((XMFLOAT3*)&rightN);

		XMMATRIX rotateX = XMMatrixIdentity();
		XMMATRIX rotateY = XMMatrixIdentity();

		if(offSetX != 0)
			rotateX = XMMatrixRotationAxis(upV,XMConvertToRadians((float)offSetX * 0.4f));
		if(offSetY != 0)
			rotateY = XMMatrixRotationAxis(right,XMConvertToRadians((float)offSetY * 0.4f));

		XMVECTOR result = XMVector3Transform(lookAt,rotateX * rotateY);

		Vector3 res;
		XMStoreFloat3((XMFLOAT3*)&res,result);

		camera->LookAt(camPos + res);

		lastMouseX = input.GetMouseX();
		lastMouseY = input.GetMouseY();
		
	}
	
}

void FPSCameraController::SetMovementSpeed(float speed)
{
	movementSpeed = speed;
}
