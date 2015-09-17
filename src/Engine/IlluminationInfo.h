#pragma once 
#include "Common.h"
#include "Vector3.h"

class EXPORT IlluminationInfo
{
public:
	Vector3 camPosition;
	unsigned int numberOfDirectionalLights;
	unsigned int numberOfPointLights;
	Vector3 padding;
};