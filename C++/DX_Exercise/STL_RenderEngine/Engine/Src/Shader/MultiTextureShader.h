#pragma once

#ifndef _MULTI_TEXTURE_SHADER_
#define _MULTI_TEXTURE_SHADER_

#include "Core.h"
#include "Shader.h"
#include "Renderer/InputLayout.h"

namespace Ronnie
{
	class ENGINE_API MultiTextureShader : public Shader
	{
    public:
        MultiTextureShader();
        ~MultiTextureShader() = default;

        virtual void Initialize(ID3D11Device * device) override;
        virtual void Bind(ID3D11DeviceContext * deviceContext) override;

    private:
        InputLayout inputlayout;
	};
}

#endif