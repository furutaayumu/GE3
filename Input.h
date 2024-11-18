#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <wrl.h>
#include "WinApp.h"


class Input
{
public:
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
public:

	bool PushKey(BYTE keyNumber);
	void Initialize(WinApp* winApp);
	void Update();
	bool TriggerKey(BYTE keyNumber);

private:
	BYTE keyPre[256] = {};
	BYTE key[256] = {};
	ComPtr<IDirectInputDevice8> keyboard;
	ComPtr<IDirectInput8> directInput;

	WinApp* winApp = nullptr;
};

