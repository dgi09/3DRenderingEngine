#pragma once
#include "Common.h"
#include "Vector3.h"

class EXPORT Rotateable
{
protected:
	Vector3 rotation;
	bool isRotationChanged;
public:
	Rotateable(void);
	
	void SetRotation(Vector3 val);
	void SetRotation(float x,float y,float z);

	Vector3 GetRotation();

	void SetRotationX(float val);
	void SetRotationY(float val);
	void SetRotationZ(float val);

	float GetRotationX();
	float GetRotationY();
	float GetRotationZ();

	void Pitch(float val);
	void Yaw(float val);
	void Roll(float val);

};

