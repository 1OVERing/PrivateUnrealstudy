#pragma once

#ifndef _RENDER_TEXTURE_COMPONENT_
#define _RENDER_TEXTURE_COMPONENT_

#include "Core.h"
#include "Component/Component.h"

namespace Ronnie
{
	class RenderTextureComponent : public Component
	{
		RTTI_DECLARATIONS(RenderTextureComponent, Component)

	public:
		RenderTextureComponent();
		~RenderTextureComponent();

		// Component을(를) 통해 상속됨
		virtual void Initialize(ID3D11Device* device) override;
		virtual void Update(ID3D11DeviceContext* context, float deltaTime) override;
		virtual void Bind(ID3D11DeviceContext* context) override;

		void Clear(
			ID3D11DeviceContext* context,
			float r, float g, float b, float a
		);

		ID3D11ShaderResourceView* GetShaderResourceView();

	private:
		ID3D11Texture2D* renderTargetTexture;
		ID3D11RenderTargetView* renderTargetView;
		ID3D11ShaderResourceView* shaderResourceView;
	};
}

#endif