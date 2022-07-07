#include "Core.h"
#include "RenderTargetView.h"
#include "Util/STLException.h"

namespace Ronnie
{
	RenderTargetView::RenderTargetView()
		: renderTargetView(nullptr)
	{
	}

	RenderTargetView::~RenderTargetView()
	{
		SafeRelease(renderTargetView);
	}

	void RenderTargetView::Create(IDXGISwapChain* swapChain, ID3D11Device* device)
	{
		// ���� Ÿ�� �� ����.

		// ����ü���� ������ �ִ� ����� ��������.
		// �б� ����.
		ID3D11Texture2D* backbuffer = nullptr;
		HRESULT hr = swapChain->GetBuffer(0, IID_PPV_ARGS(&backbuffer));
		ThrowIfFailed(hr, "Failed to get back buffer");

		// ���� Ÿ�� �� ����.
		hr = device->CreateRenderTargetView(
			backbuffer,
			nullptr,
			&renderTargetView
		);

		// ���ҽ� ����.
		SafeRelease(backbuffer);
		ThrowIfFailed(hr, "Failed to create render target view");
	}
	
	void RenderTargetView::Clear(ID3D11DeviceContext* context, const float* color)
	{
		context->ClearRenderTargetView(renderTargetView, color);
	}
}