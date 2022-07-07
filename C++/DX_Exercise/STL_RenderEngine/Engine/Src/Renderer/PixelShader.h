#pragma once

#ifndef _PIXEL_SHADER_
#define _PIXEL_SHADER_

#include "Core.h"
#include "ShaderBase.h"

namespace Ronnie
{
	class ENGINE_API PixelShader : public ShaderBase
	{
	public:
		PixelShader();
		PixelShader(const std::wstring& filename);
		PixelShader(const std::wstring& filename, const std::string& entry, const std::string& profile);
		~PixelShader();

		void Initialize(ID3D11Device* device);
		void Bind(ID3D11DeviceContext* context);

		ID3D11PixelShader* Get() { return pixelShader; }
		ID3D11PixelShader** GetAddressOf() { return &pixelShader; }

	protected:
		void Compile(ID3D11Device* device) override;
		void Create(ID3D11Device* device) override;

	private:
		ID3D11PixelShader* pixelShader;
	};
}
#endif