#pragma once
#include <cstdint>
#include<Windows.h>
class WinApp
{

public:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

		//getter
		HWND GetHwnd() const { return hwnd; }
		HINSTANCE GetHInstance() const { return wc.hInstance; }

public:
	void Initialize();
	void Update();
	void Finalize();
public:
	static const int32_t kClientWidth = 1280;
	static const int32_t kClientHeight = 720;

	bool ProcessMessage();
private:
	HWND hwnd = nullptr;

	WNDCLASS wc{};
};

