#pragma once


// DLL 익스포트 인포트
#ifdef ENGINE_BUILD_DLL
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif


#include <Windows.h>
#include <string>
#include <vector>
#include <memory>

// DX 헤더 추가
#include <d3d11.h>
#include <d3dcompiler.h>
#include <dxgi1_3.h>	// swapchain 개별생성을 DXGI클래스. 팩토리 어댑터 위한 헤더
#include <comdef.h>

// 타입 재정의
using uint32 = unsigned int;
using uint64 = unsigned __int64;
using int64 = __int64;

// 탐플릿 함수

 // com 객체인 DX 객체들의 대한 자동 릴리즈
template<typename Type>
void SafeRelease(Type t)
{
	if (t != nullptr)
	{
		t->Release();
		t = nullptr;
	}
}