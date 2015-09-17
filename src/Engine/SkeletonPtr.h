#pragma once
#include "Common.h"
#include "HeapPtr.h"
#include "Skeleton.h"

class SkeletonPtr : public HeapPtr<Skeleton>
{
public:
	SkeletonPtr();
	SkeletonPtr(unsigned int index);
	SkeletonPtr(bool isNull);
	Skeleton * Get();
	void Delete();
};

