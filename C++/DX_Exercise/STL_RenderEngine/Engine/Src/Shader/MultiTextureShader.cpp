#include "Core.h"
#include "MultiTextureShader.h"

namespace Ronnie
{
	MultiTextureShader::MultiTextureShader()
		: Shader()
	{
		vertexShader = VertexShader(TEXT("MultiTextureVertexShader"));
		pixelShader = PixelShader(TEXT("MultiTexturePixelShader"));
	}

	void MultiTextureShader::Initialize(ID3D11Device* device)
	{
		Shader::Initialize(device);

		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		inputlayout.Initialize(
			device, layout, ARRAYSIZE(layout),
			vertexShader.ShaderBuffer()
		);
	}

	void MultiTextureShader::Bind(ID3D11DeviceContext* deviceContext)
	{
		Shader::Bind(deviceContext);
		inputlayout.Bind(deviceContext);
	}
}