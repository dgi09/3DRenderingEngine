#pragma once 
#include "Common.h"
#include "Vector3.h"

class EXPORT Positionable
{
protected:
	Vector3 position;
	bool isPositionChanged;
public:
	Positionable();

	void SetPosition(Vector3 pos);
	void SetPosition(float x,float y,float z);

	Vector3 GetPosition();
	float GetPosX();
	float GetPosY();
	float GetPosZ();

	void SetPosX(float val);
	void SetPosY(float val);
	void SetPosZ(float val);

	void Move(float offSetX,float offSetY,float offSetZ);

};