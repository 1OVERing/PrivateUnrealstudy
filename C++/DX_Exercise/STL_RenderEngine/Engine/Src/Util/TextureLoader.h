#pragma once

#ifndef _TEXTURE_LOADER_
#define _TEXTURE_LOADER_

#include "Core.h"

namespace Ronnie
{
	class ENGINE_API TextureLoader
	{
	public:
		// 쉐이더에 텍스처를 넘길 때 사용하는 타입.
		// ID3D11Texture1D/2D/3D.
		static ID3D11ShaderResourceView* CreateShaderResourceView(
			ID3D11Device* device,
			const std::wstring& filename
		);

		static void Release();

		// 해시 테이블 (키-데이터)
		static std::unordered_map<std::wstring, ID3D11ShaderResourceView*> textureMap;
	};
}
#endif