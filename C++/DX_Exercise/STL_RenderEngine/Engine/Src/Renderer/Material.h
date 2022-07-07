#pragma once

#ifndef _MATERIAL_
#define _MATERIAL_

#include "Core.h"
#include "Shader/Shader.h"
#include "Texture.h"
#include "SamplerState.h"

namespace Ronnie
{
	// 머티리얼 = 쉐이더 + 파라미터(텍스처, 상수 값...).
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
			// 쉐이더 코드가 컴파일된 후의 바이트 코드 = 쉐이더 버퍼.
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