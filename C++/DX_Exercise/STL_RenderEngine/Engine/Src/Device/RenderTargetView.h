#pragma once

#ifndef _RENDER_TARGET_VIEW_
#define _RENDER_TARGET_VIEW_

#include "Core.h"

namespace Ronnie
{
	class ENGINE_API RenderTargetView
	{
	public:
		RenderTargetView();
		~RenderTargetView();

		void Create(IDXGISwapChain* swapChain, ID3D11Device* device);
		void Clear(ID3D11DeviceContext* context, const float* color);

		ID3D11RenderTargetView* Get() { return renderTargetView; }
		ID3D11RenderTargetView** GetAddressOf() { return &renderTargetView; }

	private:
		ID3D11RenderTargetView* renderTargetView;
	};
}
#endif