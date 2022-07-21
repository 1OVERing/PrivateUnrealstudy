#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <tchar.h>
#include <string>

#include <time.h> // 
#include <cmath>  // 삼각함수 들을 사용하기 위한 헤더 추가

// DirectX11 헤더.
#include <d3d11.h>
#include <d3dcompiler.h>	// 쉐이더 컴파일러 기능 제공
#include <dxgi1_3.h>	// swapchain 개별생성을 DXGI클래스. 팩토리 어댑터 위한 헤더
#include <comdef.h>	//

// lib 링킹	밑처럼 써서 lib를 가져올 수 있지만 옵션의 링크에 입력에 추가종속성에서 추가 하면된다.
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dxgi.lib")

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

IDXGIDevice* dxgiDevice = nullptr;
IDXGIAdapter* adapter = nullptr;
IDXGISwapChain1* swapChain = nullptr;
IDXGIFactory2* dxgiFactory = nullptr;
ID3D11RenderTargetView* RTV = nullptr;
// 정점 버퍼 변수
unsigned int	vertexByteWidth = 0u;
unsigned int	vertexCount = 0u;
ID3D11Buffer* Vertexbuffer = nullptr;

ID3D11VertexShader* vertexShader = nullptr;
ID3D11PixelShader* pixelShader = nullptr;
ID3D11InputLayout* inputlayout = nullptr;

// 함수 전방선언
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void InitializeScene();
void Draw();



