#pragma once 
#include <D3D11.h>
#include "Common.h"


class EXPORT SceneDXData
{
public:
	ID3D11Device * device;
	ID3D11RenderTargetView * renderTarget;
	ID3D11DepthStencilView * depthView;
	IDXGISwapChain * swapChain;
};