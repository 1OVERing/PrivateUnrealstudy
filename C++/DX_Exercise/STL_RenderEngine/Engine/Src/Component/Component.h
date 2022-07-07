#pragma once

#ifndef _COMPONENT_
#define _COMPONENT_

#include "Core.h"
#include "RTTI.h"

namespace Ronnie
{
	// 전방 선언.
	class Actor;
	class TransformComponent;

	// 컴포넌트의 최상위 계층.
	class ENGINE_API Component : public RTTI
	{
		// RTTI 선언.
		RTTI_DECLARATIONS(Component, RTTI)

	public:
		Component();
		virtual ~Component();

		// 순수 가상 함수
		// -> 자식 클래스가 이 함수를 꼭 구현하도록 강제하는 목적.
		virtual void Initialize(ID3D11Device* device) = 0;
		virtual void Update(ID3D11DeviceContext* context, float deltaTime) = 0;
		virtual void Bind(ID3D11DeviceContext* context) = 0;

		// 설정.
		virtual void SetActor(Actor* actor);
		virtual const Actor* GetOwnerActor() const 
		{ return ownerActor; }

	protected:
		// 이 컴포넌트를 소유하는 액터(기본 물체) 정보.
		Actor* ownerActor;
		// 이 컴포넌트와 같은 계층에 속한 트랜스폼 컴포넌트 정보.
		TransformComponent* transform;
	};
}

#endif