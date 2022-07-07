#include "Core.h"
#include "Logger.h"

namespace Ronnie
{
	Logger* Logger::instance;

	Logger& Logger::Get()
	{
		if (instance == nullptr)
		{
			instance = new Logger();
		}

		return *instance;
	}

	void Logger::Release()
	{
		SafeDelete(instance);
		SafeDelete(timer);
	}

	void Logger::ShowMessage(const std::wstring& message)
	{
		MessageBox(nullptr, message.c_str(), L"Info", MB_OK);
	}

	void Logger::ShowMessage(const std::string& message)
	{
		MessageBoxA(nullptr, message.c_str(), "Info", MB_OK);
	}

	void Logger::PrintMessage(const std::wstring& message)
	{
		OutputDebugString(message.c_str());
	}

	void Logger::PrintMessage(const std::string& message)
	{
		OutputDebugStringA(message.c_str());
	}

	void Logger::TimeStampStart()
	{
		if (timer == nullptr)
		{
			timer = new GameTimer();
			timer->Start();
			countsPerSecond = static_cast<float>(timer->ClockFrequency());
		}

		timeStart = static_cast<float>(timer->Now());
	}

	void Logger::TimeStampEnd(bool isShowMessage)
	{
		if (timer == nullptr)
		{
			timer = new GameTimer();
			timer->Start();
			countsPerSecond = static_cast<float>(timer->ClockFrequency());
		}

		timeEnd = static_cast<float>(timer->Now());

		if (isShowMessage == true)
		{
			ShowStamp();
		}
	}

	void Logger::ShowStamp(const char* type)
	{
		std::stringstream ss;
		ss << "Stamp Start: " << timeStart << "\n"
			<< "Stamp End: " << timeEnd << "\n"
			<< "Period: " << (timeEnd - timeStart) / countsPerSecond << "\n"
			<< "Type: " << type;

		ShowMessage(ss.str());
	}

	void Logger::PrintStamp()
	{
		std::stringstream ss;
		ss << "Stamp Start: " << timeStart << "\n"
			<< "Stamp End: " << timeEnd << "\n"
			<< "Period: " << (timeEnd - timeStart) / countsPerSecond;

		PrintMessage(ss.str());
	}

	Logger::Logger()
		: timer(nullptr),
		timeStart(0.0f),
		timeEnd(0.0f),
		countsPerSecond(0.0f)
	{
	}

	Logger::~Logger()
	{
	}
}