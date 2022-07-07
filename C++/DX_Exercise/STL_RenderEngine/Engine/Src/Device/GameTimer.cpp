#include "Core.h"
#include "GameTimer.h"
#include "Device/Window.h"

namespace Ronnie
{
	void GameTimer::ShowStat()
	{
		// â�� ���� ����� ���ڿ� ����.
		// RTRE - FPS: 60 - DeltaTime: 0.012
		std::wstringstream titleStream;
		titleStream << mainWindow->Title()
			<< "    FPS: " << fps
			<< "    DeltaTime: " << deltaTime;

		// ���� â�� ���� ����.
		mainWindow->SetTitle(titleStream.str());
	}

	GameTimer::GameTimer()
		: mainWindow(nullptr),
		countsPerSecond(0),
		countStart(0),
		frameCount(0),
		fps(0), previousFrameTime(0),
		deltaTime(0),
		clockFrequency(0)
	{
	}

	void GameTimer::Start()
	{
		// CPU Ŭ�� ��� ���.
		QueryPerformanceFrequency((LARGE_INTEGER*)&clockFrequency);
		countsPerSecond = static_cast<double>(clockFrequency);

		QueryPerformanceCounter((LARGE_INTEGER*)&countStart);
	}

	// countStart�� ����� ���ķ� �� �ʰ� �������� Ȯ���ϴ� �Լ�.
	// FPS �������� ���.
	float GameTimer::GetTime()
	{
		int64 currentTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

		// �ʴ����� ��ȯ.
		float time = static_cast<float>(currentTime - countStart)
			/ static_cast<float>(countsPerSecond);

		return time;
	}

	// ������ �ð� ��� �Լ�.
	float GameTimer::DeltaTime()
	{
		int64 currentTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

		// ���� ���������� ���� ƽ ���� ���.
		int64 tickCount = currentTime - previousFrameTime;

		previousFrameTime = currentTime;

		deltaTime = static_cast<float>(tickCount / countsPerSecond);

		// ����ó��.
		if (deltaTime < 0.0f)
		{
			deltaTime = 0.0f;
		}

		return deltaTime;
	}

	// ������ ������ ���� �����.
	int64 GameTimer::Now()
	{
		// ���� �ð� ��� (Tick ����).
		int64 currentTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

		return currentTime;
	}

	// CPU Ŭ���� ���ļ� ��.
	int64 GameTimer::ClockFrequency()
	{
		return clockFrequency;
	}

	void GameTimer::Update()
	{
		// ������ Ƚ�� ���.
		++frameCount;

		ShowStat();

		// FPS ���.
		if (GetTime() > 1.0f)
		{
			Reset();
		}
	}

	// �ʱ�ȭ �Լ�: FPS ����ϴµ� ���.\
	// 1�ʸ��� �ʱ�ȭ ��.
	void GameTimer::Reset()
	{
		fps = frameCount;
		frameCount = 0;

		// â�� ���� ����� ���ڿ� ����.
		// RTRE - FPS: 60 - DeltaTime: 0.012
		//std::wstringstream titleStream;
		//titleStream << mainWindow->Title()
		//	<< "    FPS: " << fps
		//	<< "    DeltaTime: " << deltaTime;

		//// ���� â�� ���� ����.
		//mainWindow->SetTitle(titleStream.str());

		// Ÿ�̸� �����.
		Start();
	}

	int GameTimer::FPS()
	{
		return fps;
	}

	void GameTimer::SetWindow(Window* mainWindow)
	{
		this->mainWindow = mainWindow;
	}
}