#pragma once

#ifndef _SAMPLER_STATE_
#define _SAMPLER_STATE_

#include "Core.h"

namespace Ronnie
{
	class ENGINE_API SamplerState
	{
	public:
		SamplerState();
		~SamplerState();

		void Initialize(ID3D11Device* device);
		void Bind(ID3D11DeviceContext* context, uint32 index);

		ID3D11SamplerState* Get() { return samplerState; }
		ID3D11SamplerState** GetAddressOf() { return &samplerState; }

	private:
		ID3D11SamplerState* samplerState;
	};
}
#endif