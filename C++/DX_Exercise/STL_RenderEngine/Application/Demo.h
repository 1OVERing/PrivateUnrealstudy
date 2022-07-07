#pragma once

#include "Core/Engine.h"
#include "Renderer/VertexDeclaration.h"
#include "Renderer/VertexBuffer.h"
#include "Shader/DefaultShader.h"
#include "Renderer/InputLayout.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Texture.h"
#include "Renderer/SamplerState.h"

#include "Renderer/ConstantBuffer.h"
#include "Math/Vector3f.h"
#include "Math/Matrix4f.h"
#include "Component/Actor.h"
#include "Renderer/Material.h"

#include "Renderer/Level.h"

namespace Ronnie
{
	class Demo : public Engine
	{
	public:
		Demo(HINSTANCE hInstance,
			uint32 width,
			uint32 height,
			const std::wstring& title)
			: Engine(hInstance, width, height, title)
		{
		}

		~Demo();

		virtual void Initialize() override;
		virtual void Update(float deltatTime) override;
		virtual void RenderScene() override;

	private:

		DefaultShader defaultShader;
		Material material;
		Level* mainLevel;
	};
}