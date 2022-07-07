#pragma once

#ifndef _Shader_Base_
#define _Shader_Base_

#include "Core.h"

namespace Ronnie
{
	class ENGINE_API ShaderBase
	{
	public:
		ShaderBase(const std::wstring& filename, const std::string& entry, const std::string& profile);
		virtual ~ShaderBase();

		ID3DBlob* ShaderBuffer() { return shaderBuffer; }

	protected:

		virtual void Compile(ID3D11Device* device) = 0;
		virtual void Create(ID3D11Device* device) = 0;

		std::wstring filename;
		std::string entry;
		std::string profile;

		ID3DBlob* shaderBuffer;

		std::filesystem::path shaderFolderPath;
	};
}
#endif