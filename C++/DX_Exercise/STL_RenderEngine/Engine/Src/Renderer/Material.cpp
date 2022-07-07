#include "Core.h"
#include "Material.h"

#include "Util/Logger.h"

namespace Ronnie
{
	Material::Material()
		: index(0), shader(nullptr)
	{
	}

	Material::Material(Shader* const shader)
		: index(0), shader(shader)
	{
	}

	Material::~Material()
	{
		for (auto texture : textures)
		{
			SafeDelete(texture);
		}
	}

	void Material::Initialize(ID3D11Device* device)
	{
		if (shader == nullptr)
		{
			return;
		}
		
		shader->Initialize(device);
		
		for (auto texture : textures)
		{
			texture->Initialize(device);
		}

		samplerState.Initialize(device);
	}

	void Material::Bind(ID3D11DeviceContext* context)
	{
		if (shader == nullptr)
		{
			return;
		}

		shader->Bind(context);

		for (uint32 ix = 0; ix < textures.size(); ++ix)
		{
			textures[ix]->Bind(context, ix);
		}

		samplerState.Bind(context, 0);
	}

	void Material::AddTexture(Texture* const newTexture)
	{
		textures.emplace_back(newTexture);
	}
}