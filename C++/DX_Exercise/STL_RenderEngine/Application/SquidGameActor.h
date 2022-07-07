#pragma once

#ifndef _SQUID_GAME_ACTOR_
#define _SQUID_GAME_ACTOR_

#include "Core.h"
#include "Component/Actor.h"
#include "Component/StaticMeshComponent.h"
#include "Renderer/Material.h"
#include "Renderer/StaticMesh.h"

namespace Ronnie
{
	class SquidGameActor : public Actor
	{
	public:
		SquidGameActor(
			ID3D11Device* device,
			const std::wstring& name = L"SquidGame Actor"
		);

		~SquidGameActor();

		void SetStaticMesh(StaticMesh* staticMesh);
		void SetMaterial(Material* material1, Material* material2);

		virtual void Initialize(ID3D11Device* device) override;
		virtual void Update(ID3D11DeviceContext* context, float deltaTime) override;
		virtual void Render(ID3D11DeviceContext* context) override;

	private:
		StaticMeshComponent* meshComponent;
	};
}

#endif