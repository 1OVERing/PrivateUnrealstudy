#include "Core.h"
#include "DeviceManager.h"
#include <exception>
#include <crtdbg.h>
#include "Util/STLException.h"

namespace Ronnie
{
	// 채널.
	// int->bit.
	void DeviceManager::InitializeDevice(
		HWND windowHandle, uint32 width, uint32 height, bool use4xaa)
	{
		uint32 createDeviceFlag = 0;
#if DEBUG || _DEBUG
		createDeviceFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		// 지원되는 라이브러리 버전 확인.
		const D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0
		};

		// 위의 배열의 원소 개수.
		const uint32 count = ARRAYSIZE(featureLevels);

		// 장치 생성.
		HRESULT hr = D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			createDeviceFlag,
			featureLevels,
			count,
			D3D11_SDK_VERSION,
			&device,
			nullptr,
			&deviceContext
		);

		ThrowIfFailed(hr, "Failed to create device");

		// 스왑 체인 생성.

		// 1. 멀티 샘플링 지원 여부 확인.
		uint32 numQualityLevel = 0;
		hr = device->CheckMultisampleQualityLevels(
			DXGI_FORMAT_R8G8B8A8_UNORM,
			4, 
			&numQualityLevel
		);

		ThrowIfFailed(hr, "Failed to check multi sampling");

		swapChain.Create(
			device, windowHandle, width, height, use4xaa, numQualityLevel
		);

		// 렌더 타겟 뷰 생성.
		renderTargetView.Create(swapChain.Get(), device);

		// 뎊스-스텐실 뷰 생성.
		depthStencilView.Create(device, width, height, use4xaa, numQualityLevel);

		// 바인딩(연결/할당).
		// OM -> Output Merger (렌더링 파이프라인 단계 중 최종).
		deviceContext->OMSetRenderTargets(
			1,
			renderTargetView.GetAddressOf(),
			depthStencilView.Get()
		);

		// 뷰포트(화면) 생성.
		D3D11_VIEWPORT viewport = { 0 };
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.Width = static_cast<float>(width);
		viewport.Height = static_cast<float>(height);
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		// 바인딩.
		// RS -> Rasterizer State(래스터라이저 스테이트 단계).
		deviceContext->RSSetViewports(1, &viewport);
	}

	void DeviceManager::BeginScene(const float* backgroundColor)
	{
		// 지우기 (Clear).

		// 배경색 지우기(칠하기).
		//deviceContext->ClearRenderTargetView(
		//	renderTargetView,
		//	backgroundColor
		//);
		renderTargetView.Clear(deviceContext, backgroundColor);

		// 뎊스 지우기.
		//deviceContext->ClearDepthStencilView(
		//	depthStencilView,
		//	D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		//	1.0f,
		//	0
		//);
		depthStencilView.Clear(
			deviceContext, 
			D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 
			1.0f, 0
		);
	}

	void DeviceManager::RenderScene()
	{
	}

	void DeviceManager::EndScene(uint32 syncInterval, uint32 flag)
	{
		// 화면 표시: 스왑(Swap) 프론트 버퍼 <-> 백 버퍼 교환.
		swapChain.Present(syncInterval, flag);
	}
}