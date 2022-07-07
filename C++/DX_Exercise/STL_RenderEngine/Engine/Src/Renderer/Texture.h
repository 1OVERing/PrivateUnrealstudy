#pragma once

#ifndef _TEXTURE_
#define _TEXTURE_

namespace Ronnie
{
	class ENGINE_API Texture
	{
	public:
		Texture();
		Texture(const std::wstring& filename);
		~Texture();

		void Initialize(ID3D11Device* device);
		void Bind(ID3D11DeviceContext* deviceContext, uint32 textureIndex);

		ID3D11ShaderResourceView* Get() { return shaderResourceView; }
		ID3D11ShaderResourceView** GetAddressOf() { return &shaderResourceView; }

		ID3D11ShaderResourceView** operator&() { return &shaderResourceView; }

	private:
		std::wstring filename;
		ID3D11ShaderResourceView* shaderResourceView;
	};
}
#endif