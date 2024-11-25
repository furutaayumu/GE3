#pragma once
#include <wrl.h>
#include<d3d12.h>
#include<dxgi1_6.h>
#include "WinApp.h"
class DirectXCommon
{
public:
	void Initialize(WinApp* winApp);
	void DeviceIni();
	void CommandIni();
	void SwapChain();
	void 
private:
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;
	WinApp* winApp = nullptr;
	ID3D12CommandQueue* commandQueue = nullptr;
}; 

