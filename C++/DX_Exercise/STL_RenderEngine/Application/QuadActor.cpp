#include "QuadActor.h"
#include "Renderer/VertexDeclaration.h"

namespace Ronnie
{
	QuadActor::QuadActor(ID3D11Device* device, const std::wstring& name)
		: Actor(device, name), meshComponent(nullptr)
	{
		meshComponent = new StaticMeshComponent();
		StaticMesh* staticMesh = new StaticMesh();

		VertexPositionUVNormal vertex0(
			Vector3f(-1.0f, 1.0f, 0.0f),
			Vector2f(0.0f, 0.0f),
			Vector3f(0.0f, 0.0f, -1.0f)
		);

		VertexPositionUVNormal vertex1(
			Vector3f(1.0f, 1.0f, 0.0f),
			Vector2f(1.0f, 0.0f),
			Vector3f(0.0f, 0.0f, -1.0f)
		);

		VertexPositionUVNormal vertex2(
			Vector3f(1.0f, -1.0f, 0.0f),
			Vector2f(1.0f, 1.0f),
			Vector3f(0.0f, 0.0f, -1.0f)
		);

		VertexPositionUVNormal vertex3(
			Vector3f(-1.0f, -1.0f, 0.0f),
			Vector2f(0.0f, 1.0f),
			Vector3f(0.0f, 0.0f, -1.0f)
		);

		std::vector<VertexPositionUVNormal> vertices({ vertex0, vertex1, vertex2, vertex3 });
		uint32 indices[] = { 0, 1, 2, 0, 2, 3 };

		staticMesh->AddSubMesh(
			device, 
			vertices.data(), vertices.size(), sizeof(vertices[0]),
			indices, 6
		);

		meshComponent->SetStaticMesh(staticMesh);
		AddComponent(meshComponent);
	}

	QuadActor::~QuadActor()
	{
	}

	void QuadActor::SetMaterial(Material* material)
	{
		meshComponent->AddMaterial(material);
	}

	void QuadActor::Initialize(ID3D11Device* device)
	{
		Actor::Initialize(device);
	}

	void QuadActor::Update(ID3D11DeviceContext* context, float deltaTime)
	{
		Actor::Update(context, deltaTime);
	}

	void QuadActor::Render(ID3D11DeviceContext* context)
	{
		Actor::Render(context);
	}
}