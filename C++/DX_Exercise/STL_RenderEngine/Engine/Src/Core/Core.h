#pragma once

#ifndef _CORE_
#define _CORE_

#pragma warning(disable : 4251)

#ifdef BUILD_DLL
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

#define TypeToString(ClassName) #ClassName

template<typename T>
void SafeDelete(T t)
{
	if (t != nullptr)
	{
		delete t;
		t = nullptr;
	}
}

template<typename T>
void SafeRelease(T t)
{
	if (t != nullptr)
	{
		t->Release();
		t = nullptr;
	}
}

#define NOMINMAX

// 공용으로 사용할 헤더.
#include <Windows.h>
#include <string>
#include <sstream>		// string-stream.
#include <memory>
#include <vector>
#include <algorithm>
#include <thread>

#include <map>
#include <unordered_map>
#include <filesystem>
#include <fstream>

// DX 관련 헤더.
#include <d3d11.h>
#include <d3d11shader.h>
#include <d3dcompiler.h>

typedef unsigned int uint32;
typedef int int32;
typedef __int64 int64;
typedef unsigned __int64 uint64;
typedef unsigned char uint8;

#endif