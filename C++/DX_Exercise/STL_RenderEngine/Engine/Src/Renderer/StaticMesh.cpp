#include "Core.h"
#include "StaticMesh.h"

#include <cassert>

#include "Util/Logger.h"

namespace Ronnie
{
	void SubMesh::Initialize(ID3D11Device* device, 
		void* vertices, uint32 vertexCount, uint32 vetexByteWidth, 
		void* indices, uint32 indexCount)
	{
		vertexBuffer.Initialize(
			device, vertices, vertexCount, vetexByteWidth
		);

		indexBuffer.Initialize(
			device, indices, indexCount, sizeof(uint32)
		);
	}

	void SubMesh::Bind(ID3D11DeviceContext* context)
	{
		// 토폴로지 설정.
		context->IASetPrimitiveTopology(
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
		);

		// 정점/색인 버퍼 바인딩.
		vertexBuffer.Bind(context);
		indexBuffer.Bind(context);
	}

	// 리소스 생성/데이터 업데이트/바인딩/그리기.
	void SubMesh::Draw(ID3D11DeviceContext* context)
	{
		indexBuffer.Draw(context);
	}

	// ------- Static Mesh ------- // 
	StaticMesh::StaticMesh()
	{
	}

	StaticMesh::~StaticMesh()
	{
		for (auto mesh : meshes)
		{
			SafeDelete(mesh);
		}
	}

	void StaticMesh::AddSubMesh(ID3D11Device* device, 
		void* vertices, uint32 vertexCount, uint32 vetexByteWidth, 
		void* indices, uint32 indexCount)
	{
		// 서브 메시 생성.
		SubMesh* mesh = new SubMesh();
		mesh->Initialize(device,
			vertices, vertexCount, vetexByteWidth,
			indices, indexCount);

		// 메시의 인덱스 설정.
		mesh->index = static_cast<uint32>(meshes.size());

		// 생성한 메시 추가.
		meshes.emplace_back(mesh);
	}

	void StaticMesh::AddMaterial(Material* const newMaterial)
	{
		materials.emplace_back(newMaterial);
	}

	void StaticMesh::SetMaterial(Material* const newMaterial, uint32 index)
	{
		if (index < materials.size())
		{
			materials[index] = newMaterial;
		}
	}

	Material& StaticMesh::GetMaterial(uint32 index)
	{
		if (index >= materials.size())
		{
			throw std::exception("There's no material with this index.");
		}

		return *materials[index];
	}

	void StaticMesh::Initialize(ID3D11Device* device)
	{
		for (auto material : materials)
		{
			material->Initialize(device);
		}
	}

	void StaticMesh::Bind(ID3D11DeviceContext* context)
	{
	}

	void StaticMesh::Draw(ID3D11DeviceContext* context)
	{
		/*for (auto const mesh : meshes)*/
		for (uint32 ix = 0; ix < meshes.size(); ++ix)
		{
			auto mesh = meshes[ix];

			// 머티리얼 바인딩.
			if (ix < materials.size())
			{
				materials[ix]->Bind(context);
			}

			// 정점/색인 버퍼 바인딩.
			mesh->Bind(context);

			// 드로우 콜.
			mesh->Draw(context);
		}
	}
}