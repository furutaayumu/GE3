

#include "Input.h"
#include "cassert"

#include <windows.h>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
using namespace Microsoft::WRL;

bool Input::PushKey(BYTE keyNumber)
{
	if (key[keyNumber]) {
		return true;
	}
	return false;
}

void Input::Initialize(HINSTANCE hInstance,HWND hwnd) {
	HRESULT result;

	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));
	
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));

	result = keyboard->SetDataFormat(&c_dfDIKeyboard);
	assert(SUCCEEDED(result));
	
	result = keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	assert(SUCCEEDED(result));

}

void Input::Update() {
	memcpy(keyPre, key, sizeof(key));
	keyboard->Acquire();
	keyboard->GetDeviceState(sizeof(key), key);
}

bool Input::TriggerKey(BYTE keyNumber)
{
	if (key[keyNumber] != 0 && keyPre[keyNumber] == 0 ) {
		return true;
	}
	return false; 
}
