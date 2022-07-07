#pragma once

#ifndef _SPECULAR_SHADER_
#define _SPECULAR_SHADER_

#include "Core.h"
#include "Shader.h"
#include "Renderer/InputLayout.h"

namespace Ronnie
{
    class ENGINE_API SpecularShader : public Shader
    {
    public:
        SpecularShader();
        ~SpecularShader() = default;

        virtual void Initialize(ID3D11Device* device) override;
        virtual void Bind(ID3D11DeviceContext* deviceContext) override;

    private:
        InputLayout inputlayout;
    };
}
#endif