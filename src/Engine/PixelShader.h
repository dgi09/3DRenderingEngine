#pragma  once
#include "Common.h"
#include "DeviceDependable.h"
#include "IDestroyable.h"
#include <d3d11.h>

class EXPORT PixelShader : public DeviceDependable , public IDestroyable
{
	ID3D11PixelShader * shader;
public:
	void Bind();
	void LoadFromFile(const char * fileName , const char * entryPoint);
	void LoadFromString(const char * data,unsigned int lenght,const char * entryPoint);

	void Destroy();
	void Init();
};