#pragma  once 
#include "Common.h"
#include "DeviceDependable.h"
#include <d3d11.h>
#include "ShaderType.h"
#include "IDestroyable.h"

enum TextureUsage
{
	RENDER_TARGET = D3D11_BIND_RENDER_TARGET,
	DEPTH_BUFFER = D3D11_BIND_DEPTH_STENCIL,
	UNORDERED_VIEW = D3D11_BIND_UNORDERED_ACCESS
};

class EXPORT Texture : public DeviceDependable , public IDestroyable
{
	ID3D11Texture2D * texture;
	ID3D11ShaderResourceView * shaderResource;
	ID3D11RenderTargetView * target;
	ID3D11DepthStencilView * depthView;
	ID3D11UnorderedAccessView * uav;

	TextureUsage usage;
	DXGI_FORMAT format;

	bool fromFile;
public:

	void Init();
	void Destroy();


	void InitTexture(unsigned int width,unsigned int height , TextureUsage usage ,DXGI_FORMAT format,int MipLevels = 1);
	void LoadFromFile(const char * fileName);
	ID3D11ShaderResourceView * GetShaderResourcePointer();
	ID3D11RenderTargetView * GetRenderTargetPtr();
	ID3D11DepthStencilView * GetDepthBufferPtr();
	ID3D11UnorderedAccessView * GetUnorderedView();

	void Bind(ShaderType shaderType);
	void GenerateMips();

protected:
	void CreateResourceView();
	void CreateTargetView();
	void CreateDepthBuffer();
	void CreateUnorderedView();
};