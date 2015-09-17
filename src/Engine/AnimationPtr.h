#pragma once 
#include "Common.h"
#include "HeapPtr.h"
#include "Animation.h"


class EXPORT AnimationPtr : public HeapPtr<Animation>
{
public:
	AnimationPtr();
	AnimationPtr(unsigned int index);
	AnimationPtr(bool isNull);
	Animation * Get();
	void Delete();
};