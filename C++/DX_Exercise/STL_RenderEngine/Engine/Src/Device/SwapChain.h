#pragma once

#ifndef _SWAP_CHAIN_
#define _SWAP_CHAIN_

#include "Core.h"

namespace Ronnie
{
	class ENGINE_API SwapChain
	{
	public:
		SwapChain();
		~SwapChain();

		void Create(
			ID3D11Device* device, 
			HWND windowHandle, 
			int width, int height, 
			bool use4xaa, 
			uint32 numQualityLevel
		);

		void Present(uint32 syncInterval, uint32 flags);

		IDXGISwapChain* Get() { return swapChain; }
		IDXGISwapChain** GetAddressOf() { return &swapChain; }

	private:
		IDXGISwapChain* swapChain;
	};
}
#endif