#pragma once

#ifndef _TRANSFORM_COMPONENT_
#define _TRANSFORM_COMPONENT_

#include "Core.h"
#include "Component.h"

#include "Math/Vector3f.h"
#include "Math/Matrix4f.h"

namespace Ronnie
{
	// 트랜스폼 정보를 담는 구조체 선언.
	struct Transform
	{
		Transform()
			: position(Vector3f::Zero),
			  rotation(Vector3f::Zero),
			  scale(Vector3f::One)
		{
		}

		Vector3f position;
		Vector3f rotation;
		Vector3f scale;
	};

	class ENGINE_API TransformComponent : public Component
	{
		// RTTI 선언.
		RTTI_DECLARATIONS(TransformComponent, Component)

	public:
		TransformComponent();
		~TransformComponent();

		virtual void Initialize(ID3D11Device* device) override;
		virtual void Update(
			ID3D11DeviceContext* context, float deltaTime) override;
		virtual void Bind(ID3D11DeviceContext* context) override;

		// Getter/Setter.

		Vector3f Forward() const;
		Vector3f Right() const;
		Vector3f Up() const;

		// 위치 Get/Set.
		void SetPosition(float x, float y, float z);
		void SetPosition(const Vector3f& position);
		Vector3f Position() const;

		// 회전 Get/Set.
		void SetRotation(float x, float y, float z);
		void SetRotation(const Vector3f& position);
		Vector3f Rotation() const;

		// 스케일 Get/Set.
		void SetScale(float x, float y, float z);
		void SetScale(const Vector3f& position);
		Vector3f Scale() const;

		Matrix4f transformMatrix;

	private:

		void SetDirty();

		Transform transform;
		ID3D11Buffer* transformBuffer;

		bool isDirty;			// 데이터 변경이 있는 경우 true로 설정.

	};
}

#endif