#include "Core.h"
#include "Window.h"

namespace Ronnie
{
	bool Window::Initialize(HINSTANCE hInstance, uint32 width, 
        uint32 height, const std::wstring& title, WNDPROC wndproc)
	{
        // ���� �� ����.
        this->instance = hInstance;
        this->width = width;
        this->height = height;
        this->title = title;

        // �޸� ����.
        WNDCLASSEX wc = { 0 };
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.lpszClassName = TEXT("WindowClass");
        wc.hInstance = hInstance;
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
        wc.style = CS_VREDRAW | CS_HREDRAW;
        wc.lpfnWndProc = wndproc;

        // Ŭ���� ���.
        bool result = RegisterClassEx(&wc);

        if (result == false)
        {
            MessageBox(nullptr, L"â ���� ����", L"Error", 0);
            return false;
        }

        // â ����.
        // ũ��/��ġ ����.
        RECT rect = 
        { 
            0, 0, 
            static_cast<long>(width), 
            static_cast<long>(height) 
        };

        // ���� ������ ũ�⸦ �����ϰ� ����ϱ� ���� â ũ�� ����.
        AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
        int windowWidth = rect.right - rect.left;
        int windowHeight = rect.bottom - rect.top;

        // ȭ�� ����� �׸��� ���� ��ġ ���ϱ�.
        int posX = (GetSystemMetrics(SM_CXSCREEN) - windowWidth) / 2;
        int posY = (GetSystemMetrics(SM_CYSCREEN) - windowHeight) / 2;

        // ����.
        // â -> ���α׷�.
        windowHandle = CreateWindow(
            wc.lpszClassName,
            title.c_str(),     // â ����(Ÿ��Ʋ�� �̸�).
            WS_OVERLAPPEDWINDOW,
            posX, posY,
            windowWidth, windowHeight,
            nullptr,
            nullptr,
            hInstance,
            0
        );

        // ����ó��.
        if (windowHandle == nullptr)
        {
            MessageBox(nullptr, L"â ���� ����", L"Error", 0);
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