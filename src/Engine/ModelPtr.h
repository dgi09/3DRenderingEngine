#pragma once 
#include "Common.h"
#include "HeapPtr.h"
#include "Model.h"


class EXPORT ModelPtr : public HeapPtr<Model>
{
public:
	ModelPtr();
	ModelPtr(unsigned int index);
	ModelPtr(bool isNull);
	Model * Get();
	void Delete();
};