// 에러 메시지 출력을 위한 함수
std::wstring GetErrorMessage(HRESULT hr)
{
	_com_error error(hr);
	return error.ErrorMessage();
}


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
	::hwnd = CreateWindowEx(0,/*Optional window styles.*/className.c_str()/*Window class*/, TitleName.c_str()/*Window text*/, WS_OVERLAPPEDWINDOW/*Window style*/,
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
	//=================================================================================================== 장면 초기화
	InitializeScene();
	//=================================================================================================== 메시지 루프
	MSG msg = { };

	// 메세지를 확인하면 나가라는 WM_QUIT 메세지가 아니라면 계속 돈다.
	while (msg.message != WM_QUIT/*GetMessage(&msg, nullptr, 0, 0) > 0*/)
	{
		if (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
		{
			// 윈도우 (os)가 전달한 메시지 해석
			TranslateMessage(&msg);
			// 및 전달(윈도우 프로시저 함수 호출)
			DispatchMessage(&msg);
		}
		else
		{
			// 이미지 그리기
			Draw();
		}
	}

	// 창 등록 해제
	UnregisterClass(className.c_str(), hInstance);

	return 0;
}

// DX 디바이스 초기화
void InializeDevice()
{
	unsigned int Flag = 0;

#if _DEBUG
	// 디버그 모드일 경우
	// 장치 생성 과정에서 오류가 발생했을 때 디버깅 정보를 더 많이 전달해달라는 옵션 추가.
	Flag = D3D11_CREATE_DEVICE_DEBUG;	// 디버그시 출력창에 DX오류를 띄워준다.
#endif

	Flag |= D3D11_CREATE_DEVICE_BGRA_SUPPORT; // BGRA 형식

	// DX11 버젼 지정
	// 상위 버젼을 앞에 넣으면 먼저 시도해보고 지원하지 않으면 다음 버전으로 넘어간다.
	D3D_FEATURE_LEVEL level[] = { D3D_FEATURE_LEVEL_11_1 , D3D_FEATURE_LEVEL_11_0 };

	// 스왑체인 생성을 위한 구조체 설정
	//DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};

	//swapChainDesc.BufferCount/*백버퍼 개수 설정*/ = 1;
	//swapChainDesc.BufferDesc.Width/*프레임 너비*/ = ::width;
	//swapChainDesc.BufferDesc.Height/*프레임 높이*/ = ::height;
	//swapChainDesc.BufferDesc.RefreshRate.Numerator/*프레임율 분자*/ = 60;
	//swapChainDesc.BufferDesc.RefreshRate.Denominator/*프레임율 분모*/= 1;
	//swapChainDesc.BufferDesc.Format/*이미지 채널별 포맷*/ = DXGI_FORMAT_R8G8B8A8_UNORM;
	//swapChainDesc.BufferUsage/*프레임(이미지)의 용도 설정 = 렌더링*/ = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//swapChainDesc.BufferDesc.ScanlineOrdering/*레스터가 표면에 이미지를 만드는 방법 플래그*/ = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	//swapChainDesc.BufferDesc.Scaling/*모니터 해상도에 맞게 이미지 늘림 방식*/ = DXGI_MODE_SCALING_UNSPECIFIED;

	//swapChainDesc.Windowed/*창 모드 여부*/ = true;
	//swapChainDesc.SwapEffect/*프론트 <-> 백 버퍼 변경할 때 효과 넣을지 설정*/ = DXGI_SWAP_EFFECT_DISCARD;
	//swapChainDesc.SampleDesc.Count/*멀티샘플링 할지 여부 -> 1 안함*/ = 1;
	//swapChainDesc.SampleDesc.Quality/*멀티샘플링 품질 설정 -> 기본 값(count - 1)*/= 0;
	//swapChainDesc.OutputWindow/*DX가 그릴 창 핸들*/= hwnd;
	//swapChainDesc.Flags/*스왑 체인 동작에 대한 옵션을 설명하는 DXGI_SWAP_CHAIN_FLAG*/= 0;

	D3D_FEATURE_LEVEL finaFeature = {};
	if (auto error = (D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, nullptr, Flag, level, ARRAYSIZE(level), D3D11_SDK_VERSION, &device, &finaFeature, &context)))
	{
		// D3D11CreateDevice의 원형 설명
		/*
		HRESULT WINAPI D3D11CreateDevice(
		_In_opt_ IDXGIAdapter*										pAdapter,			. 장치를 생성할 때 사용될 비디오 어댑터의 대한 포인터 0/nullptr 을 넣으면 기본 어댑터가 지정된다.
		D3D_DRIVER_TYPE												DriverType,			. 생성 할 드라이버 유형을 나타내는 D3D_DRIVER_TYPE
		HMODULE														Software,			. 소프트웨어 래스터라이저를 구현하는 DLL에 대한 핸들
		UINT														Flags,				. D3D11_CREATE_DEVICE_FLAG
		_In_reads_opt_( FeatureLevels ) CONST D3D_FEATURE_LEVEL*	pFeatureLevels,		. 생성을 시도하는 기능 수준의 순서를 결정하는 D3D_FEATURE_LEVEL 배열에 대한 포인터 고버젼-저버전 순으로 정렬한다.
		UINT														FeatureLevels,		. pFeatureLevels의 배열 요소의 개수
		UINT														SDKVersion,			. SDK의 버전 D3D11_SDK_VERSION 으로 가능
		_COM_Outptr_opt_ ID3D11Device**								ppDevice,			. 디바이스 포인터
		_Out_opt_ D3D_FEATURE_LEVEL*								pFeatureLevel,		. 성공하면 성공한 pFeatureLevels 배열 에서 첫 번째 D3D_FEATURE_LEVEL 을 반환
		_COM_Outptr_opt_ ID3D11DeviceContext**						ppImmediateContext	.
		);
		*/
		MessageBox(nullptr, GetErrorMessage(error).c_str(), TEXT("Error"), MB_OK);
		exit(-1);
	}

	GUID guid = {};
	// QueryInterface 는 Dx최상위 객체인 IUnKnown 객체의 함수이며, 첫번째 인자의 클래스를 생성해주는 역활을 한다.
	if (auto error = (device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice)))
	{
		MessageBox(nullptr, GetErrorMessage(error).c_str(), TEXT("Error"), MB_OK);
		exit(-1);
	}


	if (auto error = (dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&adapter)))
	{
		MessageBox(nullptr, GetErrorMessage(error).c_str(), TEXT("Error"), MB_OK);
		exit(-1);
	};


	if (auto error = (adapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory)))
	{
		MessageBox(nullptr, GetErrorMessage(error).c_str(), TEXT("Error"), MB_OK);
		exit(-1);
	}

	// https://docs.microsoft.com/en-us/windows/win32/api/dxgi1_2/ns-dxgi1_2-dxgi_swap_chain_desc1
	DXGI_SWAP_CHAIN_DESC1 swapchainDesc = {};
	swapchainDesc.Width = ::width;
	swapchainDesc.Height = ::height;
	swapchainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapchainDesc.Stereo = FALSE;
	swapchainDesc.SampleDesc.Count = 1;
	swapchainDesc.SampleDesc.Quality = 0;
	swapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapchainDesc.BufferCount = 2;
	swapchainDesc.Scaling/*백 버퍼의 크기가 대상 출력과 같지 않은 경우 크기 조정 동작 - > 비율에 맞게 늘린다.*/= DXGI_SCALING_STRETCH;
	swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapchainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	swapchainDesc.Flags = 0;

	if (auto error = FAILED(dxgiFactory->CreateSwapChainForHwnd(device, hwnd, &swapchainDesc, nullptr, nullptr, &swapChain)))
	{
		MessageBox(nullptr, GetErrorMessage(error).c_str(), TEXT("Error"), MB_OK);
		exit(-1);
	}


	// 디바이스 / 컨텍스트 / 스압체인 생성
	/*
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
	*/

	// 렌더(render,그리다,draw) 타겟(백버퍼) - > 우리가 이미지를 그릴 버퍼(메모리)
	ID3D11Texture2D* backbuffer = nullptr;
	// 그래픽카드가 가진 백버퍼 정보를 가져온다.
	if (auto error = FAILED(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backbuffer))))
	{
		MessageBox(nullptr, GetErrorMessage(error).c_str(), TEXT("Error"), MB_OK);
		exit(-1);
	}

	// Create Render Target View(aka.RTV)
	if (auto error = FAILED(device->CreateRenderTargetView(backbuffer, nullptr/*버퍼에 이미 들어있다.*/, &RTV)))
	{
		MessageBox(nullptr, GetErrorMessage(error).c_str(), TEXT("Error"), MB_OK);
		exit(-1);
	}

	// backbuffer 해제
	// COM 구조로 되어있다. Component Object Model
	backbuffer->Release();

	// 항상 생성을 하고 할당을 하는일을 한다.

	context->OMSetRenderTargets(1/*개수*/, &RTV/*RTV*/, nullptr/*DSV*/);

	// 화면설정 (viewport)	보통 깊이값은 0~1 사이의 값으로 정규화를 거쳐 넣어준다.
	// viewport는 구현하기에 따라서 화면을 분할한다든지 다양하다.
	D3D11_VIEWPORT viewPort = {};
	viewPort.TopLeftX = 0.f;
	viewPort.TopLeftY = 0.f;
	viewPort.Width = static_cast<float>(::width);
	viewPort.Height = static_cast<float>(::height);
	viewPort.MinDepth = 0.f;
	viewPort.MaxDepth = 1.f;

	// Setting ViewPort
	context->RSSetViewports(1, &viewPort);



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
		// PAINTSTRUCT = 창의 클라이언트 영역에 그리는데 필요한 데이터의 구조체
		PAINTSTRUCT ps;
		// BeginPaint 함수는 인자로 덪칠할 창의 핸들과 정보를 받아올 페인트구조체를 넣어 그릴 준비를 해준다..
		HDC hdc = BeginPaint(hwnd, &ps);

		// All painting occurs here, between BeginPaint and EndPaint. / 모든 그리는 것은 Beginpaint 와 EndPaint 사이에서 일어난다.

		// FillRect 에서는 핸들의 프로그램에 ps안의 클라이언트 영역의 대한 정보를 토대로 브러쉬로 사각형(클라이언트영역)을 채운다.
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		// 페인팅 끝
		EndPaint(hwnd, &ps);
		return 0;
	}
	}

	// 메시지를 처리한 결과를 리턴하며 이 결과는 메시지에 따라 다르다. 윈도우 프로시저는 이 함수가 리턴한 값을 다시 리턴해 주어야 한다.
	return DefWindowProc(hwnd/*메시지를 받은 윈도우의 핸들*/, uMsg/*메시지 구조체*/, wParam/*메시지 정보*/, lParam/*메시지 정보*/);
}

