#include "Rotateable.h"


Rotateable::Rotateable(void)
{
	rotation.x = 0.0f;
	rotation.y = 0.0f;
	rotation.z = 0.0f;
}

void Rotateable::SetRotation(Vector3 val)
{
	SetRotation(val.x,val.y,val.z);
}

void Rotateable::SetRotation(float x,float y,float z)
{
	SetRotationX(x);

	SetRotationY(y);

	SetRotationZ(z);
}

Vector3 Rotateable::GetRotation()
{
	return rotation;
}

void Rotateable::SetRotationX(float val)
{
	if(val != rotation.x)
	{
		rotation.x = val;
		isRotationChanged = true;
	}
}

void Rotateable::SetRotationY(float val)
{
	if(val != rotation.y)
	{
		rotation.y = val;
		isRotationChanged = true;
	}
}

void Rotateable::SetRotationZ(float val)
{
	if(val != rotation.z)
	{
		rotation.z = val;
		isRotationChanged = true;
	}
}

float Rotateable::GetRotationX()
{
	return rotation.x;
}

float Rotateable::GetRotationY()
{
	return rotation.y;
}

float Rotateable::GetRotationZ()
{
	return rotation.z;
}

void Rotateable::Pitch(float val)
{
	SetRotationX(rotation.x + val);
}

void Rotateable::Yaw(float val)
{
	SetRotationY(rotation.y + val);
}

void Rotateable::Roll(float val)
{
	SetRotationZ(rotation.z + val);
}

