#pragma once 
#include "Common.h"

#include "VertexShaderPtr.h"
#include "PixelShaderPtr.h"
#include "IDestroyable.h"

class EXPORT DeviceDependableFactory;
class EXPORT IInputLayout;

class EXPORT Effect : public IDestroyable
{

	VertexShaderPtr vShader;
	PixelShaderPtr pShader;
	
public:
	virtual void Init(DeviceDependableFactory * factory);
	virtual void Destroy();


	void LoadVertexShaderFromString(const char * data,unsigned int lenght,IInputLayout * layout);
	void LoadPixelShaderFromString(const char * data,unsigned int lenght);

	void Apply();
};