void InitializeScene()
{
	// 정점(Vertex) 데이터 생성
	struct Vertex
	{
		float x, y, z;
	};

	// 점 데이터		// 뷰포트 좌표계를 쓴다. 클라이언트 영역의 중앙이 0.0 좌 1.0 우 -1.0 상 1.0 하 - 1.0 NDC
	Vertex vertices[] =
	{
		{0.f,0.5f,0.5f},
		{0.5f,-0.5f,0.5f},
		{-0.5f,-0.5f,0.5f}
	};

	::vertexByteWidth = sizeof(Vertex);
	::vertexCount = ARRAYSIZE(vertices);

	D3D11_BUFFER_DESC VertexBufferDesc = {};
	VertexBufferDesc.ByteWidth /*전체 바이트 크기*/ = vertexByteWidth * vertexCount;
	VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA VertexData = {};
	VertexData.pSysMem/*버텍스버퍼를 읽어올 시작지점*/ = vertices;

	// Create VertexBuffer
	if (auto error = device->CreateBuffer(/*버퍼의 데이터*/&VertexBufferDesc,/*버퍼의 실제 데이터*/&VertexData,/*반환 버퍼*/&Vertexbuffer))
	{
		MessageBox(nullptr, GetErrorMessage(error).c_str(), TEXT("Error"), MB_OK);
		exit(-1);
	}

	// 셰이더(shader - 그래픽 카드에서 사용하는 프로그램) 생성 ( 정점 셰이더(VertexShader)/ 픽셀 셰이더(PixelShader))
	// 1. 컴파일
	// 2. 컴파일된 이진 파일 로드

	 // VS
	ID3DBlob* vertexShaderBuffer = nullptr;
	if (auto error = D3DCompileFromFile(TEXT("Shader//VertexShader.hlsl"), nullptr, nullptr, "main", "vs_5_0", 0, 0,/*컴파일된 이진파일*/&vertexShaderBuffer,/*메모리*/nullptr))
	{
		MessageBox(nullptr, GetErrorMessage(error).c_str(), TEXT("Error"), MB_OK);
		exit(-1);
	}
	// 3. 셰이더 생성
	if (auto error = ::device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), nullptr, &::vertexShader))
	{
		MessageBox(nullptr, GetErrorMessage(error).c_str(), TEXT("Error"), MB_OK);
		exit(-1);
	}

	// PS
	ID3DBlob* PixelShaderBuffer = nullptr;
	if (auto error = D3DCompileFromFile(TEXT("Shader//PixelShader.hlsl"), nullptr, nullptr, "main", "ps_5_0", 0, 0,/*컴파일된 이진파일*/&PixelShaderBuffer,/*메모리*/nullptr))
	{
		MessageBox(nullptr, GetErrorMessage(error).c_str(), TEXT("Error"), MB_OK);
		exit(-1);
	}
	// 3. 셰이더 생성
	if (auto error = ::device->CreatePixelShader(PixelShaderBuffer->GetBufferPointer(), PixelShaderBuffer->GetBufferSize(), nullptr, &::pixelShader))
	{
		MessageBox(nullptr, GetErrorMessage(error).c_str(), TEXT("Error"), MB_OK);
		exit(-1);
	}




	// D3D11_INPUT_ELEMENT_DESC 
	/*
	LPCSTR	SemanticName; 시맨틱을 문자열로 달라는 것이다.
	UINT	SemanticIndex; 시맨틱 뒤의 숫자를 줘야한다.
	DXGI_FORMAT Format; 데이터 바이트
	UINT InputSlot; 해당 데이터의 인덱스
	UINT AlignedByteOffset; 버퍼에 위치,색,텍스처 등등 데이터가 들어가는데 어느시점부터 어디까지 읽어야 하는지 버퍼의 byte의 시작주소를 넘겨줘야한다. 현재 사용x
	D3D11_INPUT_CLASSIFICATION InputSlotClass; 인스턴싱을 사용할것인지
	UINT InstanceDataStepRate;
	*/

	// 인스턴싱 = 같은 모델링 데이터를 묶어서 처리해야한다.
	D3D11_INPUT_ELEMENT_DESC inputElementDecs[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0u,0u,D3D11_INPUT_PER_VERTEX_DATA,0u},
	};

	// 입력 레이아웃 생성 (입력 = 정점, 정점의 생김새)
	if (auto error = device->CreateInputLayout(inputElementDecs, ARRAYSIZE(inputElementDecs), vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &inputlayout))
	{
		MessageBox(nullptr, GetErrorMessage(error).c_str(), TEXT("Error"), MB_OK);
		exit(-1);
	}


}

