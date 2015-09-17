#include "IInputLayout.h"
#include "LayoutDescription.h"

IInputLayout::IInputLayout()
{
	desc = nullptr;
}

IInputLayout::~IInputLayout()
{
	if(desc != nullptr)
	{
		if(desc->elements != nullptr)
			delete desc->elements;
		delete desc;
	}
}
