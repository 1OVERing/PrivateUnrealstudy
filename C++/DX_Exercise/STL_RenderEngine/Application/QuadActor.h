#pragma once

#include "Core.h"
#include "Component/Actor.h"
#include "Component/StaticMeshComponent.h"
#include "Renderer/Material.h"
#include "Renderer/StaticMesh.h"

namespace Ronnie
{
	class QuadActor : public Actor
	{
	public:
		QuadActor(ID3D11Device* device, const std::wstring& name = L"Quad Actor");
		~QuadActor();

		void SetMaterial(Material* material);

		virtual void Initialize(ID3D11Device* device) override;
		virtual void Update(ID3D11DeviceContext* context, float deltaTime) override;
		virtual void Render(ID3D11DeviceContext* context) override;

	private:
		StaticMeshComponent* meshComponent;
	};
}