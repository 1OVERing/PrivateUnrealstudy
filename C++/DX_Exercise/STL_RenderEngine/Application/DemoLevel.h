#pragma once

#include <Core.h>
#include <Renderer/Level.h>

#include <Renderer/Material.h>
#include <Shader/DefaultShader.h>
#include <Shader/DiffuseShader.h>
#include <Shader/SpecularShader.h>
#include <Shader/NormalMappingShader.h>
#include <Shader/MultiTextureShader.h>

#include <Renderer/Light.h>

namespace Ronnie
{
	class DemoLevel : public Level
	{
	public:
		DemoLevel();
		~DemoLevel();

		virtual void Initialize(ID3D11Device* device, Engine* const engine) override;
		virtual void Update(ID3D11DeviceContext* context, float deltaTime);
		virtual void Render(ID3D11DeviceContext* context);

	private:
		Material material;
		DefaultShader defaultShader;
		DiffuseShader diffuseShader;
		SpecularShader specularShader;
		NormalMappingShader normalMappingShader;
		MultiTextureShader multiTextureShader;

		Light light;
	};
}