#include "Core.h"
#include "DeviceManager.h"
#include <exception>
#include <crtdbg.h>
#include "Util/STLException.h"

namespace Ronnie
{
	// ä��.
	// int->bit.
	void DeviceManager::InitializeDevice(
		HWND windowHandle, uint32 width, uint32 height, bool use4xaa)
	{
		uint32 createDeviceFlag = 0;
#if DEBUG || _DEBUG
		createDeviceFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		// �����Ǵ� ���̺귯�� ���� Ȯ��.
		const D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0
		};

		// ���� �迭�� ���� ����.
		const uint32 count = ARRAYSIZE(featureLevels);

		// ��ġ ����.
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

		// ���� ü�� ����.

		// 1. ��Ƽ ���ø� ���� ���� Ȯ��.
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

		// ���� Ÿ�� �� ����.
		renderTargetView.Create(swapChain.Get(), device);

		// �X��-���ٽ� �� ����.
		depthStencilView.Create(device, width, height, use4xaa, numQualityLevel);

		// ���ε�(����/�Ҵ�).
		// OM -> Output Merger (������ ���������� �ܰ� �� ����).
		deviceContext->OMSetRenderTargets(
			1,
			renderTargetView.GetAddressOf(),
			depthStencilView.Get()
		);

		// ����Ʈ(ȭ��) ����.
		D3D11_VIEWPORT viewport = { 0 };
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.Width = static_cast<float>(width);
		viewport.Height = static_cast<float>(height);
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		// ���ε�.
		// RS -> Rasterizer State(�����Ͷ����� ������Ʈ �ܰ�).
		deviceContext->RSSetViewports(1, &viewport);
	}

	void DeviceManager::BeginScene(const float* backgroundColor)
	{
		// ����� (Clear).

		// ���� �����(ĥ�ϱ�).
		//deviceContext->ClearRenderTargetView(
		//	renderTargetView,
		//	backgroundColor
		//);
		renderTargetView.Clear(deviceContext, backgroundColor);

		// �X�� �����.
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
		// ȭ�� ǥ��: ����(Swap) ����Ʈ ���� <-> �� ���� ��ȯ.
		swapChain.Present(syncInterval, flag);
	}
}