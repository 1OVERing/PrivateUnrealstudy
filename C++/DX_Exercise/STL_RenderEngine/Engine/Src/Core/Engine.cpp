#include "Core.h"
#include "Engine.h"
#include "Util/ModelLoader.h"
#include "Util/TextureLoader.h"

#include "Device/KeyboardInput.h"
#include "Device/MouseInput.h"

namespace Ronnie
{
	std::unique_ptr<KeyboardInput> Engine::keyboard;
	std::unique_ptr<MouseInput> Engine::mouse;

	std::unique_ptr<Window> Engine::mainWindow;
	std::unique_ptr<DeviceManager> Engine::deviceManager;

	LRESULT CALLBACK WindowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
			// Ű���� �Է� ó���ϵ���.
		case WM_ACTIVATEAPP:
			DirectX::Keyboard::ProcessMessage(message, wParam, lParam);
			DirectX::Mouse::ProcessMessage(message, wParam, lParam);
			break;

		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYUP:
			DirectX::Keyboard::ProcessMessage(message, wParam, lParam);
			break;

			// ���콺 �Է� ó���ǵ���.
		case WM_INPUT:
		case WM_MOUSEMOVE:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_MOUSEWHEEL:
		case WM_MOUSEHOVER:
			DirectX::Mouse::ProcessMessage(message, wParam, lParam);
			break;

			// â�� �������� ��.
		case WM_DESTROY:
			// ���α׷� ���� �޽��� ����.
			PostQuitMessage(0);
			break;
		}

		// �ü���� �⺻���� �˾Ƽ� ó���ϵ���.
		return DefWindowProc(handle, message, wParam, lParam);
	}

	Engine::Engine(
		HINSTANCE hInstance,
		uint32 width,
		uint32 height,
		const std::wstring& title)
	{
		// â ��ü ����.
		//Window* window = new Window();
		//delete window;

		mainWindow = std::make_unique<Window>();
		mainWindow->Initialize(hInstance, width, height, title, WindowProc);

		// Device Manager �ʱ�ȭ.
		deviceManager = std::make_unique<DeviceManager>();
		deviceManager->InitializeDevice(
			mainWindow->WindowHandle(),
			mainWindow->Width(),
			mainWindow->Height(),
			true
		);

		// Ÿ�̸� �ʱ�ȭ.
		gameTimer = std::make_unique<GameTimer>();
		gameTimer->SetWindow(mainWindow.get());

		// �Է� ��ġ �ʱ�ȭ.
		keyboard = std::make_unique<KeyboardInput>();
		keyboard->Initialize();

		mouse = std::make_unique<MouseInput>(mainWindow->WindowHandle());
		mouse->Initialize();
	}

	Engine::~Engine()
	{
		ModelLoader::Release();
		TextureLoader::Release();
	}

	void Engine::Initialize()
	{
		// ���� ����.
		backgroundColor[0] = 0.6f;
		backgroundColor[1] = 0.8f;
		backgroundColor[2] = 0.9f;
		backgroundColor[3] = 1.0f;
	}

	// ���� ����.
	void Engine::Run()
	{	
		Initialize();

		// Ÿ�̸� ����.
		gameTimer->Start();

		// Ÿ�� ������ ���� �ڵ�.
		// ���� �ð� ����.
		int64 previousTime = gameTimer->Now();

		// �� �������� ƽ ���� ���.
		int64 oneFrameCount = gameTimer->ClockFrequency() / targetFrameRate;

		MSG message = { 0 };
		while (message.message != WM_QUIT)
		{
			// �޽��� ĳġ(�ޱ�).
			// GetMessage / PeekMessage.
			if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
			{
				// �޽��� �ؼ�.
				TranslateMessage(&message);

				// �޽��� ó�� ������ ����.
				DispatchMessage(&message);
			}

			else
			{
				// ���� �ð� Ȯ��.
				int64 currentTime = gameTimer->Now();

				// Ÿ�� ������ �������� �� �������� �������� Ȯ��.
				if (currentTime >= previousTime + oneFrameCount)
				{
					// Ÿ�̸� ������Ʈ.
					gameTimer->Update();
					float deltaTime = gameTimer->DeltaTime();

					// ���� ����.
					ProcessInput();
					Update(deltaTime);
					Draw();					// Render.

					// ���� �ð� ������Ʈ.
					previousTime = currentTime;
				}
			}

			//Sleep(0);
		}
	}

	void Engine::ProcessInput()
	{
		keyboard->Update();
		mouse->Update();
	}

	// �׸��� ���� �����͸� �����ϴ� �Լ�.
	void Engine::Update(float deltaTime)
	{
	}

	// ������Ʈ(����)�� �����͸� ������� ȭ��(������) �׸��� �Լ�.
	void Engine::Draw()
	{
		BeginScene();
		RenderScene();
		EndScene();
	}

	KeyboardInput& Engine::GetKeyboard()
	{
		return *keyboard.get();
	}

	MouseInput& Engine::GetMouse()
	{
		return *mouse.get();
	}

	void Engine::BeginScene()
	{
		deviceManager->BeginScene(backgroundColor);
	}

	void Engine::RenderScene()
	{
		deviceManager->RenderScene();
	}

	void Engine::EndScene()
	{
		deviceManager->EndScene(0, 0);
	}
}
