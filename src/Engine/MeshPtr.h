#pragma once
#include "Common.h"
#include "HeapPtr.h"
#include "Mesh.h"


class EXPORT MeshPtr : public HeapPtr<Mesh>
{
public:
	MeshPtr();
	MeshPtr(unsigned int index);
	MeshPtr(bool isNull);
	Mesh * Get();
	void Delete();
};

