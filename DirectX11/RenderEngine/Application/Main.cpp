#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <tchar.h>
#include <string>

// DirectX11 ���.
#include <d3d11.h>
#include <d3dcompiler.h> // ���̴� �����Ϸ� ��� ����

// lib ��ŷ			��ó�� �Ἥ lib�� ������ �� ������ �ƴϸ� �ɼ��� ��ũ�� �Է¿� �߰��ϸ�ȴ�.
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")


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
IDXGISwapChain* swapChain = nullptr;





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

void InializeDevice()
{
	unsigned int Flag = 0;

#if _DEBUG
	// ����� ����� ���
	// ��ġ ���� �������� ������ �߻����� �� ����� ������ �� ���� �����ش޶�� �ɼ� �߰�.
	Flag ^= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// DX11 ���� ����
	// ���� ������ �տ� ������ ���� �õ��غ��� �������� ������ ���� �������� �Ѿ��.
	D3D_FEATURE_LEVEL level[] = { D3D_FEATURE_LEVEL_11_1 , D3D_FEATURE_LEVEL_11_0 };

	// ����ü�� ������ ���� ����ü ����
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

	swapChainDesc.BufferCount = 1; // ����� ���� ����
	swapChainDesc.BufferDesc.Width = ::width;	// ������ �ʺ�
	swapChainDesc.BufferDesc.Height = ::height;	// ������ ����
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;// �̹��� ä�κ� ����
	swapChainDesc.Windowed = true;				// â ��� ����
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;// ������(�̹���)�� �뵵 ���� = ������
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;// ����Ʈ <-> �� ���� ������ �� ȿ�� ������ ����
	swapChainDesc.SampleDesc.Count = 1;			// ��Ƽ���ø� ���� ���� -> 1 ����
	swapChainDesc.SampleDesc.Quality = 0;		// ��Ƽ���ø� ǰ�� ���� -> �⺻ ��(count - 1)
	swapChainDesc.OutputWindow = hwnd;			// DX�� �׸� â �ڵ�

	D3D_FEATURE_LEVEL finaFeature;


	D3D11CreateDevice(nullptr,D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE);
	

	// ����̽� / ���ؽ�Ʈ / ����ü�� ����
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

	// ���п��� Ȯ��
	S_OK;
	E_FAIL;
	if (FAILED(result))
	{
		MessageBox(nullptr,TEXT("Failed to create device."), TEXT("Error"),MB_OK);
		exit(-1);
	}
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