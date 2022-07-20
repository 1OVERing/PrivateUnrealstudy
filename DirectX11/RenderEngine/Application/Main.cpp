#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <tchar.h>
#include <string>

// DirectX11 ���.
#include <d3d11.h>
#include <d3dcompiler.h>	// ���̴� �����Ϸ� ��� ����
#include <dxgi1_3.h>

// lib ��ŷ	��ó�� �Ἥ lib�� ������ �� ������ �ɼ��� ��ũ�� �Է¿� �߰����Ӽ����� �߰� �ϸ�ȴ�.
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dxgi.lib")

void InializeDevice();

// ���� ����
std::wstring className = TEXT("Direct3D Window class");		// â Ŭ���� �̸�
std::wstring TitleName = TEXT("Direct3D Render Engine");	// â Ÿ��Ʋ �̸�
HWND hwnd = nullptr;				// ���α׷� �ڵ�
HINSTANCE hInstance = nullptr;	// ���α׷� �ڵ� �ν��Ͻ�
long width = 1280;					// â�� �ʺ�
long height = 720;					// â�� ����

// DX ���� ����
ID3D11Device* device = nullptr;
ID3D11DeviceContext* context = nullptr;

IDXGISwapChain1* swapChain = nullptr;
// �Լ� ���漱��
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// __stdcall , __cdecl�� ����
/*
__stdcall = WINAPI __cdecl = WINAPIV
������(�ý���) �Լ� ����� stack �޸𸮿� ���δ�. �� ���� �� �޸𸮸� ��ü�� ��� ������ �޸� ������ ��ü�� �����̳Ŀ� ���� ���� �ٸ���.
__stdcall = �Լ� ��ü���� �޸� ������ ����Ѵ�.
__cdecl = caller��� �ְ� �޸� ������ ����Ѵ�.
*/
// wWinMain�Լ��� ���ڿ� ����
/* ���ڴ� windows.h - > winbase.h - >
wwinmain�Լ� ������ �Ķ���Ͱ��� �J��� ������ش�.*/
// _In_ , _In_opt_�� ����
/* _In_, _In_opt_ �� ������ �ý��� ���α׷����Ҷ��� ���Ǹ�,
�Ķ������ input output�� ��������� ���ش�.*/

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	//=================================================================================================== â ����
	::hInstance = hInstance; // ::(������ : ����� ���������� ����ϱ� ���� ���δ�.)

	// Register the window class.
	// WNDCLASS = ������ â�� ���� �ʿ��� �����͸� ���� ����ü
	WNDCLASS wc = { };

	// ���������ν��� ( â������ �޼��� ó�� �Լ� ) // Invoke(����ȣ�� ���) ����(Delegate)/ callback ���. �Լ��� ��ġ�� �˷��ְ� Ư�� ��Ȳ�� �����찡 ȣ�����ش�.
	wc.lpfnWndProc = WindowProc;
	// ���α׷��� �ڵ� �ν��Ͻ�
	wc.hInstance = hInstance;
	// ������ â�� �̸�
	wc.lpszClassName = className.c_str();

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
	::hwnd = CreateWindowEx(0,/*Optional window styles.*/className.c_str()/*Window class*/,TitleName.c_str()/*Window text*/,WS_OVERLAPPEDWINDOW/*Window style*/,
		// setting window Size and position
		xpos, ypos, windowWidth, windowHeight,

		nullptr,		// Parent window	( �θ� â�� ���� ������ )
		nullptr,		// Menu				( �޴�â ������ )
		hInstance,		// Instance handle	( ���α׷� �ڵ� �ν��Ͻ� )
		nullptr			// Additional application data	( �ΰ� ������ ) â�� ����ü���� �����͸� �Ѱ� ����� �� �ִ�.
	);

	if (::hwnd == nullptr)
	{
		return 0;
	}
	/////////////////////////////////////wc.hbrBackground = WHITE_BRUSH;
	ShowWindow(::hwnd, SW_SHOW); // â ����
	UpdateWindow(::hwnd);	// â ������Ʈ
	//=================================================================================================== DX �ʱ�ȭ
	InializeDevice();
	//=================================================================================================== �޽��� ����
	MSG msg = { };
	
	// �޼����� Ȯ���ϸ� ������� WM_QUIT �޼����� �ƴ϶�� ��� ����.
	while (msg.message != WM_QUIT/*GetMessage(&msg, nullptr, 0, 0) > 0*/)
	{
		if (PeekMessage(&msg,nullptr,0u,0u,PM_REMOVE))
		{
			// ������ (os)�� ������ �޽��� �ؼ�
			TranslateMessage(&msg);
			// �� ����(������ ���ν��� �Լ� ȣ��)
			DispatchMessage(&msg);
		}
		else
		{

		}
	}

	// â ��� ����
	UnregisterClass(className.c_str(),hInstance);
	
	return 0;
}

