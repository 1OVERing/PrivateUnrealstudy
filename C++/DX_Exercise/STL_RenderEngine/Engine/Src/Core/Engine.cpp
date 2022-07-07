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
			// 키보드 입력 처리하도록.
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

			// 마우스 입력 처리되도록.
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

			// 창이 삭제됐을 때.
		case WM_DESTROY:
			// 프로그램 종료 메시지 전송.
			PostQuitMessage(0);
			break;
		}

		// 운영체제가 기본으로 알아서 처리하도록.
		return DefWindowProc(handle, message, wParam, lParam);
	}

	Engine::Engine(
		HINSTANCE hInstance,
		uint32 width,
		uint32 height,
		const std::wstring& title)
	{
		// 창 객체 생성.
		//Window* window = new Window();
		//delete window;

		mainWindow = std::make_unique<Window>();
		mainWindow->Initialize(hInstance, width, height, title, WindowProc);

		// Device Manager 초기화.
		deviceManager = std::make_unique<DeviceManager>();
		deviceManager->InitializeDevice(
			mainWindow->WindowHandle(),
			mainWindow->Width(),
			mainWindow->Height(),
			true
		);

		// 타이머 초기화.
		gameTimer = std::make_unique<GameTimer>();
		gameTimer->SetWindow(mainWindow.get());

		// 입력 장치 초기화.
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
		// 배경색 지정.
		backgroundColor[0] = 0.6f;
		backgroundColor[1] = 0.8f;
		backgroundColor[2] = 0.9f;
		backgroundColor[3] = 1.0f;
	}

	// 게임 루프.
	void Engine::Run()
	{	
		Initialize();

		// 타이머 시작.
		gameTimer->Start();

		// 타겟 프레임 제한 코드.
		// 이전 시간 저장.
		int64 previousTime = gameTimer->Now();

		// 한 프레임의 틱 개수 계산.
		int64 oneFrameCount = gameTimer->ClockFrequency() / targetFrameRate;

		MSG message = { 0 };
		while (message.message != WM_QUIT)
		{
			// 메시지 캐치(받기).
			// GetMessage / PeekMessage.
			if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
			{
				// 메시지 해석.
				TranslateMessage(&message);

				// 메시지 처리 루프로 전달.
				DispatchMessage(&message);
			}

			else
			{
				// 현재 시간 확인.
				int64 currentTime = gameTimer->Now();

				// 타겟 프레임 기준으로 한 프레임이 지났는지 확인.
				if (currentTime >= previousTime + oneFrameCount)
				{
					// 타이머 업데이트.
					gameTimer->Update();
					float deltaTime = gameTimer->DeltaTime();

					// 엔진 루프.
					ProcessInput();
					Update(deltaTime);
					Draw();					// Render.

					// 이전 시간 업데이트.
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

	// 그리기 전에 데이터를 갱신하는 함수.
	void Engine::Update(float deltaTime)
	{
	}

	// 업데이트(갱신)된 데이터를 기반으로 화면(프레임) 그리는 함수.
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
