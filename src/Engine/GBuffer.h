#pragma once
#include "Common.h"

#include "IDestroyable.h"
#include "TexturePtr.h"
#include "DeviceDependable.h"
#include "DeviceDependableFactory.h"
#include "SamplerPtr.h"
#include <d3d11.h>
#include "Color.h"


#define DIFFUSE 0
#define NORMAL 1
#define SPEC_EMMISIVE 2
#define DEPTH 3

class EXPORT GBuffer : public DeviceDependable , public IDestroyable
{
	TexturePtr textures[4];
	ID3D11RenderTargetView * views[3];
public:

	void Init(int windowW, int windowH, DeviceDependableFactory * factory);
	void Clear(Color diffuseColor);
	void BindToOM();
	void Destroy();
	void BindToPS();
	void UnbindFromPS();
	
	TexturePtr GetDiffuseTexture();
	TexturePtr GetDepthTexture();
};