// DX ����̽� �ʱ�ȭ
void InializeDevice()
{
	unsigned int Flag = 0;

#if _DEBUG
	// ����� ����� ���
	// ��ġ ���� �������� ������ �߻����� �� ����� ������ �� ���� �����ش޶�� �ɼ� �߰�.
	Flag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	Flag |= D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	// DX11 ���� ����
	// ���� ������ �տ� ������ ���� �õ��غ��� �������� ������ ���� �������� �Ѿ��.
	D3D_FEATURE_LEVEL level[] = { D3D_FEATURE_LEVEL_11_1 , D3D_FEATURE_LEVEL_11_0 };

	// ����ü�� ������ ���� ����ü ����
	//DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};

	//swapChainDesc.BufferCount/*����� ���� ����*/ = 1;
	//swapChainDesc.BufferDesc.Width/*������ �ʺ�*/ = ::width;
	//swapChainDesc.BufferDesc.Height/*������ ����*/ = ::height;
	//swapChainDesc.BufferDesc.RefreshRate.Numerator/*�������� ����*/ = 60;
	//swapChainDesc.BufferDesc.RefreshRate.Denominator/*�������� �и�*/= 1;
	//swapChainDesc.BufferDesc.Format/*�̹��� ä�κ� ����*/ = DXGI_FORMAT_R8G8B8A8_UNORM;
	//swapChainDesc.BufferUsage/*������(�̹���)�� �뵵 ���� = ������*/ = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//swapChainDesc.BufferDesc.ScanlineOrdering/*�����Ͱ� ǥ�鿡 �̹����� ����� ��� �÷���*/ = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	//swapChainDesc.BufferDesc.Scaling/*����� �ػ󵵿� �°� �̹��� �ø� ���*/ = DXGI_MODE_SCALING_UNSPECIFIED;

	//swapChainDesc.Windowed/*â ��� ����*/ = true;
	//swapChainDesc.SwapEffect/*����Ʈ <-> �� ���� ������ �� ȿ�� ������ ����*/ = DXGI_SWAP_EFFECT_DISCARD;
	//swapChainDesc.SampleDesc.Count/*��Ƽ���ø� ���� ���� -> 1 ����*/ = 1;
	//swapChainDesc.SampleDesc.Quality/*��Ƽ���ø� ǰ�� ���� -> �⺻ ��(count - 1)*/= 0;
	//swapChainDesc.OutputWindow/*DX�� �׸� â �ڵ�*/= hwnd;
	//swapChainDesc.Flags/*���� ü�� ���ۿ� ���� �ɼ��� �����ϴ� DXGI_SWAP_CHAIN_FLAG*/= 0;

	D3D_FEATURE_LEVEL finaFeature = {};
	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, nullptr, Flag, level, ARRAYSIZE(level), D3D11_SDK_VERSION, &device, &finaFeature, &context)))
	{
		// D3D11CreateDevice�� ���� ����
		/*
		HRESULT WINAPI D3D11CreateDevice(
		_In_opt_ IDXGIAdapter*										pAdapter,			. ��ġ�� ������ �� ���� ���� ������� ���� ������ 0/nullptr �� ������ �⺻ ����Ͱ� �����ȴ�.
		D3D_DRIVER_TYPE												DriverType,			. ���� �� ����̹� ������ ��Ÿ���� D3D_DRIVER_TYPE
		HMODULE														Software,			. ����Ʈ���� �����Ͷ������� �����ϴ� DLL�� ���� �ڵ�
		UINT														Flags,				. D3D11_CREATE_DEVICE_FLAG
		_In_reads_opt_( FeatureLevels ) CONST D3D_FEATURE_LEVEL*	pFeatureLevels,		. ������ �õ��ϴ� ��� ������ ������ �����ϴ� D3D_FEATURE_LEVEL �迭�� ���� ������ �����-������ ������ �����Ѵ�.
		UINT														FeatureLevels,		. pFeatureLevels�� �迭 ����� ����
		UINT														SDKVersion,			. SDK�� ���� D3D11_SDK_VERSION ���� ����
		_COM_Outptr_opt_ ID3D11Device**								ppDevice,			. ����̽� ������
		_Out_opt_ D3D_FEATURE_LEVEL*								pFeatureLevel,		. �����ϸ� ������ pFeatureLevels �迭 ���� ù ��° D3D_FEATURE_LEVEL �� ��ȯ
		_COM_Outptr_opt_ ID3D11DeviceContext**						ppImmediateContext	.
		);
		*/
		MessageBox(nullptr, TEXT("D3D11CreateDevice Error"), TEXT("Error"), MB_OK);
		exit(-1);
	}

	GUID guid = {};
	IDXGIDevice* dxgiDevice = nullptr;
	if (FAILED(device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice)))
	{
		MessageBox(nullptr, TEXT("device->QueryInterface Error"), TEXT("Error"), MB_OK);
		exit(-1);
	}
	
	IDXGIAdapter* adapter = nullptr;
	if (FAILED(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&adapter)))
	{
		MessageBox(nullptr, TEXT("dxgiDevice->GetParent Error"), TEXT("Error"), MB_OK);
		exit(-1);
	};

	IDXGIFactory2* dxgiFactory = nullptr;
	if (FAILED(adapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory)))
	{
		MessageBox(nullptr, TEXT("adapter->GetParent Error"), TEXT("Error"), MB_OK);
		exit(-1);
	}
	DXGI_SWAP_CHAIN_FULLSCREEN_DESC Desc = {};
	Desc.RefreshRate.Denominator = 1;
	Desc.RefreshRate.Numerator = 60;
	Desc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	Desc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	Desc.Windowed = true;

	// https://docs.microsoft.com/en-us/windows/win32/api/dxgi1_2/ns-dxgi1_2-dxgi_swap_chain_desc1
	DXGI_SWAP_CHAIN_DESC1 swapchainDesc = {};
	swapchainDesc.Width			= ::width;
	swapchainDesc.Height		= ::height;
	swapchainDesc.Format		= DXGI_FORMAT_R8G8B8A8_UNORM;
	swapchainDesc.Stereo		= FALSE;
	swapchainDesc.SampleDesc.Count		= 1;
	swapchainDesc.SampleDesc.Quality	= 0;
	swapchainDesc.BufferUsage	= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapchainDesc.BufferCount	= 1;
	swapchainDesc.Scaling		= DXGI_SCALING_ASPECT_RATIO_STRETCH;
	swapchainDesc.SwapEffect	= DXGI_SWAP_EFFECT_DISCARD;
	swapchainDesc.AlphaMode		= DXGI_ALPHA_MODE_STRAIGHT;
	swapchainDesc.Flags			= 0;

	if (FAILED(dxgiFactory->CreateSwapChainForHwnd(device, hwnd, &swapchainDesc, nullptr, nullptr, &swapChain)))
	{
		MessageBox(nullptr, TEXT("dxgiFactory->CreateSwapChainForHwnd Error"), TEXT("Error"), MB_OK);
		exit(-1);
	}


	// ����̽� / ���ؽ�Ʈ / ����ü�� ����
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
			);	// ����̽�, ���ؽ�Ʈ , ����ü���� �ѹ��� �����. �ڼ��� ������ ���ε��� �ؾ��Ѵ�.
	*/
}

