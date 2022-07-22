#pragma once


// DLL �ͽ���Ʈ ����Ʈ
#ifdef ENGINE_BUILD_DLL
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif


#include <Windows.h>
#include <string>
#include <vector>
#include <memory>

// DX ��� �߰�
#include <d3d11.h>
#include <d3dcompiler.h>
#include <dxgi1_3.h>	// swapchain ���������� DXGIŬ����. ���丮 ����� ���� ���
#include <comdef.h>

// Ÿ�� ������
using uint32 = unsigned int;
using uint64 = unsigned __int64;
using int64 = __int64;

// Ž�ø� �Լ�

 // com ��ü�� DX ��ü���� ���� �ڵ� ������
template<typename Type>
void SafeRelease(Type t)
{
	if (t != nullptr)
	{
		t->Release();
		t = nullptr;
	}
}