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

		// FBX 파일 열어서 씬 읽어오기.
		std::unique_ptr<const aiScene> scene(ImportMesh(filename));

		// 예외처리.
		if (scene == nullptr)
		{
			throw std::exception("모델링 로드 실패.");
		}

		std::vector<MeshData*> meshDatas;

		// 루트 노드부터 처리.
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

		// 임포트 옵션.
		static const uint32 flags =
			aiProcess_Triangulate |		// 폴리곤을 삼각형으로.
			aiProcess_GenUVCoords |		// UV가 없는 경우 좌표 정보 생성.
			aiProcess_CalcTangentSpace |	// Tangent 공간 처리(노멀매핑에 필요).
			aiProcess_ConvertToLeftHanded;	// 왼손 좌표계로 변환.

		return aiImportFile(finalPath.string().c_str(), flags);
	}

	void ModelLoader::ProcessNode(ID3D11Device* device, aiNode* node, const aiScene* scene, StaticMesh** outMesh,
		const std::string& filename, std::vector<MeshData*>& meshDatas)
	{
		// 메쉬 처리.
		for (uint32 ix = 0; ix < node->mNumMeshes; ++ix)
		{
			const aiMesh* mesh = scene->mMeshes[node->mMeshes[ix]];
			ProcessMesh(device, mesh, scene, outMesh, filename, meshDatas);
		}

		// 노드 처리.
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
		// UV 데이터가 있는지 확인.
		if (mesh->HasTextureCoords(0) == true)
		{
			outUV.x = mesh->mTextureCoords[0][index].x;
			outUV.y = mesh->mTextureCoords[0][index].y;
		}
	}

	void LoadNormal(const aiMesh* mesh, uint32 index, Vector3f& outNormal)
	{
		// 노멀이 있는지 확인.
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
		std::vector<VertexPositionUVNormalBinormalTangent> vertices;	// 정점배열.
		std::vector<uint32> indices;					// 인덱스 배열.

		// 배열 공간 확보.
		vertices.reserve(static_cast<size_t>(mesh->mNumVertices));
		indices.reserve(
			static_cast<size_t>(mesh->mNumFaces * static_cast<size_t>(3))
		);

		// 정점 배열 데이터 채우기.
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

			// 정점 생성.
			VertexPositionUVNormalBinormalTangent vertex(position, uv, normal, binormal, tangent);

			// 정점 추가.
			vertices.emplace_back(vertex);
		}

		// 인덱스 배열 데이터 채우기.
		for (uint32 ix = 0; ix < mesh->mNumFaces; ++ix)
		{
			const aiFace& face = mesh->mFaces[ix];

			indices.emplace_back(face.mIndices[0]);
			indices.emplace_back(face.mIndices[1]);
			indices.emplace_back(face.mIndices[2]);
		}

		// 스태틱 메시에 서브 메시 추가.
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