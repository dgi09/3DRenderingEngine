#pragma once
#include "Common.h"
#include "Vector3.h"
#include "Vector4.h"

struct EXPORT DLData
{
	Vector4 diffuseColor;
	Vector3 direction;
	float padding;
};