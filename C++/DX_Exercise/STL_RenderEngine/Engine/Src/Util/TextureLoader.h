#pragma once

#ifndef _TEXTURE_LOADER_
#define _TEXTURE_LOADER_

#include "Core.h"

namespace Ronnie
{
	class ENGINE_API TextureLoader
	{
	public:
		// ���̴��� �ؽ�ó�� �ѱ� �� ����ϴ� Ÿ��.
		// ID3D11Texture1D/2D/3D.
		static ID3D11ShaderResourceView* CreateShaderResourceView(
			ID3D11Device* device,
			const std::wstring& filename
		);

		static void Release();

		// �ؽ� ���̺� (Ű-������)
		static std::unordered_map<std::wstring, ID3D11ShaderResourceView*> textureMap;
	};
}
#endif