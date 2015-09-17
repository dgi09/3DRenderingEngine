#pragma once 
#include "Common.h"

class EXPORT IDestroyable 
{
public:
	virtual void Destroy() = 0;
};