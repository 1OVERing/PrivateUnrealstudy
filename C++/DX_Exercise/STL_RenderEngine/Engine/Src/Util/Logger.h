#pragma once

#ifndef _LOGGER_
#define _LOGGER_

#include "Core.h"
#include "Device/GameTimer.h"

namespace Ronnie
{
	class ENGINE_API Logger
	{
	public:
		static Logger& Get();
		~Logger();
		void Release();

		void ShowMessage(const std::wstring& message);
		void ShowMessage(const std::string& message);

		void PrintMessage(const std::wstring& messasge);
		void PrintMessage(const std::string& message);

		void TimeStampStart();
		void TimeStampEnd(bool isShowMessage = false);
		void ShowStamp(const char* type = "");
		void PrintStamp();

	private:
		Logger();

		static Logger* instance;
		GameTimer* timer;
		
		float timeStart;
		float timeEnd;
		float countsPerSecond;
	};
}

#endif