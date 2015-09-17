#pragma  once 
#include "Common.h"
#include <d3d11.h>
#include "TexturePtr.h"
#include "PixelShaderPtr.h"

class DeviceDependableFactory;


class EXPORT ToneMapper
{
	PixelShaderPtr  shader;
	ID3D11Device * device;
	TexturePtr bloomTexture;
public:
	void Init(DeviceDependableFactory * factory);
	void SetDevice(ID3D11Device * device);
	void SetShaderCode(const char * code);
	void Destroy();

	void SetBloomTexture(TexturePtr txt);
	void Run(TexturePtr src,TexturePtr dst);
	void Run(TexturePtr src,ID3D11RenderTargetView * dst);

private:
	void IntRun(ID3D11ShaderResourceView * src,ID3D11RenderTargetView * dst);
};