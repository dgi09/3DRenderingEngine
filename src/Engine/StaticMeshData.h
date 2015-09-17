#pragma once
#include "Common.h"
#include "Vertex.h"
#include "Constants.h"
#include "Vector3.h"
class EXPORT StaticMeshData
{
public:
	StaticVert  vertecies[MAX_VERTS];
	unsigned int numberOfVerts;
	
	unsigned int  indecies[MAX_INDECIES];
	unsigned int numberOfIndecies;

	Vector3 position[MAX_VERTS];
};