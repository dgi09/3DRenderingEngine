#include "Window.h"
#include "Scene.h"

Window::Window(void)
{
	windowOpened = true;
	depthView = nullptr;

}


Window::~Window(void)
{
	delete scene;
	

	if(depthState != nullptr)
		depthState->Release();

	if(depthView != nullptr)
		depthView->Release();
	if(depthTexture != nullptr)
		depthTexture->Release();

	if(backBufferView != nullptr)
		backBufferView->Release();
	if(context != nullptr)
		context->Release();
	if(device != nullptr)
		device->Release();

	if(swapChain != nullptr)
		swapChain->Release();
}

Window * Window::Create(int width,int height,LPCWSTR caption, int showCmd)
{

	WNDCLASSEX win;
	ZeroMemory(&win,sizeof(WNDCLASSEX));
	win.cbClsExtra = 0;
	win.cbWndExtra = 0;
	win.cbSize = sizeof(WNDCLASSEX);
	win.hInstance = GetModuleHandle(NULL);
	win.lpszClassName = L"D3DWindow";
	win.lpfnWndProc = WinProc;
	win.hbrBackground = (HBRUSH)(COLOR_WINDOW+2);

	

	RegisterClassEx(&win);
	HWND handle = CreateWindowEx(WS_EX_CLIENTEDGE,L"D3DWindow",caption,WS_OVERLAPPEDWINDOW,0,0,width,height,NULL
		,NULL,GetModuleHandle(NULL),NULL);


	Window * window = new Window();
	window->InitD3D(handle,width,height);
	
	ShowWindow(handle,showCmd);
	UpdateWindow(handle);


	return window;
}

Window * Window::Create(int width,int height,HWND handle)
{
	Window * window = new Window();
	window->InitD3D(handle,width,height);
	return window;
}

void Window::Destroy(Window * window)
{
	delete window;
}

void Window::HandleEvents()
{
	while(PeekMessage(&msg, NULL, 0, 0,PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if(msg.message == WM_QUIT)
			Close();
	}
}

bool Window::IsOpen()
{
	return windowOpened;
}

void Window::Close()
{
	windowOpened = false;
}



void Window::BeginDraw()
{
	float color[4] = {0.0f,0.0f,0.0f,1.0f};
	context->ClearRenderTargetView(backBufferView,color);
	context->ClearDepthStencilView(depthView,D3D11_CLEAR_DEPTH,1.0f,0);
}

void Window::EndDraw()
{
	swapChain->Present(0,0);
}

Scene * Window::GetScene()
{
	return scene;
}

void Window::InitD3D(HWND handle,int width,int height)
{
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc,sizeof(DXGI_SWAP_CHAIN_DESC));
	desc.BufferCount = 2;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.OutputWindow = handle;
	desc.SampleDesc.Count = 1;
	desc.Windowed = TRUE;

	D3D_FEATURE_LEVEL ftr;
	ftr = D3D_FEATURE_LEVEL_11_0;

	HRESULT reslt = D3D11CreateDeviceAndSwapChain(NULL,D3D_DRIVER_TYPE_HARDWARE,
		nullptr,0,&ftr,1,
		D3D11_SDK_VERSION,
		&desc,
		&swapChain,
		&device,
		nullptr,
		&context);

	ID3D11Texture2D * backBuffer = nullptr;
	swapChain->GetBuffer(0,__uuidof(ID3D11Texture2D),(LPVOID*)&backBuffer);
	device->CreateRenderTargetView(backBuffer,nullptr,&backBufferView);

	backBuffer->Release();


	D3D11_VIEWPORT view;
	ZeroMemory(&view,sizeof(D3D11_VIEWPORT));

	view.TopLeftX = 0.0f;
	view.TopLeftY = 0.0f;
	view.Width = width;
	view.Height = height;
	view.MinDepth = 0.0f;
	view.MaxDepth = 1.0f;

	context->RSSetViewports(1,&view);

	D3D11_TEXTURE2D_DESC depthDescr;
	depthDescr.ArraySize = 1;
	depthDescr.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthDescr.CPUAccessFlags = 0;
	depthDescr.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthDescr.Height = height;
	depthDescr.MipLevels = 1;
	depthDescr.MiscFlags = 0;
	depthDescr.SampleDesc.Count = 1;
	depthDescr.SampleDesc.Quality = 0;
	depthDescr.Usage = D3D11_USAGE_DEFAULT;
	depthDescr.Width = width;

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory( &descDSV, sizeof(descDSV) );
	descDSV.Format = depthDescr.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;

	device->CreateTexture2D(&depthDescr,nullptr,&depthTexture);
	device->CreateDepthStencilView(depthTexture,&descDSV,&depthView);
	context->OMSetRenderTargets(1,&backBufferView,depthView);

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	// Set up the description of the stencil state.
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	HRESULT res = device->CreateDepthStencilState(&depthStencilDesc,&depthState);
	context->OMSetDepthStencilState(depthState,1);
	
	D3D11_RASTERIZER_DESC rDesc;
	ZeroMemory(&rDesc,sizeof(D3D11_RASTERIZER_DESC));
	rDesc.CullMode = D3D11_CULL_NONE;
	rDesc.FillMode = D3D11_FILL_SOLID;

	device->CreateRasterizerState(&rDesc,&rState);
	context->RSSetState(rState);
	SceneDXData dxData;
	dxData.device = device;
	dxData.depthView = depthView;
	dxData.swapChain = swapChain;
	dxData.renderTarget = backBufferView;

	scene = new Scene(dxData,width,height);
}

HWND Window::GetHandle()
{
	return handle;
}



/////////////////////////

LRESULT CALLBACK WinProc(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
	default:
		return DefWindowProc(hWindow,msg,wParam,lParam);
	}

	return 0;
}