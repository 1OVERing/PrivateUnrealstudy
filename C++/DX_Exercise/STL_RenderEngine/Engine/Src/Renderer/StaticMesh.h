#pragma once

#ifndef _STATIC_MESH_
#define _STATIC_MESH_

#include "Core.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Material.h"

namespace Ronnie
{
	class ENGINE_API SubMesh
	{
	public:

		void Initialize(ID3D11Device* device,
			void* vertices, uint32 vertexCount, uint32 vetexByteWidth,
			void* indices, uint32 indexCount);

		void Bind(ID3D11DeviceContext* context);
		void Draw(ID3D11DeviceContext* context);

		uint32 index;		// 서브메시 인덱스.
		VertexBuffer vertexBuffer;
		IndexBuffer indexBuffer;
	};

	class ENGINE_API StaticMesh
	{
	public:
		StaticMesh();
		~StaticMesh();

		void AddSubMesh(ID3D11Device* device,
			void* vertices, uint32 vertexCount, uint32 vetexByteWidth,
			void* indices, uint32 indexCount);

		void AddMaterial(Material* const newMaterial);
		void SetMaterial(Material* const newMaterial, uint32 index);
		Material& GetMaterial(uint32 index);

		void Initialize(ID3D11Device* device);
		void Bind(ID3D11DeviceContext* context);
		void Draw(ID3D11DeviceContext* context);

	private:
		std::vector<SubMesh*> meshes;
		std::vector<Material*> materials;
	};
}

#endif