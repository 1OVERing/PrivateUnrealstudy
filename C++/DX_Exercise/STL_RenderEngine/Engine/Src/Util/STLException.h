#pragma once

#ifndef _STL_EXCEPTION_
#define _STL_EXCEPTION_

#include "Core.h"
#include <exception>

namespace Ronnie
{
	inline void ThrowIfFailed(HRESULT hr, const char* message, const char* filename = "")
	{
		if (FAILED(hr))
		{
			std::string msg = std::string(message) + std::string(filename);
			throw std::exception(msg.c_str());
		}
	}
}
#endif