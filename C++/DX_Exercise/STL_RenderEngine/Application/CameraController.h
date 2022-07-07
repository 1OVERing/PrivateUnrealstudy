#pragma once

#ifndef _CAMERA_CONTROLLER_
#define _CAMERA_CONTROLLER_

#include "Core.h"
#include "Component/Component.h"

namespace Ronnie
{
	class KeyboardInput;
	class MouseInput;
	class CameraController : public Component
	{
		RTTI_DECLARATIONS(CameraController, Component)

	public:
		CameraController();
		//CameraController(const CameraController& other) = delete;
		~CameraController();

		// Inherited via Component
		virtual void Initialize(ID3D11Device* device) override;
		virtual void Update(ID3D11DeviceContext* context, float deltaTime) override;
		virtual void Bind(ID3D11DeviceContext* context) override;

		void SetMovespeed(float moveSpeed);
		void SetRotateSpeed(float rotateSpeed);

	private:

		void MoveCamera(float deltaTime);
		void RotateCamera(float deltaTime);

		float moveSpeed;
		float rotateSpeed;
	};
}

#endif