#pragma once
#include "Common.h"
#include "Texture.h"
#include "HeapPtr.h"

class EXPORT TexturePtr : public HeapPtr<Texture>
{

public:
	TexturePtr();
	TexturePtr(unsigned int index);
	TexturePtr(bool isNull);

	Texture * Get();
	void Delete();
};

