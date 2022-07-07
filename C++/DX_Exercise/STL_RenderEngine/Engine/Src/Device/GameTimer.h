#pragma once

#ifndef _GAME_TIMER_
#define _GAME_TIMER_

#include "Core.h"

namespace Ronnie
{
	class Window;
	class ENGINE_API GameTimer
	{
	public:
		GameTimer();
		~GameTimer() = default;

		void Start();
		float GetTime();
		float DeltaTime();

		int64 Now();
		int64 ClockFrequency();

		void Update();
		void Reset();
		int FPS();

		void ShowStat();

		// 의존성 주입: Dependency Injection (DI).
		void SetWindow(Window* mainWindow);
		
	private:
		Window* mainWindow;

		// 타이머 변수.
		double countsPerSecond;
		int64 countStart;
		int frameCount;
		int fps;

		int64 previousFrameTime;
		float deltaTime;

		int64 clockFrequency;
	};
}
#endif