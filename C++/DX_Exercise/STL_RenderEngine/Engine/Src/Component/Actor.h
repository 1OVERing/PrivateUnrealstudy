#pragma once

#ifndef _ACTOR_
#define _ACTOR_

#include "Core.h"
#include "Component.h"

namespace Ronnie
{
	// 변수 및 파라미터 선언을 위한 전방 선언.
	class TransformComponent;
	class Vector3f;
	class ENGINE_API Actor
	{
	public:
		Actor(ID3D11Device* device, const std::wstring& name = TEXT("Actor"));
		virtual ~Actor();

		// 컴포넌트 추가/가져오기.
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

	// 액터(Actor)가 가진 컴포넌트를 타입으로 검색해서 반환하는 함수.
	// 검색에 성공하면 해당 컴포넌트 반환.
	// 검색에 실패(없으면)하면 nullptr 반환.
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