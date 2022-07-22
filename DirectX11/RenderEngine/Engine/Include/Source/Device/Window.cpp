#include "Window.h"
#include <exception> // 표준예외.

namespace STL
{
	Window::Window(HINSTANCE hinstance, uint32 w, uint32 h, const std::wstring& title, WNDPROC procedure)
	:classname(L"RanderEngine"),title(title),width(w),height(h),hInstance(hinstance),handle(nullptr), procedure(procedure){}
	Window::~Window()
	{
		// 클래스 등록 해제
		UnregisterClass(classname.c_str(), hInstance);
	}
/*-----------------------------------------------------------------------------------------------------------------------------------*/
	void Window::SetTitle(const std::wstring& newTitle)
	{
	}

	//=================================================================================================== 창 클래스 설정 및 생성
	void Window::Intialize()
	{
		// Register the window class.
		// WNDCLASS = 윈도우 창에 대해 필요한 데이터를 가진 구조체
		WNDCLASS wc = { };

		// 윈도우프로시저 ( 창에대한 메세지 처리 함수 ) // Invoke(간접호출 방식) 위임(Delegate)/ callback 방식. 함수의 위치를 알려주고 특정 상황에 윈도우가 호출해준다.
		wc.lpfnWndProc = procedure;
		// 프로그램의 핸들 인스턴스
		wc.hInstance = hInstance;
		// 윈도우 창의 이름
		wc.lpszClassName = classname.c_str();

		// (클래스 이름 등록) 사용할 윈도우 창에 대한 정보를 담을 구조체를 레지스트를 등록을 시켜준다.
		RegisterClass(&wc);


		// window 창에 대한 크기 조정
		// RECT는 직사각형의 데이터를 가진 구조체 (Left,Top,Right(너비),Bottom(높이));
		RECT rect = { 0,0,width ,height };
		// 스타일에 맞춰서 클라이언트 영역의 이 내가 원하는 크기만큼 나오게 바꿔준다.
		AdjustWindowRect(&rect/*window 창의 크기 구조체*/, WS_OVERLAPPEDWINDOW/*창의 대한 스타일*/, FALSE/*타이틀바의 대한 스타일*/);

		// 저정된 직사각형 크기로 창 가로/세로 크기 구한다.
		long windowWidth = rect.right - rect.left;
		long windowHeight = rect.bottom - rect.top;

		// 화면의 중심에서 창을 그리기 위한 생성좌표 구하기
		long xpos = (GetSystemMetrics(SM_CXSCREEN) - windowWidth) / 2; // GetSystemMetrics(SM_CXSCREEN) = window에게 지금 윈도우 창의 위치를 묻는 함수
		long ypos = (GetSystemMetrics(SM_CYSCREEN) - windowHeight) / 2; // SM_CXSCREEN = X SM_CYSCREEN = Y

		// Create the window.
		handle = CreateWindowEx(0,/*Optional window styles.*/classname.c_str()/*Window class*/, title.c_str()/*Window text*/, WS_OVERLAPPEDWINDOW/*Window style*/,
			xpos, ypos, windowWidth, windowHeight, // setting window Size and position
			nullptr,		// Parent window	( 부모 창에 대한 포인터 )
			nullptr,		// Menu				( 메뉴창 포인터 )
			hInstance,		// Instance handle	( 프로그램 핸들 인스턴스 )
			nullptr			// Additional application data	( 부가 데이터 ) 창에 구조체같은 데이터를 넘겨 사용할 수 있다.
		);

		if (handle == nullptr)
		{
			// 익셉션 exception은 여기서 걸리게 되면 프로그램이 여기서 멈추고 예외처리를 해준다. assert와 비슷한 동작을 한다.
			//assert(handle != nullptr);
			throw std::exception("윈도우 생성 실패!");
		}



		ShowWindow(handle, SW_SHOW); // 창 띄우기
		UpdateWindow(handle);	// 창 업데이트
	}
}
