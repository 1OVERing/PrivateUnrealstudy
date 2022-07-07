#include "Core.h"
#include "Window.h"

namespace Ronnie
{
	bool Window::Initialize(HINSTANCE hInstance, uint32 width, 
        uint32 height, const std::wstring& title, WNDPROC wndproc)
	{
        // 변수 값 설정.
        this->instance = hInstance;
        this->width = width;
        this->height = height;
        this->title = title;

        // 메모리 세팅.
        WNDCLASSEX wc = { 0 };
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.lpszClassName = TEXT("WindowClass");
        wc.hInstance = hInstance;
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
        wc.style = CS_VREDRAW | CS_HREDRAW;
        wc.lpfnWndProc = wndproc;

        // 클래스 등록.
        bool result = RegisterClassEx(&wc);

        if (result == false)
        {
            MessageBox(nullptr, L"창 생성 실패", L"Error", 0);
            return false;
        }

        // 창 생성.
        // 크기/위치 조정.
        RECT rect = 
        { 
            0, 0, 
            static_cast<long>(width), 
            static_cast<long>(height) 
        };

        // 렌더 프레임 크기를 온전하게 사용하기 위해 창 크기 조절.
        AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
        int windowWidth = rect.right - rect.left;
        int windowHeight = rect.bottom - rect.top;

        // 화면 가운데로 그리기 위한 위치 구하기.
        int posX = (GetSystemMetrics(SM_CXSCREEN) - windowWidth) / 2;
        int posY = (GetSystemMetrics(SM_CYSCREEN) - windowHeight) / 2;

        // 생성.
        // 창 -> 프로그램.
        windowHandle = CreateWindow(
            wc.lpszClassName,
            title.c_str(),     // 창 제목(타이틀바 이름).
            WS_OVERLAPPEDWINDOW,
            posX, posY,
            windowWidth, windowHeight,
            nullptr,
            nullptr,
            hInstance,
            0
        );

        // 예외처리.
        if (windowHandle == nullptr)
        {
            MessageBox(nullptr, L"창 생성 실패", L"Error", 0);
            return false;
        }

        ShowWindow(windowHandle, SW_SHOW);
        UpdateWindow(windowHandle);

		return true;
	}
	
	HINSTANCE Window::Instance()
	{
		return instance;
	}

	HWND Window::WindowHandle()
	{
		return windowHandle;
	}

	uint32 Window::Width()
	{
		return width;
	}

	uint32 Window::Height()
	{
		return height;
	}

	std::wstring Window::Title()
	{
		return title;
	}

	void Window::SetTitle(const std::wstring& title)
	{
		//SetWindowText
        //SetWindowText(HWND, const wchar_t*);
        SetWindowText(windowHandle, title.c_str());
	}
}