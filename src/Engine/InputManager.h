#pragma once 
#include "Common.h"
#include <Windows.h>
#include <dinput.h>

enum EXPORT MouseButton
{
	B_LEFT = 0,
	B_RIGHT
};

class EXPORT InputManager
{
	IDirectInput8 * inputDevice;
	IDirectInputDevice8 * keyboard;
	IDirectInputDevice8 * mouse;

	DIMOUSESTATE mState;

	int mouseX, mouseY;
	bool mouseMove;
	unsigned char keys[256];

	bool firstInit;
	HWND hwnd;
public:
	InputManager();
	~InputManager();

	void Init(HWND handle,HINSTANCE hInstance);
	void Update();

	bool KeyPressed(UINT key);
	bool MouseButtonDown(MouseButton button);
	bool MouseMove();

	int GetMouseX();
	int GetMouseY();
};