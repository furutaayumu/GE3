#include "WinApp.h"
#include "externals/imgui/imgui.h"
#include <cstdint>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void WinApp::Initialize() {
	CoInitializeEx(0, COINIT_MULTITHREADED);

	//ウィンドウプロシージャ
	wc.lpfnWndProc = WindowProc;

	//ウィンドウクラス名
	wc.lpszClassName = L"CG2WindowClass";

	//インスタンスハンドル
	wc.hInstance = GetModuleHandle(nullptr);

	//カーソル
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

	//ウィンドウクラスを登録する
	RegisterClass(&wc);

	RECT wrc = { 0,0,kClientWidth,kClientHeight };

	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	////ウィンドウの生成
	//HWND hwnd = CreateWindow(
	//	wc.lpszClassName,
	//	L"CG2",
	//	WS_OVERLAPPEDWINDOW,
	//	CW_USEDEFAULT,
	//	CW_USEDEFAULT,
	//	wrc.right - wrc.left,
	//	wrc.bottom - wrc.top,
	//	nullptr,
	//	nullptr,
	//	wc.hInstance,
	//	nullptr
	//);
	ShowWindow(hwnd, SW_SHOW);
}

void WinApp::Update() {

}