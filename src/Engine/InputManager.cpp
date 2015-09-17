#include "InputManager.h"
#include <Windows.h>

InputManager::InputManager()
{
	inputDevice = nullptr;
	keyboard = nullptr;

	mouseMove = false;
	mouseX = 0;
	mouseY = 0;
	firstInit = true;
}

InputManager::~InputManager()
{

	if(keyboard != nullptr)
	{
		keyboard->Unacquire();
		keyboard->Release();
	}

	if(inputDevice != nullptr)
		inputDevice->Release();
}

void InputManager::Init(HWND handle,HINSTANCE hInstance)
{

	hwnd = handle;

	DirectInput8Create(hInstance,0x0800,IID_IDirectInput8,(void**)&inputDevice,nullptr);
	inputDevice->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	keyboard->SetDataFormat(&c_dfDIKeyboard);
	keyboard->SetCooperativeLevel(handle, DISCL_FOREGROUND | DISCL_EXCLUSIVE);

	keyboard->Acquire();
	//keyboard->GetDeviceState(sizeof(keys),(void**)&keys);
	ZeroMemory(keys,sizeof(keys));

	inputDevice->CreateDevice(GUID_SysMouse, &mouse, NULL);
	mouse->SetDataFormat(&c_dfDIMouse);
	mouse->SetCooperativeLevel(handle, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	mouse->Acquire();


}

void InputManager::Update()
{
	if(firstInit)
	{
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(hwnd,&p);

		mouseX = p.x;
		mouseY = p.y;

		firstInit = false;
	}

	HRESULT res = keyboard->GetDeviceState(sizeof(keys),(void**)&keys);
	if((res == DIERR_INPUTLOST) || (res == DIERR_NOTACQUIRED))
	{
		keyboard->Acquire();
	}

	res = mouse->GetDeviceState(sizeof(DIMOUSESTATE),(void**)&mState);


	if((res == DIERR_INPUTLOST) || (res == DIERR_NOTACQUIRED))
	{
		mouse->Acquire();
	}


	if(mState.lX != 0 || mState.lY != 0)
	{
		mouseX += mState.lX;
		mouseY += mState.lY;


		mouseMove = true;

	}
	else 
	{
		mouseMove = false;
	}
}

bool InputManager::KeyPressed(UINT key)
{
	if(key >= 0 && key <= 256)
	{
		if(keys[key])
			return true;
		else return false;
	}

	return false;
}

bool InputManager::MouseMove()
{
	return mouseMove;
}

int InputManager::GetMouseX()
{
	return mouseX;
}

int InputManager::GetMouseY()
{
	return mouseY;
}

bool InputManager::MouseButtonDown(MouseButton button)
{
	return (bool)(mState.rgbButtons[button] & 0x80);
}
