#pragma once

#ifndef _ENGINE_
#define _ENGINE_

#include "Core.h"
#include "Device/Window.h"
#include "Device/DeviceManager.h"
#include "Device/GameTimer.h"

namespace Ronnie
{
	// �Է� ���� ���漱��(Forward Declaration).
	class KeyboardInput;
	class MouseInput;

	// ����.
	class ENGINE_API Engine
	{
		friend class GameMainLoop;

	public:
		Engine(
			HINSTANCE hInstance,
			uint32 width,
			uint32 height,
			const std::wstring& title
		);

		virtual ~Engine();

		virtual void Initialize();
		virtual void Run();

		virtual void ProcessInput();
		virtual void Update(float deltaTime);
		virtual void Draw();

		static KeyboardInput& GetKeyboard();
		static MouseInput& GetMouse();

		static uint32 ScreenWidth() { return mainWindow->Width(); }
		static uint32 ScreenHeight() { return mainWindow->Height(); }

		static ID3D11Device* GetDevice() { return deviceManager->GetDevice(); }
		static ID3D11Device** GetDeviceAdressOf() { return deviceManager->GetDeviceAddressOf(); }

		static ID3D11DeviceContext* GetDeviceContext() { return deviceManager->GetDeviceContext(); }
		static ID3D11DeviceContext** GetDeviceContextAdressOf() { return deviceManager->GetDeviceContextAddressOf(); }

		static ID3D11DepthStencilView* GetDepthStencilView() { return deviceManager->GetDepthStencilView(); }
		static ID3D11RenderTargetView* GetRenderTargetView() { return deviceManager->GetRenderTargetView(); }

	protected:

		virtual void BeginScene();
		virtual void RenderScene();
		virtual void EndScene();

		// ��� ����.
		float backgroundColor[4];

		// Smart Pointer.
		static std::unique_ptr<Window> mainWindow;
		static std::unique_ptr<DeviceManager> deviceManager;

		// ������ Ÿ�Կ��� ��� ����.
		std::unique_ptr<GameTimer> gameTimer;

		static std::unique_ptr<KeyboardInput> keyboard;
		static std::unique_ptr<MouseInput> mouse;

		// Ÿ�� ������ ����Ʈ.
		int targetFrameRate = 90;
	};
}
#endif