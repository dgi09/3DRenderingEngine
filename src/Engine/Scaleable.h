#pragma once

#include "Common.h"
#include "Vector3.h"

class  EXPORT Scaleable
{

protected:
	Vector3 scale;
	bool isScaleChanged;
public:
	Scaleable(void);

	void SetScale(Vector3 val);
	void SetScale(float x,float y,float z);

	Vector3 GetScale();

	void SetScaleX(float val);
	void SetScaleY(float val);
	void SetScaleZ(float val);

	float GetScaleX();
	float GetScaleY();
	float GetScaleZ();

};

