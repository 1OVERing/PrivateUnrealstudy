#pragma once

#ifndef _LEVEL_
#define _LEVEL_

#include "Core.h"

namespace Ronnie
{
	class Actor;

	class Material;
	class StaticMesh;

	class ENGINE_API Level
	{
	public:
		Level();
		virtual ~Level();

		virtual void Initialize(ID3D11Device* device, class Engine* const engine);
		virtual void Update(ID3D11DeviceContext* context, float deltaTime);
		virtual void Render(ID3D11DeviceContext* context);

		void AddActor(Actor* const newActor);

	protected:
		std::vector<Actor*> actors;

		void AddMaterial(Material* material);
		void AddMesh(StaticMesh* mesh);

		std::vector<Material*> materials;
		//std::vector<StaticMesh*> meshes;

		// 메인 카메라.
		Actor* mainCamera;

		class Engine* engine;
	};
}

#endif