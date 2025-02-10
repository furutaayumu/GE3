#pragma once
#include <wrl.h>
#include<d3d12.h>
#include<dxgi1_6.h>
#include "WinApp.h"
#include <dxcapi.h>
#include <array>
#include<format>
#include <chrono>
#include <thread>

#include"externals/DirectXTex/DirectXTex.h"
#include"externals/imgui/imgui_impl_dx12.h"
#include "externals/imgui/imgui_impl_win32.h"
class DirectXCommon
{
public:
	Microsoft::WRL::ComPtr<IDxcBlob> CompileShader(
		//CompilerするShaderファイルへのパス
		const std::wstring& filePath,
		//Compilerに使用するProfile
		const wchar_t* profile);

	Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(size_t sizeInBytes);
	ID3D12Resource* CreateTextureResource(const DirectX::TexMetadata& metadata);
	void UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);
	static DirectX::ScratchImage LoadTexture(const std::string& filePath);
	HANDLE GetFenceEvent()const { return fenceEvent; }
	ID3D12GraphicsCommandList* GetCommandlist()const { return commandList.Get(); }
	ID3D12DescriptorHeap* GetSrvDescriptorHeap()const { return srvDescriptorHeap.Get(); }
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);
private://関数
	
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
	
	//ゲッター
	ID3D12Device* GetDevice() const { return device.Get(); }
	ID3D12GraphicsCommandList* GetCommandList()const { return commandList.Get(); }
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

	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue = nullptr;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList = nullptr;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator = nullptr;

	
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};


	Microsoft::WRL::ComPtr<ID3D12Resource> resource = nullptr;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvDescriptorHeap = nullptr;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvDescriptorHeap = nullptr;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvDescriptorHeap = nullptr;

	Microsoft::WRL::ComPtr<ID3D12Resource> depthStancilResource = nullptr;

	//RTV
	const uint32_t descriptorSizeRTV{};
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
	//SRV
	const uint32_t descriptorSizeSRV{};
	//DSV
	const uint32_t descriptorSizeDSV{};

	Microsoft::WRL::ComPtr<ID3D12Fence> fence = nullptr;

	D3D12_VIEWPORT viewport{};
	D3D12_RECT scissorRect{};

	D3D12_CPU_DESCRIPTOR_HANDLE rtvStartHandle{};
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2]{};

	Microsoft::WRL::ComPtr<IDxcUtils> dxcUtils = nullptr;
	Microsoft::WRL::ComPtr<IDxcCompiler3> dxCompiler = nullptr;
	Microsoft::WRL::ComPtr<IDxcIncludeHandler> includeHander = nullptr;



	//スワップチェーンリソーｽ
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, 2> swapChainResources;
	
	//フェンス値
	UINT64 fenceValue = 0;
	HANDLE fenceEvent{};

	D3D12_RESOURCE_BARRIER barrier{};

	private:
	//FP固定化
		void InitializeFixFPS();

		void UpdataFixFPS();
		std::chrono::steady_clock::time_point reference_;
}; 

