#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <wrl.h>

#pragma once
class Input
{
public:
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
public:


	void Initialize(HINSTANCE hInstance,HWND hwnd);
	void Update();

private:
	ComPtr<IDirectInputDevice8> keyboard;
};

