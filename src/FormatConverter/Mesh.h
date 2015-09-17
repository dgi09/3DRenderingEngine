#pragma once 

template <class T>
class Mesh
{
public:

	Mesh();
	~Mesh();
	
	T * verts;
	unsigned int numberOfVerts;
	unsigned int * indecies;
	unsigned int numberOfIndecies;


};

template <class T>
Mesh<T>::~Mesh()
{
	if(verts != nullptr)
	{
		delete[] verts;
	}

	if(indecies != nullptr)
		delete[] indecies;
}

template <class T>
Mesh<T>::Mesh()
{
	verts = nullptr;
	indecies = nullptr;
	numberOfIndecies = 0;
	numberOfVerts = 0;
}
