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
	void CreateZBuffer();
	void FlexCreateDescriptor();
	void RTVInitialize();
private:
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible); 
	WinApp* winApp = nullptr;

	ID3D12CommandQueue* commandQueue = nullptr;
	ID3D12GraphicsCommandList* commandList = nullptr;
	ID3D12CommandAllocator* commandAllocator = nullptr;

	IDXGISwapChain4* swapChain = nullptr;

	ID3D12Resource* resource = nullptr;

	ID3D12DescriptorHeap* rtvDescriptorHeap = nullptr;
	ID3D12DescriptorHeap* srvDescriptorHeap = nullptr;
	ID3D12DescriptorHeap* dsvDescriptorHeap = nullptr;

	D3D12_CPU_DESCRIPTOR_HANDLE* rtvHandles[2] = { nullptr };
	ID3D12Resource* swapChainResources[2] = { nullptr };
}; 

