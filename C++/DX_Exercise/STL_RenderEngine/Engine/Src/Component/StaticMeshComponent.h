#pragma once

#ifndef _STATIC_MESH_COMPONENT_
#define _STATIC_MESH_COMPONENT_

#include "Core.h"
#include "Component.h"
#include "Renderer/StaticMesh.h"

namespace Ronnie
{
	class ENGINE_API StaticMeshComponent : public Component
	{
		RTTI_DECLARATIONS(StaticMeshComponent, Component)

	public:
		StaticMeshComponent();
		~StaticMeshComponent();

		void AddSubMesh(ID3D11Device* device,
			void* vertices, uint32 vertexCount, uint32 vetexByteWidth,
			void* indices, uint32 indexCount);

		// 스태틱 메시 설정.
		void SetStaticMesh(StaticMesh* const staticMesh);

		void AddMaterial(Material* const newMaterial);
		void SetMaterial(Material* const newMaterial, uint32 index);
		Material& GetMaterial(uint32 index);

		virtual void Initialize(ID3D11Device* device) override;
		virtual void Update(ID3D11DeviceContext* context, float deltaTime) override;
		virtual void Bind(ID3D11DeviceContext* context) override;

		void Draw(ID3D11DeviceContext* context);

	private:
		StaticMesh* staticMesh;
	};
}

#endif