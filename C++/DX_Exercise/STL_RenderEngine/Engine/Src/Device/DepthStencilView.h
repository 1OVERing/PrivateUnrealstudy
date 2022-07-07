#pragma once

#ifndef _DEPTH_STENCIL_VIEW_
#define _DEPTH_STENCIL_VIEW_

#include "Core.h"

namespace Ronnie
{
	class ENGINE_API DepthStencilView
	{
	public:
		DepthStencilView();
		~DepthStencilView();

		void Create(ID3D11Device* device, uint32 width, uint32 height, bool use4xaa, uint32 numQualityLevel);
		void Clear(ID3D11DeviceContext* context, uint32 clearFlags, float depth, uint8 stencil);

		ID3D11DepthStencilView* Get() { return depthStencilView; }
		ID3D11DepthStencilView** GetAddressOf() { return &depthStencilView; }

	private:
		ID3D11DepthStencilView* depthStencilView;
	};
}
#endif