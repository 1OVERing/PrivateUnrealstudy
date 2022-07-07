#include "Core.h"
#include "MouseInput.h"

namespace Ronnie
{
	using namespace DirectX;

	std::unique_ptr<DirectX::Mouse> MouseInput::mouse(new DirectX::Mouse());

	static const MouseMode DefaultMouseMode = MouseMode::Relative;

	MouseInput::MouseInput(HWND handle, MouseMode mode)
	{
		mouse->SetWindow(handle);
		SetMode(mode);
	}

	MouseInput::~MouseInput()
	{
	}

	const DirectX::Mouse::State& MouseInput::CurrentState() const
	{
		return currentState;
	}

	const DirectX::Mouse::State& MouseInput::PreviousState() const
	{
		return previouseState;
	}

	void MouseInput::Initialize()
	{
		currentState = mouse->GetState();
		previouseState = currentState;
	}

	void MouseInput::Update()
	{
		previouseState = currentState;
		currentState = mouse->GetState();
	}

	void MouseInput::SetWindow(HWND handle)
	{
		mouse->SetWindow(handle);
	}

	int MouseInput::X() const
	{
		return currentState.x;
	}

	int MouseInput::DeltaX() const
	{
		if (Mode() == MouseMode::Relative)
		{
			return X();
		}
		else
		{
			return currentState.x - previouseState.x;
		}
	}

	int MouseInput::Y() const
	{
		return currentState.y;
	}

	int MouseInput::DeltaY() const
	{
		if (Mode() == MouseMode::Relative)
		{
			return Y();
		}
		else
		{
			return currentState.y - previouseState.y;
		}
	}

	int MouseInput::Wheel() const
	{
		return currentState.scrollWheelValue;
	}

	bool MouseInput::IsButtonUp(MouseButtons button) const
	{
		//return GetButtonState(currentState, button) == false;
		return !GetButtonState(currentState, button);
	}

	bool MouseInput::IsButtonDown(MouseButtons button) const
	{
		return GetButtonState(currentState, button);
	}

	bool MouseInput::WasButtonUp(MouseButtons button) const
	{
		return !GetButtonState(previouseState, button);
	}

	bool MouseInput::WasButtonDown(MouseButtons button) const
	{
		return GetButtonState(previouseState, button);
	}

	bool MouseInput::WasButtonPressedThisFrame(MouseButtons button) const
	{
		return WasButtonUp(button) && IsButtonDown(button);
	}

	bool MouseInput::WasButtonReleasedThisFrame(MouseButtons button) const
	{
		return WasButtonDown(button) && IsButtonUp(button);
	}

	bool MouseInput::IsButtonHeldDown(MouseButtons button) const
	{
		return WasButtonDown(button) && IsButtonDown(button);
	}

	MouseMode MouseInput::Mode() const
	{
		auto state = mouse->GetState();
		return static_cast<MouseMode>(state.positionMode);
	}

	void MouseInput::SetMode(MouseMode mode)
	{
		mouse->SetMode(static_cast<Mouse::Mode>(mode));
	}

	bool MouseInput::GetButtonState(
		const DirectX::Mouse::State& state, 
		MouseButtons button) const
	{
		switch (button)
		{
		case MouseButtons::Left:
			return state.leftButton;

		case MouseButtons::Right:
			return state.rightButton;

		case MouseButtons::Middle:
			return state.middleButton;

		case MouseButtons::X1:
			return state.xButton1;

		case MouseButtons::X2:
			return state.xButton2;

		default:
			throw std::exception("Invalied MouseButton.");
		}
	}
}