void Draw()
{
	// 현재 사용된 swapCahin에서 스압체인 이펙트에서 백버퍼의 내용을 버리는 것을 하면 켜줘야 한다. 또한 밑의 Present1을 쓰면 다시 버퍼의 내용을 플래스 수정을 해야한다.
	//context->OMSetRenderTargets(1, &RTV, nullptr);

	//리소스를 생성할땐 device를 쓰며, 사용할 땐 context를 사용한다.
	// 1. beginrender	-> 배경 지우기.
	float Clearcolor[] = { 0.5f,0.5f ,1.f ,1.f };	// 물감은 계속섞으면 검정색이 되며 빛은 계속 섞으면 횐색이된다.
	context->ClearRenderTargetView(RTV, Clearcolor);
	// 2. render		-> 장면 그리기.
	{
		//데이터 /셰이더 설정 (뭘 먼저하든 상관 x)
		{
			// 점을 연결해서 면을 만들 때 기준이 되는 방식을 지정함
			context->IASetPrimitiveTopology(/*정점을 무엇을 기준으로 그리는 방식을 설명한다. -> 들어오는 순서대로 3개씩 삼각형을 그린다.*/D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			/*드로우콜 때마다 생성-삭제 반복을 줄여준다.*/static unsigned int stride /*xyzw(위치)xyzw(색).. 등등 4개씩 끊어쓸건지*/= ::vertexByteWidth;
			/*드로우콜 때마다 생성-삭제 반복을 줄여준다.*/static unsigned int offset/**/= 0u;
			context->IASetVertexBuffers(0,1,&::Vertexbuffer,&stride,&offset);
			context->IASetInputLayout(::inputlayout);

			// 셰이더 설정
			context->VSSetShader(::vertexShader, nullptr,0);
			context->PSSetShader(::pixelShader, nullptr, 0);
		}
	}

	context->Draw(vertexCount,0); // 드로우 콜  드로우콜을 하면 렌더링 파이프라인 토대로 프레임워크가 돈다.

	// Endrender	-> 스압체인 교환.
	swapChain->Present(/*vSync 사용유무(모니터 주사율과 동기화를 할것인가) = 사용한다 1*/1u,0u);
}
