#include "CameraController.h"

#include "Math/Vector3f.h"
#include "Component/TransformComponent.h"

#include <Core/Engine.h>
#include <Device/KeyboardInput.h>
#include <Device/MouseInput.h>

namespace Ronnie
{
	RTTI_DEFINITIONS(CameraController)

	CameraController::CameraController()
		: moveSpeed(1.0f), rotateSpeed(5.0f)
	{
	}

	CameraController::~CameraController()
	{
	}

	void CameraController::Initialize(ID3D11Device* device)
	{
	}

	void CameraController::Update(ID3D11DeviceContext* context, float deltaTime)
	{
		MoveCamera(deltaTime);
		RotateCamera(deltaTime);
	}

	void CameraController::Bind(ID3D11DeviceContext* context)
	{
	}

	void CameraController::SetMovespeed(float moveSpeed)
	{
		this->moveSpeed = moveSpeed;
	}

	void CameraController::SetRotateSpeed(float rotateSpeed)
	{
		this->rotateSpeed = rotateSpeed;
	}

	void CameraController::MoveCamera(float deltaTime)
	{
		// 한 프레임에 이동해야할 거리 설정.
		float moveAmount = moveSpeed * deltaTime;
		if (Engine::GetKeyboard().IsKeyDown(Keys::A))
		{
			// 왼쪽 이동 처리.
			Vector3f position = transform->Position();
			position += transform->Right() * -moveAmount;
			transform->SetPosition(position);
		}

		if (Engine::GetKeyboard().IsKeyDown(Keys::D))
		{
			// 오른쪽 이동 처리.
			Vector3f position = transform->Position();
			position += transform->Right() * moveAmount;
			transform->SetPosition(position);
		}
		if (Engine::GetKeyboard().IsKeyDown(Keys::S))
		{
			// 뒤로 이동 처리.
			Vector3f position = transform->Position();
			position += transform->Forward() * -moveAmount;
			transform->SetPosition(position);
		}

		if (Engine::GetKeyboard().IsKeyDown(Keys::W))
		{
			// 앞으로 이동 처리.
			Vector3f position = transform->Position();
			position += transform->Forward() * moveAmount;
			transform->SetPosition(position);
		}

		if (Engine::GetKeyboard().IsKeyDown(Keys::Q))
		{
			// 아래쪽 이동 처리.
			Vector3f position = transform->Position();
			position += transform->Up() * -moveAmount;
			transform->SetPosition(position);
		}

		if (Engine::GetKeyboard().IsKeyDown(Keys::E))
		{
			// 위쪽 이동 처리.
			Vector3f position = transform->Position();
			position += transform->Up() * moveAmount;
			transform->SetPosition(position);
		}
	}

	void CameraController::RotateCamera(float deltaTime)
	{
		// 마우스 클릭이 된 상태에서만 드래그 처리.
		if (Engine::GetMouse().IsButtonHeldDown(MouseButtons::Left))
		{
			float rotateAmount = rotateSpeed * deltaTime;

			// 드래그 문턱 값.
			//static float threshold = 1.0f;

			auto rotation = transform->Rotation();
			rotation.x -= rotateAmount * Engine::GetMouse().DeltaY();
			if (rotation.x >= 360.0f || rotation.x <= -360.0f)
			{
				rotation.x = 0.0f;
			}

			rotation.y -= rotateAmount * Engine::GetMouse().DeltaX();
			if (rotation.y >= 360.0f || rotation.y <= -360.0f)
			{
				rotation.y = 0.0f;
			}
			transform->SetRotation(rotation);
		}
	}
}