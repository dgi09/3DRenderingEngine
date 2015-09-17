#include "MeshPtr.h"
#include "Heap.h"

MeshPtr::MeshPtr(unsigned int index) : HeapPtr(index)
{
}

MeshPtr::MeshPtr()
{

}

MeshPtr::MeshPtr(bool isNull) : HeapPtr(isNull)
{
}

Mesh * MeshPtr::Get()
{
	return Heap::GetPtr()->Meshes.Get(index);
}

void MeshPtr::Delete()
{
	Heap::GetPtr()->Meshes.Get(index)->Destroy();
	Heap::GetPtr()->Meshes.Delete(index);
}
