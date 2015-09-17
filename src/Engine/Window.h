#pragma once
#include "Common.h"
#include <d3d11.h>
#include <Windows.h>

class EXPORT Scene;

class EXPORT Window
{
	HWND handle;
	ID3D11DeviceContext * context;
	ID3D11Device * device;
	IDXGISwapChain * swapChain;
	ID3D11RenderTargetView * backBufferView;
	ID3D11RasterizerState * rState;

	ID3D11DepthStencilView * depthView;
	ID3D11DepthStencilState * depthState;
	ID3D11Texture2D * depthTexture;

	bool windowOpened;
	int width;
	int height;

	MSG msg;

	Scene * scene;

	Window(void);
	~Window(void);


public:
	
	static Window * Create(int width,int height,LPCWSTR caption, int showCmd);
	static Window * Create(int width,int height,HWND handle);
	static void Destroy(Window * window);
	
	void HandleEvents();
	bool IsOpen();
	void Close();

	void EndDraw();

	void BeginDraw();

	HWND GetHandle();

	Scene * GetScene();

protected:
	void InitD3D(HWND handle,int width,int height);
};

extern LRESULT CALLBACK WinProc(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam);

