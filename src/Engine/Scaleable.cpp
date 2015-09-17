#include "Scaleable.h"

Scaleable::Scaleable(void)
{
	scale.x = 1.0f;
	scale.y = 1.0f;
	scale.z = 1.0f;
	isScaleChanged = true;
}

void Scaleable::SetScale(Vector3 val)
{
	SetScale(val.x,val.y,val.z);
}

void Scaleable::SetScale(float x,float y,float z)
{
	SetScaleX(x);
	SetScaleY(y);
	SetScaleZ(z);
}

Vector3 Scaleable::GetScale()
{
	return scale;
}

void Scaleable::SetScaleX(float val)
{
	if(val != scale.x)
	{
		scale.x = val;
		isScaleChanged = true;
	}
}

void Scaleable::SetScaleY(float val)
{
	if(val != scale.y)
	{
		scale.y = val;
		isScaleChanged = true;
	}
}

void Scaleable::SetScaleZ(float val)
{
	if(val != scale.z)
	{
		scale.z = val;
		isScaleChanged = true;
	}
}

float Scaleable::GetScaleX()
{
	return scale.x;
}

float Scaleable::GetScaleY()
{
	return scale.y;
}

float Scaleable::GetScaleZ()
{
	return scale.z;
}


