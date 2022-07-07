#include "Core.h"
#include "SwapChain.h"
#include "Util/STLException.h"

namespace Ronnie
{
	SwapChain::SwapChain()
		: swapChain(nullptr)
	{
	}
	
	SwapChain::~SwapChain()
	{
		SafeRelease(swapChain);
	}

	void SwapChain::Create(ID3D11Device* device, HWND windowHandle, int width, int height, bool use4xaa, uint32 numQualityLevel)
	{
		IDXGIDevice* dxgiDevice;
		HRESULT hr = device->QueryInterface(IID_PPV_ARGS(&dxgiDevice));

		ThrowIfFailed(hr, "Failed to get IDXGIDevice");

		IDXGIAdapter* dxgiAdapter;
		hr = dxgiDevice->GetParent(IID_PPV_ARGS(&dxgiAdapter));

		SafeRelease(dxgiDevice);
		ThrowIfFailed(hr, "Failed to Get IDXGIAdapter");

		IDXGIFactory* dxgiFactory;
		hr = dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));

		SafeRelease(dxgiAdapter);
		ThrowIfFailed(hr, "Failed to Get IDXGIFactory");

		// Draw -> ȭ�� �̹���.
		// Draw -> �ؽ�ó(�׸����� �̹���)
		// ����ü�� ������ ���� ����.
		// ������ ������.
		// ���۵� ������ -> �׸� �׸��� -> �̹��� ���� -> ���̴�.
		DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
		swapChainDesc.BufferCount = 1;	// ���� 2���� ����ϰڴ�->���� ���۸�.
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.Windowed = true;
		swapChainDesc.OutputWindow = windowHandle;
		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = height;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		if (use4xaa)
		{
			swapChainDesc.SampleDesc.Count = 4;
			swapChainDesc.SampleDesc.Quality = numQualityLevel - 1;
		}
		else
		{
			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;
		}

		// ����.
		hr = dxgiFactory->CreateSwapChain(
			device,
			&swapChainDesc,
			&swapChain
		);

		// COM -> Component Object Model.
		// ActiveX
		SafeRelease(dxgiFactory);
		ThrowIfFailed(hr, "Failed to create swap chain");
	}

	// ���� (Wrapper) -> �Լ� ���α�.
	// Invoke - ���� ȣ��.
	void SwapChain::Present(uint32 syncInterval, uint32 flags)
	{
		swapChain->Present(syncInterval, flags);
	}
}