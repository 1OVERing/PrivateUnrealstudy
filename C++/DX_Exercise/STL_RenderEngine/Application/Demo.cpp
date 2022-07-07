#include "Demo.h"
#include "Util/STLException.h"

#include <cmath>		// �ﰢ�Լ� ����.

#include "Component/TransformComponent.h"
#include "Component/StaticMeshComponent.h"

#include "DemoLevel.h"

#include "Device/KeyboardInput.h"

namespace Ronnie
{
	Demo::~Demo()
	{
		SafeDelete(mainLevel);
	}

	void Demo::Initialize()
	{
		Engine::Initialize();

		targetFrameRate = 120;

		ID3D11Device* device = deviceManager->GetDevice();

		mainLevel = new DemoLevel();
		mainLevel->Initialize(device, this);
	}

	void Demo::Update(float deltaTime)
	{
		// ESC Ű�� ������.
		if (keyboard->IsKeyDown(Keys::Escape) == true)
		{
			if (MessageBox(
				nullptr,
				TEXT("���� �Ͻðڽ��ϱ�?"),
				TEXT("���α׷� ����"),
				MB_YESNO) == IDYES)
			{
				PostQuitMessage(0);
				return;
			}
		}

		mainLevel->Update(deviceManager->GetDeviceContext(), deltaTime);
	}

	void Demo::RenderScene()
	{
		auto context = deviceManager->GetDeviceContext();

		mainLevel->Render(context);
	}
}