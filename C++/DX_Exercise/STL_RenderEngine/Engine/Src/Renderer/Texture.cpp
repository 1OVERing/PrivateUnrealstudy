#include "Core.h"
#include "Texture.h"
#include "Util/TextureLoader.h"
#include "Util/STLException.h"

namespace Ronnie
{
	Texture::Texture()
		: filename(L""), shaderResourceView(nullptr)
	{
	}

	Texture::Texture(const std::wstring& filename)
		: filename(filename), shaderResourceView(nullptr)
	{
	}
	
	Texture::~Texture()
	{
	}

	void Texture::Initialize(ID3D11Device* device)
	{
		shaderResourceView = TextureLoader::CreateShaderResourceView(device, filename);
		if (shaderResourceView == nullptr)
		{
			throw std::exception("Failed to create shader resource view.");
		}
	}

	void Texture::Bind(ID3D11DeviceContext* deviceContext, uint32 textureIndex)
	{
		deviceContext->PSSetShaderResources(
			textureIndex, 1, &shaderResourceView
		);
	}
}