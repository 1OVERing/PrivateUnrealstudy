#pragma once

#ifndef _DIFFUSE_SHADER_
#define _DIFFUSE_SHADER_

#include "Core.h"
#include "Shader.h"
#include "Renderer/InputLayout.h"

namespace Ronnie
{
    class ENGINE_API DiffuseShader : public Shader
    {
    public:
        DiffuseShader();
        ~DiffuseShader() = default;

        virtual void Initialize(ID3D11Device* device) override;
        virtual void Bind(ID3D11DeviceContext* deviceContext) override;

    private:
        InputLayout inputlayout;
    };
}
#endif