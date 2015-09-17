#pragma once
#include "Common.h"
#include <d3d11.h>
#include "DeviceDependable.h"
#include "IDestroyable.h"
#include "Vector3.h"
#include "Constants.h"

class EXPORT Mesh : public DeviceDependable , public IDestroyable
{
	
	ID3D11Buffer * vertexBuffer;
	ID3D11Buffer * indexBuffer;

	unsigned int numberOfVerts;
	unsigned int numberOfIndecies;
	unsigned int stride;

	D3D11_PRIMITIVE_TOPOLOGY topology;

	Vector3 positionsBuffer[MAX_VERTS];
public:
	void Init();
	void Destroy();

	void Draw();
	void DrawIndexed();
	void DrawInstanced(unsigned int numberOfInstanes);
	

	void InitVertexBuffer(unsigned int dataSize, unsigned int stride,void * data);
	void InitIndexBuffer(unsigned int numberIndecies,unsigned int * data);
	void InitPositionBuffer(Vector3 * buffer);
	void SetPrimitveTopology(D3D11_PRIMITIVE_TOPOLOGY topology);

	Vector3 * GetPoistions();


	int GetNumberOfVerts();
	void * LockVerts();
	void UnlockVerts();
};

