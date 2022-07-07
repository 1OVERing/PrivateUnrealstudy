#pragma once

#ifndef _MOUSE_INPUT_
#define _MOUSE_INPUT_

#include "Core.h"
#include <Mouse.h>

namespace Ronnie
{
	enum class MouseButtons
	{
		Left = 0,
		Right,
		Middle,
		X1,
		X2
	};

	enum class MouseMode
	{
		Absolute = 0,
		Relative
	};

	class ENGINE_API MouseInput
	{
	public:
		MouseInput(HWND handle, MouseMode mode = MouseMode::Absolute);
		~MouseInput();

		const DirectX::Mouse::State& CurrentState() const;
		const DirectX::Mouse::State& PreviousState() const;

		// �ʱ�ȭ/������Ʈ.
		virtual void Initialize();
		virtual void Update();
		
		// ���콺 ���� �о�� â ���� �Լ�.
		void SetWindow(HWND handle);

		// x��ǥ ����.
		int X() const;
		int DeltaX() const;
		
		// y��ǥ ����.
		int Y() const;
		int DeltaY() const;

		// wheel ��.
		int Wheel() const;

		// �̺�Ʈ.
		bool IsButtonUp(MouseButtons button) const;
		bool IsButtonDown(MouseButtons button) const;

		bool WasButtonUp(MouseButtons button) const;
		bool WasButtonDown(MouseButtons button) const;

		bool WasButtonPressedThisFrame(MouseButtons button) const;
		bool WasButtonReleasedThisFrame(MouseButtons button) const;

		bool IsButtonHeldDown(MouseButtons button) const;

		// ������ ���콺��� Getter/Setter.
		MouseMode Mode() const;
		void SetMode(MouseMode mode);

	private:

		bool GetButtonState(
			const DirectX::Mouse::State& state, 
			MouseButtons button) const;

		static std::unique_ptr<DirectX::Mouse> mouse;

		DirectX::Mouse::State currentState;
		DirectX::Mouse::State previouseState;
	};
}

#endif