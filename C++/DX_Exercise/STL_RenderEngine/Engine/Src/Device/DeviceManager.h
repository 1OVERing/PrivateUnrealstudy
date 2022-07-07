#pragma once

#ifndef _DEVICE_MANAGER_
#define _DEVICE_MANAGER_

#include "Core.h"
#include "SwapChain.h"
#include "RenderTargetView.h"
#include "DepthStencilView.h"

// Direct3D 장치 관리.
namespace Ronnie
{
	class ENGINE_API DeviceManager
	{
	public:
		DeviceManager() = default;
		virtual ~DeviceManager() = default;

		// use4xaa - 멀티샘플링 사용 여부 설정.
		void InitializeDevice(
			HWND windowHandle,
			uint32 width, uint32 height,
			bool use4xaa
		);

		// 렌더링 관련.
		void BeginScene(const float* backgroundColor);
		void RenderScene();
		void EndScene(uint32 syncInterval, uint32 flag);

		// Getter.
		ID3D11Device* GetDevice() { return device; }
		ID3D11Device** GetDeviceAddressOf() { return &device; }

		ID3D11DeviceContext* GetDeviceContext() { return deviceContext; }
		ID3D11DeviceContext** GetDeviceContextAddressOf() { return &deviceContext; }

		IDXGISwapChain* GetSwapChain() { return swapChain.Get(); }

		ID3D11DepthStencilView* GetDepthStencilView() { return depthStencilView.Get(); }
		ID3D11RenderTargetView* GetRenderTargetView() { return renderTargetView.Get(); }

	protected:
		
		ID3D11Device* device;
		ID3D11DeviceContext* deviceContext;
	
		SwapChain swapChain;
		RenderTargetView renderTargetView;
		DepthStencilView depthStencilView;
	};
}
#endif