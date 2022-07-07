#include "Core.h"
#include "ModelLoader.h"
#include <DirectXTex.h>
#include "Util/STLException.h"

#include "Logger.h"

namespace Ronnie
{
	std::unordered_map<std::string, std::vector<ModelLoader::MeshData*>> ModelLoader::modelMap;

	void ModelLoader::LoadModel(ID3D11Device* device,
		const std::string& filename, StaticMesh** outMesh)
	{
		auto search = modelMap.find(filename);
		if (search != modelMap.end())
		{
			for (auto mesh : search->second)
			{
				(*outMesh)->AddSubMesh(device,
					mesh->vertices.data(), static_cast<uint32>(mesh->vertices.size()), sizeof(mesh->vertices[0]),
					mesh->indices.data(), static_cast<uint32>(mesh->indices.size()));
			}

			return;
		}

		// FBX ���� ��� �� �о����.
		std::unique_ptr<const aiScene> scene(ImportMesh(filename));

		// ����ó��.
		if (scene == nullptr)
		{
			throw std::exception("�𵨸� �ε� ����.");
		}

		std::vector<MeshData*> meshDatas;

		// ��Ʈ ������ ó��.
		ProcessNode(device, scene->mRootNode, scene.get(), outMesh, filename, meshDatas);

		modelMap.insert({ filename, meshDatas });
	}

	void ModelLoader::Release()
	{
		for (auto pair : modelMap)
		{
			if (pair.second.size() > 0)
			{
				for (auto model : pair.second)
				{
					SafeDelete(model);
				}
			}
		}
	}

	const aiScene* ModelLoader::ImportMesh(const std::string& filename)
	{
		auto finalPath = std::filesystem::current_path().parent_path();
		finalPath /= "Content\\Models";
		finalPath /= filename;

		// ����Ʈ �ɼ�.
		static const uint32 flags =
			aiProcess_Triangulate |		// �������� �ﰢ������.
			aiProcess_GenUVCoords |		// UV�� ���� ��� ��ǥ ���� ����.
			aiProcess_CalcTangentSpace |	// Tangent ���� ó��(��ָ��ο� �ʿ�).
			aiProcess_ConvertToLeftHanded;	// �޼� ��ǥ��� ��ȯ.

		return aiImportFile(finalPath.string().c_str(), flags);
	}

	void ModelLoader::ProcessNode(ID3D11Device* device, aiNode* node, const aiScene* scene, StaticMesh** outMesh,
		const std::string& filename, std::vector<MeshData*>& meshDatas)
	{
		// �޽� ó��.
		for (uint32 ix = 0; ix < node->mNumMeshes; ++ix)
		{
			const aiMesh* mesh = scene->mMeshes[node->mMeshes[ix]];
			ProcessMesh(device, mesh, scene, outMesh, filename, meshDatas);
		}

		// ��� ó��.
		for (uint32 ix = 0; ix < node->mNumChildren; ++ix)
		{
			ProcessNode(device, node->mChildren[ix], scene, outMesh, filename, meshDatas);
		}
	}

	void LoadPosition(const aiMesh* mesh, uint32 index, Vector3f& outPosition)
	{
		outPosition.x = mesh->mVertices[index].x;
		outPosition.y = mesh->mVertices[index].y;
		outPosition.z = mesh->mVertices[index].z;
	}

	void LoadUV(const aiMesh* mesh, uint32 index, Vector2f& outUV)
	{
		// UV �����Ͱ� �ִ��� Ȯ��.
		if (mesh->HasTextureCoords(0) == true)
		{
			outUV.x = mesh->mTextureCoords[0][index].x;
			outUV.y = mesh->mTextureCoords[0][index].y;
		}
	}

	void LoadNormal(const aiMesh* mesh, uint32 index, Vector3f& outNormal)
	{
		// ����� �ִ��� Ȯ��.
		if (mesh->HasNormals() == true)
		{
			outNormal.x = mesh->mNormals[index].x;
			outNormal.y = mesh->mNormals[index].y;
			outNormal.z = mesh->mNormals[index].z;
		}
	}

	void LoadBinormalAndTangent(const aiMesh* mesh, uint32 index, Vector3f& outBinormal, Vector3f& outTangent)
	{
		if (mesh->HasTangentsAndBitangents() == true)
		{
			outBinormal.x = mesh->mBitangents[index].x;
			outBinormal.y = mesh->mBitangents[index].y;
			outBinormal.z = mesh->mBitangents[index].z;

			outTangent.x = mesh->mTangents[index].x;
			outTangent.y = mesh->mTangents[index].y;
			outTangent.z = mesh->mTangents[index].z;
		}
	}

	void ModelLoader::ProcessMesh(ID3D11Device* device,
		const aiMesh* mesh, const aiScene* scene, StaticMesh** outMesh, const std::string& filename,
		std::vector<MeshData*>& meshDatas)
	{
		std::vector<VertexPositionUVNormalBinormalTangent> vertices;	// �����迭.
		std::vector<uint32> indices;					// �ε��� �迭.

		// �迭 ���� Ȯ��.
		vertices.reserve(static_cast<size_t>(mesh->mNumVertices));
		indices.reserve(
			static_cast<size_t>(mesh->mNumFaces * static_cast<size_t>(3))
		);

		// ���� �迭 ������ ä���.
		for (uint32 ix = 0; ix < mesh->mNumVertices; ++ix)
		{
			Vector3f position;
			//Vector3f color;
			Vector2f uv;
			Vector3f normal;
			Vector3f binormal;
			Vector3f tangent;

			LoadPosition(mesh, ix, position);
			LoadUV(mesh, ix, uv);
			LoadNormal(mesh, ix, normal);
			LoadBinormalAndTangent(mesh, ix, binormal, tangent);

			// ���� ����.
			VertexPositionUVNormalBinormalTangent vertex(position, uv, normal, binormal, tangent);

			// ���� �߰�.
			vertices.emplace_back(vertex);
		}

		// �ε��� �迭 ������ ä���.
		for (uint32 ix = 0; ix < mesh->mNumFaces; ++ix)
		{
			const aiFace& face = mesh->mFaces[ix];

			indices.emplace_back(face.mIndices[0]);
			indices.emplace_back(face.mIndices[1]);
			indices.emplace_back(face.mIndices[2]);
		}

		// ����ƽ �޽ÿ� ���� �޽� �߰�.
		(*outMesh)->AddSubMesh(
			device,
			vertices.data(), static_cast<uint32>(vertices.size()), sizeof(vertices[0]),
			indices.data(), static_cast<uint32>(indices.size())
		);

		MeshData* newMesh = new MeshData();
		newMesh->vertices.assign(vertices.begin(), vertices.end());
		newMesh->indices.assign(indices.begin(), indices.end());
		meshDatas.emplace_back(newMesh);
	}
}