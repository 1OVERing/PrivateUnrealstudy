#pragma once

#ifndef _VERTEX_SHADER_
#define _VERTEX_SHADER_

#include "Core.h"
#include "ShaderBase.h"

namespace Ronnie
{
	class ENGINE_API VertexShader : public ShaderBase
	{
	public:
		VertexShader();
		VertexShader(const std::wstring& filename);
		VertexShader(const std::wstring& filename, const std::string& entry, const std::string& profile);
		~VertexShader();

		void Initialize(ID3D11Device* device);
		void Bind(ID3D11DeviceContext* context);

		ID3D11VertexShader* Get() { return vertexShader; }
		ID3D11VertexShader** GetAddressOf() { return &vertexShader; }

	protected:
		void Compile(ID3D11Device* device) override;
		void Create(ID3D11Device* device) override;

	private:
		ID3D11VertexShader* vertexShader;
	};
}
#endif