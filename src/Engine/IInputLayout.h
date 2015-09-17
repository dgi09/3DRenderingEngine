#pragma once 
#include "Common.h"

struct EXPORT LayoutDescription;

class EXPORT IInputLayout
{
protected:
	LayoutDescription * desc;
public:
	IInputLayout();
	virtual ~IInputLayout();
	virtual LayoutDescription * GetDescription() = 0;
};