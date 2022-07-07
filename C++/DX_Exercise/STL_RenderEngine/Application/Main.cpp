#pragma once

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "Core.h"
#include "Demo.h"
#include <exception>

using namespace Ronnie;

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd)
{
    // 메모리 릭 검사 옵션.
#if DEBUG || _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    //_CrtSetBreakAlloc(1183);

    try
    {
        // 프로그램(게임) 생성.
        std::unique_ptr<Demo> app(new Demo(hInstance, 1600, 900, L"Real-Time Render Engine"));

        // 게임 실행.
        app->Run();
    }
    catch (std::exception ex)
    {
        MessageBoxA(nullptr, ex.what(), "Error", 0);
    }
}