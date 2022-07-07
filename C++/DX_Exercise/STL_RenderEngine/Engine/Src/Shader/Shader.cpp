#include "Core.h"
#include "Shader.h"

namespace Ronnie
{
	Shader::Shader(const std::wstring& filename)
		: vertexShader(filename), pixelShader(filename)
	{
	}

	Shader::Shader(const std::wstring& filename, const std::string& entry)
		: vertexShader(filename, entry, "vs_5_0"), pixelShader(filename, entry, "ps_5_0")
	{
	}

	void Shader::Initialize(ID3D11Device* device)
	{
		vertexShader.Initialize(device);
		pixelShader.Initialize(device);
	}

	void Shader::Bind(ID3D11DeviceContext* deviceContext)
	{
		vertexShader.Bind(deviceContext);
		pixelShader.Bind(deviceContext);
	}
}