// ������ ���ν��� �Լ�
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY: // â�� ������ ��
	{	
		PostQuitMessage(0); // â�� ����Ǿ����� ���α׷� ���� �޽���
		return 0; // 1�� �������� 0�� �������� ����Ǿ��� �� ���ȴ�.
	}
	case WM_KEYDOWN: // ��� Ű�� ������ ��
	{
		if (wParam == VK_ESCAPE)
		{
			if (MessageBox(nullptr/*�θ� �ڵ�*/, TEXT("Quit?")/*�޼��� ����*/, TEXT("Quit Engine")/*�޽��� �ڽ� �̸�*/, MB_YESNO/*�ڽ��� Ÿ��(YES/NO �ڽ�)*/) == IDYES/*���� ���� ��*/)
				DestroyWindow(hwnd); // â ����
		}
	}
	case WM_PAINT: // â�� �׷��� �� ��
	{
		// PAINTSTRUCT = â�� Ŭ���̾�Ʈ ������ �׸��µ� �ʿ��� �������� ����ü
		PAINTSTRUCT ps;
		// BeginPaint �Լ��� ���ڷ� �Cĥ�� â�� �ڵ�� ������ �޾ƿ� ����Ʈ����ü�� �־� �׸� �غ� ���ش�..
		HDC hdc = BeginPaint(hwnd, &ps);

		// All painting occurs here, between BeginPaint and EndPaint. / ��� �׸��� ���� Beginpaint �� EndPaint ���̿��� �Ͼ��.

		// FillRect ������ �ڵ��� ���α׷��� ps���� Ŭ���̾�Ʈ ������ ���� ������ ���� �귯���� �簢��(Ŭ���̾�Ʈ����)�� ä���.
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		
		// ������ ��
		EndPaint(hwnd, &ps);
		return 0;
	}
	}

	// �޽����� ó���� ����� �����ϸ� �� ����� �޽����� ���� �ٸ���. ������ ���ν����� �� �Լ��� ������ ���� �ٽ� ������ �־�� �Ѵ�.
	return DefWindowProc(hwnd/*�޽����� ���� �������� �ڵ�*/, uMsg/*�޽��� ����ü*/, wParam/*�޽��� ����*/, lParam/*�޽��� ����*/);
}