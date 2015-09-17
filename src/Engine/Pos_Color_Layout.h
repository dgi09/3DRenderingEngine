#pragma once 
#include "Common.h"
#include "IInputLayout.h"

class EXPORT Pos_Color_Layout : public IInputLayout
{
public:
	virtual LayoutDescription * GetDescription();

};