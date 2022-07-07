#pragma once

#ifndef _PLAYER_CONTROLLER_
#define _PLAYER_CONTROLLER_

#include "Core.h"
#include "Component/Component.h"

namespace Ronnie
{
	class PlayerController : public Component
	{
		RTTI_DECLARATIONS(PlayerController, Component)

	public:
		PlayerController();
		~PlayerController();

		// Inherited via Component
		virtual void Initialize(ID3D11Device* device) override;
		virtual void Update(ID3D11DeviceContext* context, float deltaTime) override;
		virtual void Bind(ID3D11DeviceContext* context) override;
	};
}

#endif