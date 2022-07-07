#include "Core.h"
#include "StaticMeshComponent.h"

namespace Ronnie
{
	RTTI_DEFINITIONS(StaticMeshComponent)

	StaticMeshComponent::StaticMeshComponent()
		: staticMesh(nullptr)
	{
	}

	StaticMeshComponent::~StaticMeshComponent()
	{
		SafeDelete(staticMesh);
	}

	void StaticMeshComponent::AddSubMesh(
		ID3D11Device* device, 
		void* vertices, uint32 vertexCount, uint32 vertexByteWidth, 
		void* indices, uint32 indexCount)
	{
		if (staticMesh == nullptr)
		{
			staticMesh = new StaticMesh();
		}

		staticMesh->AddSubMesh(
			device, 
			vertices, vertexCount, vertexByteWidth,
			indices, indexCount
		);
	}

	void StaticMeshComponent::SetStaticMesh(StaticMesh* const staticMesh)
	{
		this->staticMesh = staticMesh;
	}

	void StaticMeshComponent::AddMaterial(Material* const newMaterial)
	{
		staticMesh->AddMaterial(newMaterial);
	}

	void StaticMeshComponent::SetMaterial(
		Material* const newMaterial, uint32 index)
	{
		staticMesh->SetMaterial(newMaterial, index);
	}

	Material& StaticMeshComponent::GetMaterial(uint32 index)
	{
		return staticMesh->GetMaterial(index);
	}

	void StaticMeshComponent::Initialize(ID3D11Device* device)
	{
		staticMesh->Initialize(device);
	}

	void StaticMeshComponent::Update(
		ID3D11DeviceContext* context, float deltaTime)
	{
	}

	void StaticMeshComponent::Bind(ID3D11DeviceContext* context)
	{
		staticMesh->Bind(context);
	}
	
	void StaticMeshComponent::Draw(ID3D11DeviceContext* context)
	{
		staticMesh->Draw(context);
	}
}