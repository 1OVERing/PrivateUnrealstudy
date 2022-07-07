#pragma once

#ifndef _BASIC_SHADER_
#define _BASIC_SHADER_

#include "Core.h"
#include "Shader.h"
#include "Renderer/InputLayout.h"

namespace Ronnie
{
    class ENGINE_API DefaultShader : public Shader
    {
    public:
        DefaultShader();
        ~DefaultShader() = default;

        virtual void Initialize(ID3D11Device* device) override;
        virtual void Bind(ID3D11DeviceContext* deviceContext) override;

    private:
        InputLayout inputlayout;
    };
}
#endif