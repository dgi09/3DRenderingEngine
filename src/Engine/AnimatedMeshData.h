#pragma once 
#include "Common.h"
#include "Vertex.h"
#include "Constants.h"
#include "Vector3.h"


class EXPORT AnimatedMeshData
{
public:
	unsigned int numOfVerts;
	AnimatedVert  verts[MAX_VERTS];

	unsigned int numOfIndecies;
	unsigned int indecies[MAX_INDECIES];
	Vector3 positions[MAX_VERTS];
};

