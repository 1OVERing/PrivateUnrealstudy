//#pragma once
//
//#include "Core.h"
//#include "Application.h"
//#include <crtdbg.h>
//#include <exception>
//
//int WINAPI WinMain(
//    _In_ HINSTANCE hInstance,
//    _In_opt_ HINSTANCE hPrevInstance,
//    _In_ LPSTR lpCmdLine,
//    _In_ int nShowCmd)
//{
//    // �޸� �� �˻� �ɼ�.
//#if DEBUG || _DEBUG
//    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//#endif
//
//    try
//    {
//        // ���α׷�(����) ����.
//        std::unique_ptr<Ronnie::Application> app(Ronnie::CreateApplication(
//            hInstance, 1280, 800, L"Real-Time Render Engine")
//        );
//
//        // ���� ����.
//        app->Run();
//    }
//    catch (std::exception ex)
//    {
//        MessageBoxA(nullptr, ex.what(), "Error", 0);
//    }
//}