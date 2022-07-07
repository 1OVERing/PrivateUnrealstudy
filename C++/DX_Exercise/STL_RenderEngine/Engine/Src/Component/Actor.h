#pragma once

#ifndef _ACTOR_
#define _ACTOR_

#include "Core.h"
#include "Component.h"

namespace Ronnie
{
	// ���� �� �Ķ���� ������ ���� ���� ����.
	class TransformComponent;
	class Vector3f;
	class ENGINE_API Actor
	{
	public:
		Actor(ID3D11Device* device, const std::wstring& name = TEXT("Actor"));
		virtual ~Actor();

		// ������Ʈ �߰�/��������.
		void AddComponent(Component* component);
		
		template<typename T>
		T* GetComponent();

		virtual void Initialize(ID3D11Device* device);
		virtual void Update(ID3D11DeviceContext* context, float deltaTime);
		virtual void Render(ID3D11DeviceContext* context);

		const std::vector<Component*> Components() const 
		{ 
			return components; 
		}

		std::unique_ptr<TransformComponent> transform;

		void SetPosition(float x, float y, float z);
		void SetPosition(const Vector3f& position);
		Vector3f Position() const;

		void SetRotation(float x, float y, float z);
		void SetRotation(const Vector3f& rotation);
		Vector3f Rotation() const;

		void SetScale(float x, float y, float z);
		void SetScale(const Vector3f& scale);
		Vector3f Scale() const;

		std::wstring GetName() const { return name; }
		void SetName(const std::wstring& name) { this->name = name; }

	protected:
		std::vector<Component*> components;
		std::wstring name;
	};

	// ����(Actor)�� ���� ������Ʈ�� Ÿ������ �˻��ؼ� ��ȯ�ϴ� �Լ�.
	// �˻��� �����ϸ� �ش� ������Ʈ ��ȯ.
	// �˻��� ����(������)�ϸ� nullptr ��ȯ.
	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto component : components)
		{
			T* t = component->As<T>();
			if (t != nullptr)
			{
				return t;
			}
		}

		return nullptr;
	}
}

#endif