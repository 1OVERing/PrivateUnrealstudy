#include "Core.h"
#include "VertexShader.h"
#include "Util/STLException.h"

namespace Ronnie
{
	VertexShader::VertexShader()
		: VertexShader(L"VertexShader", "main", "vs_5_0")
	{
	}

	VertexShader::VertexShader(const std::wstring& filename)
		: VertexShader(filename, "main", "vs_5_0")
	{
	}

	VertexShader::VertexShader(const std::wstring& filename, const std::string& entry, const std::string& profile)
		: ShaderBase(filename, entry, profile), vertexShader(nullptr)
	{
	}

	VertexShader::~VertexShader()
	{	
		SafeRelease(vertexShader);
	}

	void VertexShader::Initialize(ID3D11Device* device)
	{
		Compile(device);
		Create(device);
	}

	void VertexShader::Bind(ID3D11DeviceContext* context)
	{
		context->VSSetShader(vertexShader, nullptr, 0);
	}

	void VertexShader::Compile(ID3D11Device* device)
	{
		uint32 compileFlags = 0;
#if DEBUG | _DEBUG
		compileFlags |= D3DCOMPILE_DEBUG;
#endif
		// 쉐이더 파일 폴더 설정.
		auto folderPath = shaderFolderPath;
		auto finalPath = folderPath.append(filename.c_str() + std::wstring(L".cso"));

		//ID3DBlob* errorBlob = nullptr;

		//HRESULT hr = D3DCompileFromFile(
		//	finalPath.c_str(),
		//	nullptr, 
		//	nullptr, 
		//	entry.c_str(), 
		//	profile.c_str(), 
		//	compileFlags, 0,
		//	&shaderBuffer, 
		//	nullptr
		//	//&errorBlob
		//);

		HRESULT hr = D3DReadFileToBlob(finalPath.c_str(), &shaderBuffer);

		//if (errorBlob != nullptr)
		//{
		//	auto errorMessage 
		//		= static_cast<const char*>(errorBlob->GetBufferPointer());

		//	MessageBoxA(nullptr, errorMessage, "Error", MB_OK);
		//}

		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "Error", "Error", MB_OK);
		}
		
		ThrowIfFailed(hr, "Failed to compile vertex shader.");
	}

	void VertexShader::Create(ID3D11Device* device)
	{
		HRESULT hr = device->CreateVertexShader(
			shaderBuffer->GetBufferPointer(), 
			shaderBuffer->GetBufferSize(),
			nullptr, 
			&vertexShader
		);

		ThrowIfFailed(hr, "Failed to create vertex shader.");
	}
}