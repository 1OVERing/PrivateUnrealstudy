#pragma once

#ifndef _COMPONENT_
#define _COMPONENT_

#include "Core.h"
#include "RTTI.h"

namespace Ronnie
{
	// ���� ����.
	class Actor;
	class TransformComponent;

	// ������Ʈ�� �ֻ��� ����.
	class ENGINE_API Component : public RTTI
	{
		// RTTI ����.
		RTTI_DECLARATIONS(Component, RTTI)

	public:
		Component();
		virtual ~Component();

		// ���� ���� �Լ�
		// -> �ڽ� Ŭ������ �� �Լ��� �� �����ϵ��� �����ϴ� ����.
		virtual void Initialize(ID3D11Device* device) = 0;
		virtual void Update(ID3D11DeviceContext* context, float deltaTime) = 0;
		virtual void Bind(ID3D11DeviceContext* context) = 0;

		// ����.
		virtual void SetActor(Actor* actor);
		virtual const Actor* GetOwnerActor() const 
		{ return ownerActor; }

	protected:
		// �� ������Ʈ�� �����ϴ� ����(�⺻ ��ü) ����.
		Actor* ownerActor;
		// �� ������Ʈ�� ���� ������ ���� Ʈ������ ������Ʈ ����.
		TransformComponent* transform;
	};
}

#endif