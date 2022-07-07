#include "Core.h"
#include "GameTimer.h"
#include "Device/Window.h"

namespace Ronnie
{
	void GameTimer::ShowStat()
	{
		// 창의 제목에 사용할 문자열 생성.
		// RTRE - FPS: 60 - DeltaTime: 0.012
		std::wstringstream titleStream;
		titleStream << mainWindow->Title()
			<< "    FPS: " << fps
			<< "    DeltaTime: " << deltaTime;

		// 메인 창의 제목 설정.
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
		// CPU 클럭 사용 방식.
		QueryPerformanceFrequency((LARGE_INTEGER*)&clockFrequency);
		countsPerSecond = static_cast<double>(clockFrequency);

		QueryPerformanceCounter((LARGE_INTEGER*)&countStart);
	}

	// countStart를 기록한 이후로 몇 초가 지났는지 확인하는 함수.
	// FPS 계산용으로 사용.
	float GameTimer::GetTime()
	{
		int64 currentTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

		// 초단위로 변환.
		float time = static_cast<float>(currentTime - countStart)
			/ static_cast<float>(countsPerSecond);

		return time;
	}

	// 프레임 시간 계산 함수.
	float GameTimer::DeltaTime()
	{
		int64 currentTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

		// 이전 프레임으로 부터 틱 개수 계산.
		int64 tickCount = currentTime - previousFrameTime;

		previousFrameTime = currentTime;

		deltaTime = static_cast<float>(tickCount / countsPerSecond);

		// 예외처리.
		if (deltaTime < 0.0f)
		{
			deltaTime = 0.0f;
		}

		return deltaTime;
	}

	// 프레임 제한을 위해 사용함.
	int64 GameTimer::Now()
	{
		// 현재 시간 계산 (Tick 단위).
		int64 currentTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

		return currentTime;
	}

	// CPU 클럭의 주파수 값.
	int64 GameTimer::ClockFrequency()
	{
		return clockFrequency;
	}

	void GameTimer::Update()
	{
		// 프레임 횟수 계산.
		++frameCount;

		ShowStat();

		// FPS 계산.
		if (GetTime() > 1.0f)
		{
			Reset();
		}
	}

	// 초기화 함수: FPS 계산하는데 사용.\
	// 1초마다 초기화 함.
	void GameTimer::Reset()
	{
		fps = frameCount;
		frameCount = 0;

		// 창의 제목에 사용할 문자열 생성.
		// RTRE - FPS: 60 - DeltaTime: 0.012
		//std::wstringstream titleStream;
		//titleStream << mainWindow->Title()
		//	<< "    FPS: " << fps
		//	<< "    DeltaTime: " << deltaTime;

		//// 메인 창의 제목 설정.
		//mainWindow->SetTitle(titleStream.str());

		// 타이머 재시작.
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