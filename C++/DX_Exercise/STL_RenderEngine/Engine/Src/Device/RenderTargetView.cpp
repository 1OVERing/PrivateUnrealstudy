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
		// 렌더 타겟 뷰 생성.

		// 스왑체인이 가지고 있는 백버퍼 가져오기.
		// 읽기 전용.
		ID3D11Texture2D* backbuffer = nullptr;
		HRESULT hr = swapChain->GetBuffer(0, IID_PPV_ARGS(&backbuffer));
		ThrowIfFailed(hr, "Failed to get back buffer");

		// 렌더 타겟 뷰 생성.
		hr = device->CreateRenderTargetView(
			backbuffer,
			nullptr,
			&renderTargetView
		);

		// 리소스 해제.
		SafeRelease(backbuffer);
		ThrowIfFailed(hr, "Failed to create render target view");
	}
	
	void RenderTargetView::Clear(ID3D11DeviceContext* context, const float* color)
	{
		context->ClearRenderTargetView(renderTargetView, color);
	}
}