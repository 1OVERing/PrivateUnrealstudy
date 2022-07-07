#include "Core.h"
#include "SamplerState.h"
#include "Util/STLException.h"

namespace Ronnie
{
	SamplerState::SamplerState()
		: samplerState(nullptr)
	{
	}

	SamplerState::~SamplerState()
	{
		SafeRelease(samplerState);
	}

	void SamplerState::Initialize(ID3D11Device* device)
	{
		// 샘플러 스테이트 생성.
		D3D11_SAMPLER_DESC samplerDesc;
		memset(&samplerDesc, 0, sizeof(samplerDesc));
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

		HRESULT hr = device->CreateSamplerState(
			&samplerDesc, &samplerState
		);
		ThrowIfFailed(hr, "Failed to create sampler state.");
	}

	void SamplerState::Bind(ID3D11DeviceContext* context, uint32 index)
	{
		context->PSSetSamplers(index, 1, &samplerState);
	}
}