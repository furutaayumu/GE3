#pragma once
#include <wrl.h>
#include<d3d12.h>
#include<dxgi1_6.h>
#include "WinApp.h"
#include <dxcapi.h>
#include <array>
#include<format>

#include"externals/imgui/imgui_impl_dx12.h"
#include "externals/imgui/imgui_impl_win32.h"
class DirectXCommon
{
	
public:
	void Initialize(WinApp* winApp);
	//描画前処理
	void PreDraw();
	//描画後処理
	void PostDraw();

	//SRV専用
	D3D12_CPU_DESCRIPTOR_HANDLE GetSRVCPUDescriptorHandle(uint32_t index);
	D3D12_GPU_DESCRIPTOR_HANDLE GetSRVGPUDescriptorHandle(uint32_t index);

	ID3D12DescriptorHeap*	 CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible); 
	Microsoft::WRL::ComPtr<ID3D12Device> DeviceGet() { return device; }
	
private:
	void DeviceIni();
	void CommandIni();
	void SwapChain();
	void CreateZBuffer();
	void FlexCreateDescriptor();
	void RTVInitialize();
	void DSVInitialize();
	void FenceInitialize();
	void ViewportIni();
	void scissorIni();
	void DxCoInitialize();
	void ImGuiInitialize();

	Microsoft::WRL::ComPtr<ID3D12Device> device;
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
	


	//ハンドルを取得する
	static D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descriptorHeap, uint32_t descriptorSize, uint32_t index);
	static D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDecriptorHandle(const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descriptorHeap, uint32_t descriptorSize, uint32_t index);
	
	WinApp* winApp = nullptr;

	ID3D12CommandQueue* commandQueue = nullptr;
	ID3D12GraphicsCommandList* commandList = nullptr;
	ID3D12CommandAllocator* commandAllocator = nullptr;

	
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

	ID3D12Resource* resource = nullptr;

	ID3D12DescriptorHeap* rtvDescriptorHeap = nullptr;
	ID3D12DescriptorHeap* srvDescriptorHeap = nullptr;
	ID3D12DescriptorHeap* dsvDescriptorHeap = nullptr;

	//RTV
	const uint32_t descriptorSizeRTV{};
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
	//SRV
	const uint32_t descriptorSizeSRV{};
	//DSV
	const uint32_t descriptorSizeDSV{};

	ID3D12Fence* fence = nullptr;

	D3D12_VIEWPORT viewport{};
	D3D12_RECT scissorRect{};

	D3D12_CPU_DESCRIPTOR_HANDLE rtvStartHandle{};
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2]{};

	IDxcUtils* dxcUtils = nullptr;
	IDxcCompiler3* dxCompiler = nullptr;
	IDxcIncludeHandler* includeHander = nullptr;

	//スワップチェーンリソーｽ
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, 2> swapChainResources;
	
	//フェンス値
	UINT64 fenceValue = 0;
	HANDLE fenceEvent{};
}; 

