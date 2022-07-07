#include "Core.h"
#include "Actor.h"
#include "Component/TransformComponent.h"
#include "Math/Vector3f.h"
#include <Component\StaticMeshComponent.h>

#include "Util/Logger.h"

namespace Ronnie
{
	Actor::Actor(ID3D11Device* device, const std::wstring& name)
		: name(name)
	{
		// Ʈ������ ������Ʈ ����.
		transform = std::make_unique<TransformComponent>();
		transform->Initialize(device);
	}

	Actor::~Actor()
	{
		for (auto component : components)
		{
			SafeDelete(component);
		}
	}

	void Actor::AddComponent(Component* component)
	{
		// �߰��Ǵ� ������Ʈ�� ������(Owner) ���� ����.
		component->SetActor(this);

		// ������Ʈ �迭�� ������Ʈ �߰�.
		components.emplace_back(component);
	}

	void Actor::Initialize(ID3D11Device* device)
	{
		//transform->Initialize(device);
		for (const auto& component : components)
		{
			component->Initialize(device);
		}
	}

	void Actor::Update(ID3D11DeviceContext* context, float deltaTime)
	{
		transform->Update(context, deltaTime);

		for (const auto& component : components)
		{
			component->Update(context, deltaTime);
		}
	}

	void Actor::Render(ID3D11DeviceContext* context)
	{
		transform->Bind(context);

		// Todo: ���߿� MeshComponent�� �߰��Ǹ� �ۼ� ����.
		for (auto component : components)
		{
			// ����ȯ.
			StaticMeshComponent* meshComponent 
				= component->As<StaticMeshComponent>();
			
			if (meshComponent != nullptr)
			{
				meshComponent->Bind(context);
				meshComponent->Draw(context);
			}
		}
	}

	void Actor::SetPosition(float x, float y, float z)
	{
		transform->SetPosition(x, y, z);
	}

	void Actor::SetPosition(const Vector3f& position)
	{
		transform->SetPosition(position);
	}

	Vector3f Actor::Position() const
	{
		return transform->Position();
	}

	void Actor::SetRotation(float x, float y, float z)
	{
		transform->SetRotation(x, y, z);
	}

	void Actor::SetRotation(const Vector3f& rotation)
	{
		transform->SetRotation(rotation);
	}

	Vector3f Actor::Rotation() const
	{
		return transform->Rotation();
	}

	void Actor::SetScale(float x, float y, float z)
	{
		transform->SetScale(x, y, z);
	}

	void Actor::SetScale(const Vector3f& scale)
	{
		transform->SetScale(scale);
	}

	Vector3f Actor::Scale() const
	{
		return transform->Scale();
	}
}