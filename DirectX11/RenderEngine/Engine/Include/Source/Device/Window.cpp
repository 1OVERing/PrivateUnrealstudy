#include "Window.h"
#include <exception> // ǥ�ؿ���.

namespace STL
{
	Window::Window(HINSTANCE hinstance, uint32 w, uint32 h, const std::wstring& title, WNDPROC procedure)
	:classname(L"RanderEngine"),title(title),width(w),height(h),hInstance(hinstance),handle(nullptr), procedure(procedure){}
	Window::~Window()
	{
		// Ŭ���� ��� ����
		UnregisterClass(classname.c_str(), hInstance);
	}
/*-----------------------------------------------------------------------------------------------------------------------------------*/
	void Window::SetTitle(const std::wstring& newTitle)
	{
	}

	//=================================================================================================== â Ŭ���� ���� �� ����
	void Window::Intialize()
	{
		// Register the window class.
		// WNDCLASS = ������ â�� ���� �ʿ��� �����͸� ���� ����ü
		WNDCLASS wc = { };

		// ���������ν��� ( â������ �޼��� ó�� �Լ� ) // Invoke(����ȣ�� ���) ����(Delegate)/ callback ���. �Լ��� ��ġ�� �˷��ְ� Ư�� ��Ȳ�� �����찡 ȣ�����ش�.
		wc.lpfnWndProc = procedure;
		// ���α׷��� �ڵ� �ν��Ͻ�
		wc.hInstance = hInstance;
		// ������ â�� �̸�
		wc.lpszClassName = classname.c_str();

		// (Ŭ���� �̸� ���) ����� ������ â�� ���� ������ ���� ����ü�� ������Ʈ�� ����� �����ش�.
		RegisterClass(&wc);


		// window â�� ���� ũ�� ����
		// RECT�� ���簢���� �����͸� ���� ����ü (Left,Top,Right(�ʺ�),Bottom(����));
		RECT rect = { 0,0,width ,height };
		// ��Ÿ�Ͽ� ���缭 Ŭ���̾�Ʈ ������ �� ���� ���ϴ� ũ�⸸ŭ ������ �ٲ��ش�.
		AdjustWindowRect(&rect/*window â�� ũ�� ����ü*/, WS_OVERLAPPEDWINDOW/*â�� ���� ��Ÿ��*/, FALSE/*Ÿ��Ʋ���� ���� ��Ÿ��*/);

		// ������ ���簢�� ũ��� â ����/���� ũ�� ���Ѵ�.
		long windowWidth = rect.right - rect.left;
		long windowHeight = rect.bottom - rect.top;

		// ȭ���� �߽ɿ��� â�� �׸��� ���� ������ǥ ���ϱ�
		long xpos = (GetSystemMetrics(SM_CXSCREEN) - windowWidth) / 2; // GetSystemMetrics(SM_CXSCREEN) = window���� ���� ������ â�� ��ġ�� ���� �Լ�
		long ypos = (GetSystemMetrics(SM_CYSCREEN) - windowHeight) / 2; // SM_CXSCREEN = X SM_CYSCREEN = Y

		// Create the window.
		handle = CreateWindowEx(0,/*Optional window styles.*/classname.c_str()/*Window class*/, title.c_str()/*Window text*/, WS_OVERLAPPEDWINDOW/*Window style*/,
			xpos, ypos, windowWidth, windowHeight, // setting window Size and position
			nullptr,		// Parent window	( �θ� â�� ���� ������ )
			nullptr,		// Menu				( �޴�â ������ )
			hInstance,		// Instance handle	( ���α׷� �ڵ� �ν��Ͻ� )
			nullptr			// Additional application data	( �ΰ� ������ ) â�� ����ü���� �����͸� �Ѱ� ����� �� �ִ�.
		);

		if (handle == nullptr)
		{
			// �ͼ��� exception�� ���⼭ �ɸ��� �Ǹ� ���α׷��� ���⼭ ���߰� ����ó���� ���ش�. assert�� ����� ������ �Ѵ�.
			//assert(handle != nullptr);
			throw std::exception("������ ���� ����!");
		}



		ShowWindow(handle, SW_SHOW); // â ����
		UpdateWindow(handle);	// â ������Ʈ
	}
}
