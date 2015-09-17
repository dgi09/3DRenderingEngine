#include "Positionable.h"

Positionable::Positionable()
{
	position.x = 0;
	position.y = 0;
	position.z = 0;
	isPositionChanged = true;
}

void Positionable::SetPosition(Vector3 pos)
{
	SetPosition(pos.x,pos.y,pos.z);
}

void Positionable::SetPosition(float x,float y,float z)
{
	SetPosX(x);
	SetPosY(y);
	SetPosZ(z);
}

Vector3 Positionable::GetPosition()
{
	return position;
}

float Positionable::GetPosX()
{
	return position.x;
}

float Positionable::GetPosY()
{
	return position.y;
}

float Positionable::GetPosZ()
{
	return position.z;
}

void Positionable::SetPosX(float val)
{
	if(val != position.x)
	{
		position.x = val;
		isPositionChanged = true;
	}
}

void Positionable::SetPosY(float val)
{
	if(val != position.y)
	{
		position.y = val;
		isPositionChanged = true;
	}
}

void Positionable::SetPosZ(float val)
{
	if(val != position.z)
	{
		position.z = val;
		isPositionChanged = true;
	}
}

void Positionable::Move(float offSetX,float offSetY,float offSetZ)
{
	SetPosX(position.x + offSetX);
	SetPosY(position.y + offSetY);
	SetPosZ(position.z + offSetZ);
}
