#pragma once 
#include "Common.h"
#include "Scene.h"
#include "InputManager.h"

class EXPORT FPSCameraController
{
	CameraPtr cam;

	int lastMouseX;
	int lastMouseY;

	bool drag;

	float movementSpeed;
public:

	void SetCamera(CameraPtr camera);
	void SetMovementSpeed(float speed);

	void Update(InputManager & input);
};
