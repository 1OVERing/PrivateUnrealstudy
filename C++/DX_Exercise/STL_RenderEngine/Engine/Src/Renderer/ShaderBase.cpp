#include "Core.h"
#include "ShaderBase.h"

namespace Ronnie
{
	ShaderBase::ShaderBase(const std::wstring& filename, const std::string& entry, const std::string& profile)
		: filename(filename), entry(entry), profile(profile), shaderBuffer(nullptr)
	{
		shaderFolderPath 
			= std::filesystem::current_path().parent_path().append(TEXT("Shader"));
	}
	
	ShaderBase::~ShaderBase()
	{
		SafeRelease(shaderBuffer);
	}
}