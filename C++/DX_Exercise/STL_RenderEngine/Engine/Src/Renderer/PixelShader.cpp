#include "Core.h"
#include "PixelShader.h"
#include "Util/STLException.h"

namespace Ronnie
{
	PixelShader::PixelShader()
		: PixelShader(L"PixelShader", "main", "ps_5_0")
	{
	}

	PixelShader::PixelShader(const std::wstring& filename)
		: PixelShader(filename, "main", "ps_5_0")
	{
	}

	PixelShader::PixelShader(const std::wstring& filename, const std::string& entry, const std::string& profile)
		: ShaderBase(filename, entry, profile), pixelShader(nullptr)
	{
	}

	PixelShader::~PixelShader()
	{
		if (pixelShader != nullptr)
		{
			SafeRelease(pixelShader);
		}
	}

	void PixelShader::Initialize(ID3D11Device* device)
	{
		Compile(device);
		Create(device);
	}

	void PixelShader::Bind(ID3D11DeviceContext* context)
	{
		context->PSSetShader(pixelShader, nullptr, 0);
	}

	void PixelShader::Compile(ID3D11Device* device)
	{
		uint32 compileFlags = 0;
#if DEBUG | _DEBUG
		compileFlags |= D3DCOMPILE_DEBUG;
#endif
		// 쉐이더 파일 폴더 설정.
		auto folderPath = shaderFolderPath;
		auto finalPath = folderPath.append(filename.c_str() + std::wstring(L".cso"));

		//HRESULT hr = D3DCompileFromFile(
		//	finalPath.c_str(),
		//	nullptr,
		//	nullptr,
		//	entry.c_str(),
		//	profile.c_str(),
		//	compileFlags, 0,
		//	&shaderBuffer,
		//	nullptr
		//);

		HRESULT hr = D3DReadFileToBlob(finalPath.c_str(), &shaderBuffer);
		ThrowIfFailed(hr, "Failed to compile pixel shader.");
	}

	void PixelShader::Create(ID3D11Device* device)
	{
		HRESULT hr = device->CreatePixelShader(
			shaderBuffer->GetBufferPointer(),
			shaderBuffer->GetBufferSize(),
			nullptr, 
			&pixelShader
		);

		ThrowIfFailed(hr, "Failed to create pixel shader.");
	}
}