#pragma once 
#include "Common.h"

class EXPORT Color
{
public:
	float r,g,b,a;
	Color(float r,float g,float b,float a);
	Color();
	static Color Black();
	static Color White();
	static Color Red();
	static Color Blue();
};