#pragma once 
#include "Common.h"
#include "PLData.h"
#include <DirectXMath.h>


class EXPORT Scene;

class EXPORT PointLight 
{
	PLData * data;
	bool isChanged;
public:
	void SetPosition(float x,float y,float z);
	void SetPosition(Vector3 position);

	void SetDiffuse(Vector4 diffuse);
	void SetDiffuse(float r,float g,float b,float a);

	void SetRange(float val);

private:
	friend class EXPORT Scene;
	void Init();
	bool IsChanged();
	void ChangeApplied();
	void SetData(PLData * data);
};