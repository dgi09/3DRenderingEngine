#pragma once 
#include "Common.h"

class EXPORT Vector3
{
public:
	float x;
	float y;
	float z;

	bool operator!=(Vector3 & vec);
	bool operator==(Vector3 & vec);
	Vector3 operator-(Vector3 & vec);
	Vector3 operator+(Vector3 & vec);
	Vector3 operator*(float val);

	Vector3(float x,float y,float z);
	Vector3();

	Vector3 Normalize();
	float Lenght();
};