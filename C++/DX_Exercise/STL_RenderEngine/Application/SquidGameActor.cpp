#include "SquidGameActor.h"
#include "Util/ModelLoader.h"

Ronnie::SquidGameActor::SquidGameActor(
	ID3D11Device* device, 
	const std::wstring& name)
	: Actor(device, name)
{
	meshComponent = new StaticMeshComponent();
	StaticMesh* staticMesh = new StaticMesh();
	ModelLoader::LoadModel(device, "PinkSoldier_v01.fbx", &staticMesh);
	SetStaticMesh(staticMesh);
	AddComponent(meshComponent);
}

Ronnie::SquidGameActor::~SquidGameActor()
{
}

void Ronnie::SquidGameActor::SetStaticMesh(StaticMesh* staticMesh)
{
	meshComponent->SetStaticMesh(staticMesh);
}

void Ronnie::SquidGameActor::SetMaterial(Material* material1, Material* material2)
{
	meshComponent->AddMaterial(material1);
	meshComponent->AddMaterial(material1);
	meshComponent->AddMaterial(material1);
	meshComponent->AddMaterial(material1);
	meshComponent->AddMaterial(material1);
	meshComponent->AddMaterial(material1);

	meshComponent->AddMaterial(material2);
	meshComponent->AddMaterial(material2);
}

void Ronnie::SquidGameActor::Initialize(ID3D11Device* device)
{
	Actor::Initialize(device);
}

void Ronnie::SquidGameActor::Update(ID3D11DeviceContext* context, float deltaTime)
{
	Actor::Update(context, deltaTime);
}

void Ronnie::SquidGameActor::Render(ID3D11DeviceContext* context)
{
	Actor::Render(context);
}
