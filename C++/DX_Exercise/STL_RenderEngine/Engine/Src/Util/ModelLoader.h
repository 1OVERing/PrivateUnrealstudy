#pragma once

#ifndef _MODEL_LOADER_
#define _MODEL_LOADER_

#include "Core.h"

// Assimp ���̺귯�� ���.
#include <Importer.hpp>
#include <cimport.h>
#include <postprocess.h>
#include <scene.h>

#include "Math/Vector3f.h"
#include "Math/Vector2f.h"
#include "Renderer/VertexDeclaration.h"
#include "Renderer/StaticMesh.h"

namespace Ronnie
{
	class ENGINE_API ModelLoader
	{
	private:
		class ENGINE_API MeshData
		{
		public:
			MeshData() = default;
			~MeshData()
			{
				vertices.~vector();
				indices.~vector();
			}

			std::vector<VertexPositionUVNormalBinormalTangent> vertices;
			std::vector<uint32> indices;
		};

	public:
		static std::unordered_map<std::string, std::vector<MeshData*>> modelMap;

		// �޽� �ε�.
		static void LoadModel(
			ID3D11Device* device,
			const std::string& filename,
			StaticMesh** outMesh
		);

		static void Release();

	private:
		static const aiScene* ImportMesh(const std::string& filename);
		static void ProcessNode(
			ID3D11Device* device,
			aiNode* node,
			const aiScene* scene,
			StaticMesh** outMesh, const std::string& filename, std::vector<MeshData*>& meshDatas
		);
		static void ProcessMesh(
			ID3D11Device* device,
			const aiMesh* mesh,
			const aiScene* scene,
			StaticMesh** outMesh, const std::string& filename, std::vector<MeshData*>& meshDatas
		);
	};
}
#endif