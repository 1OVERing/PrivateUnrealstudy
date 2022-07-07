#pragma once

#ifndef _MATERIAL_
#define _MATERIAL_

#include "Core.h"
#include "Shader/Shader.h"
#include "Texture.h"
#include "SamplerState.h"

namespace Ronnie
{
	// ��Ƽ���� = ���̴� + �Ķ����(�ؽ�ó, ��� ��...).
	class ENGINE_API Material
	{
	public:
		Material();
		Material(Shader* const shader);
		~Material();

		void Initialize(ID3D11Device* device);
		void Bind(ID3D11DeviceContext* context);
		
		void AddTexture(Texture* const newTexture);

		ID3DBlob* GetVertexShaderBuffer() 
		{
			// ���̴� �ڵ尡 �����ϵ� ���� ����Ʈ �ڵ� = ���̴� ����.
			return shader->GetVertexShaderBuffer(); 
		}

		ID3DBlob* GetPixelShaderBuffer()
		{
			return shader->GetPixelShaderBuffer();
		}

	private:
		uint32 index;
		Shader* shader;
		std::vector<Texture*> textures;
		SamplerState samplerState;
	};
}

#endif