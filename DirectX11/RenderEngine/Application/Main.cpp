#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <tchar.h>
#include <string>

// DirectX11 헤더.
#include <d3d11.h>
#include <d3dcompiler.h> // 쉐이더 컴파일러 기능 제공

// lib 링킹			밑처럼 써서 lib를 가져올 수 있지만 아니면 옵션의 링크에 입력에 추가하면된다.
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")


void InializeDevice();

// 변수 선언
std::wstring className = TEXT("Direct3D Window class");		// 창 클래스 이름
std::wstring TitleName = TEXT("Direct3D Render Engine");	// 창 타이틀 이름
HWND hwnd = nullptr;				// 프로그램 핸들
HINSTANCE hInstance = nullptr;	// 프로그램 핸들 인스턴스
long width = 1280;					// 창의 너비
long height = 720;					// 창의 높이

// DX 변수 선언
ID3D11Device* device = nullptr;
ID3D11DeviceContext* context = nullptr;
IDXGISwapChain* swapChain = nullptr;





LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// __stdcall , __cdecl의 대해
/*
__stdcall = WINAPI __cdecl = WINAPIV
진입점(시스템) 함수 실행시 stack 메모리에 쌓인다. 다 쓰인 후 메모리를 전체를 잡고 끝나면 메모리 해제의 주체가 무엇이냐에 대해 따라 다르다.
__stdcall = 함수 자체에서 메모리 해제를 담당한다.
__cdecl = caller라는 애가 메모리 해제를 담당한다.
*/
// wWinMain함수의 인자에 대해
/* 인자는 windows.h - > winbase.h - >
wwinmain함수 선언의 파라미터값을 긇어와 사용해준다.*/
// _In_ , _In_opt_의 대해
/* _In_, _In_opt_ 는 윈도우 시스템 프로그래밍할때만 사용되며,
파라미터의 input output을 명시적으로 해준다.*/


int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	//=================================================================================================== 창 생성
	::hInstance = hInstance; // ::(스코프 : 현재는 전역변수를 사용하기 위해 붙인다.)

	// Register the window class.
	// WNDCLASS = 윈도우 창에 대해 필요한 데이터를 가진 구조체
	WNDCLASS wc = { };

	// 윈도우프로시저 ( 창에대한 메세지 처리 함수 ) // Invoke(간접호출 방식) 위임(Delegate)/ callback 방식. 함수의 위치를 알려주고 특정 상황에 윈도우가 호출해준다.
	wc.lpfnWndProc = WindowProc;
	// 프로그램의 핸들 인스턴스
	wc.hInstance = hInstance;
	// 윈도우 창의 이름
	wc.lpszClassName = className.c_str();

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
	::hwnd = CreateWindowEx(0,/*Optional window styles.*/className.c_str()/*Window class*/,TitleName.c_str()/*Window text*/,WS_OVERLAPPEDWINDOW/*Window style*/,
		// setting window Size and position
		xpos, ypos, windowWidth, windowHeight,

		nullptr,		// Parent window	( 부모 창에 대한 포인터 )
		nullptr,		// Menu				( 메뉴창 포인터 )
		hInstance,		// Instance handle	( 프로그램 핸들 인스턴스 )
		nullptr			// Additional application data	( 부가 데이터 ) 창에 구조체같은 데이터를 넘겨 사용할 수 있다.
	);

	if (::hwnd == nullptr)
	{
		return 0;
	}
	/////////////////////////////////////wc.hbrBackground = WHITE_BRUSH;
	ShowWindow(::hwnd, SW_SHOW); // 창 띄우기
	UpdateWindow(::hwnd);	// 창 업데이트
	//=================================================================================================== DX 초기화
	InializeDevice();
	//=================================================================================================== 메시지 루프
	MSG msg = { };
	
	// 메세지를 확인하면 나가라는 WM_QUIT 메세지가 아니라면 계속 돈다.
	while (msg.message != WM_QUIT/*GetMessage(&msg, nullptr, 0, 0) > 0*/)
	{
		if (PeekMessage(&msg,nullptr,0u,0u,PM_REMOVE))
		{
			// 윈도우 (os)가 전달한 메시지 해석
			TranslateMessage(&msg);
			// 및 전달(윈도우 프로시저 함수 호출)
			DispatchMessage(&msg);
		}
		else
		{

		}
	}

	// 창 등록 해제
	UnregisterClass(className.c_str(),hInstance);
	
	return 0;
}

void InializeDevice()
{
	unsigned int Flag = 0;

#if _DEBUG
	// 디버그 모드일 경우
	// 장치 생성 과정에서 오류가 발생했을 때 디버깅 정보를 더 많이 전달해달라는 옵션 추가.
	Flag ^= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// DX11 버젼 지정
	// 상위 버젼을 앞에 넣으면 먼저 시도해보고 지원하지 않으면 다음 버전으로 넘어간다.
	D3D_FEATURE_LEVEL level[] = { D3D_FEATURE_LEVEL_11_1 , D3D_FEATURE_LEVEL_11_0 };

	// 스왑체인 생성을 위한 구조체 설정
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

	swapChainDesc.BufferCount = 1; // 백버퍼 개수 설정
	swapChainDesc.BufferDesc.Width = ::width;	// 프레임 너비
	swapChainDesc.BufferDesc.Height = ::height;	// 프레임 높이
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;// 이미지 채널별 포맷
	swapChainDesc.Windowed = true;				// 창 모드 여부
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;// 프레임(이미지)의 용도 설정 = 렌더링
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;// 프론트 <-> 백 버퍼 변경할 때 효과 넣을지 설정
	swapChainDesc.SampleDesc.Count = 1;			// 멀티샘플링 할지 여부 -> 1 안함
	swapChainDesc.SampleDesc.Quality = 0;		// 멀티샘플링 품질 설정 -> 기본 값(count - 1)
	swapChainDesc.OutputWindow = hwnd;			// DX가 그릴 창 핸들

	D3D_FEATURE_LEVEL finaFeature;


	D3D11CreateDevice(nullptr,D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE);
	

	// 디바이스 / 컨텍스트 / 스압체인 생성
	auto result = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		Flag,
		level,
		ARRAYSIZE(level),
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&swapChain,
		&device,
		&finaFeature,
		&context
		);	// 디바이스, 컨텍스트 , 스압체인을 한번에 만든다. 자세한 내용은 따로따로 해야한다.

	// 실패여부 확인
	S_OK;
	E_FAIL;
	if (FAILED(result))
	{
		MessageBox(nullptr,TEXT("Failed to create device."), TEXT("Error"),MB_OK);
		exit(-1);
	}
}

// 윈도우 프로시저 함수
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY: // 창이 삭제될 때
	{	
		PostQuitMessage(0); // 창이 종료되었으니 프로그램 종료 메시지
		return 0; // 1이 문제있음 0은 문제없이 종료되었을 때 사용된다.
	}
	case WM_KEYDOWN: // 어떠한 키가 눌렸을 때
	{
		if (wParam == VK_ESCAPE)
		{
			if (MessageBox(nullptr/*부모 핸들*/, TEXT("Quit?")/*메세지 내용*/, TEXT("Quit Engine")/*메시지 박스 이름*/, MB_YESNO/*박스의 타입(YES/NO 박스)*/) == IDYES/*받은 내용 비교*/)
				DestroyWindow(hwnd); // 창 종료
		}
	}
	case WM_PAINT: // 창을 그려야 할 때
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		// All painting occurs here, between BeginPaint and EndPaint.

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
		return 0;
	}
	}


	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}