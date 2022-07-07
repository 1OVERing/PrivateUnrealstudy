#include "PlayerController.h"
#include <Component/TransformComponent.h>
#include "Engine.h"
#include <Device/KeyboardInput.h>

namespace Ronnie
{
	RTTI_DEFINITIONS(PlayerController)

	PlayerController::PlayerController()
	{
	}

	PlayerController::~PlayerController()
	{
	}

	void PlayerController::Initialize(ID3D11Device* device)
	{
	}

	void PlayerController::Update(ID3D11DeviceContext* context, float deltaTime)
	{
		static float amount = 1.0f;
		if (Engine::GetKeyboard().IsKeyDown(Keys::A) == true)
		{
			auto position = transform->Position();
			position.x -= amount * deltaTime;
			transform->SetPosition(position);
		}

		if (Engine::GetKeyboard().IsKeyDown(Keys::D) == true)
		{
			auto position = transform->Position();
			position.x += amount * deltaTime;
			transform->SetPosition(position);
		}

		if (Engine::GetKeyboard().IsKeyDown(Keys::S) == true)
		{
			auto position = transform->Position();
			position.y -= amount * deltaTime;
			transform->SetPosition(position);
		}

		if (Engine::GetKeyboard().IsKeyDown(Keys::W) == true)
		{
			auto position = transform->Position();
			position.y += amount * deltaTime;
			transform->SetPosition(position);
		}
	}

	void PlayerController::Bind(ID3D11DeviceContext* context)
	{
	}
}