#pragma once

#ifndef _NORMAL_MAPPING_SHADER_
#define _NORMAL_MAPPING_SHADER_

#include "Core.h"
#include "Shader.h"
#include "Renderer/InputLayout.h"

namespace Ronnie
{
    class ENGINE_API NormalMappingShader : public Shader
    {
    public:
        NormalMappingShader();
        ~NormalMappingShader() = default;

        virtual void Initialize(ID3D11Device* device) override;
        virtual void Bind(ID3D11DeviceContext* deviceContext) override;

    private:
        InputLayout inputlayout;
    };
}
#endif