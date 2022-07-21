#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <tchar.h>
#include <string>

#include <time.h> // 
#include <cmath>  // �ﰢ�Լ� ���� ����ϱ� ���� ��� �߰�

// DirectX11 ���.
#include <d3d11.h>
#include <d3dcompiler.h>	// ���̴� �����Ϸ� ��� ����
#include <dxgi1_3.h>	// swapchain ���������� DXGIŬ����. ���丮 ����� ���� ���
#include <comdef.h>	//

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

IDXGIDevice* dxgiDevice = nullptr;
IDXGIAdapter* adapter = nullptr;
IDXGISwapChain1* swapChain = nullptr;
IDXGIFactory2* dxgiFactory = nullptr;
ID3D11RenderTargetView* RTV = nullptr;
// ���� ���� ����
unsigned int	vertexByteWidth = 0u;
unsigned int	vertexCount = 0u;
ID3D11Buffer* Vertexbuffer = nullptr;

ID3D11VertexShader* vertexShader = nullptr;
ID3D11PixelShader* pixelShader = nullptr;
ID3D11InputLayout* inputlayout = nullptr;

// �Լ� ���漱��
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void InitializeScene();
void Draw();



// ���� �޽��� ����� ���� �Լ�
std::wstring GetErrorMessage(HRESULT hr)
{
	_com_error error(hr);
	return error.ErrorMessage();
}


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
	::hwnd = CreateWindowEx(0,/*Optional window styles.*/className.c_str()/*Window class*/, TitleName.c_str()/*Window text*/, WS_OVERLAPPEDWINDOW/*Window style*/,
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
	//=================================================================================================== ��� �ʱ�ȭ
	InitializeScene();
	//=================================================================================================== �޽��� ����
	MSG msg = { };

	// �޼����� Ȯ���ϸ� ������� WM_QUIT �޼����� �ƴ϶�� ��� ����.
	while (msg.message != WM_QUIT/*GetMessage(&msg, nullptr, 0, 0) > 0*/)
	{
		if (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
		{
			// ������ (os)�� ������ �޽��� �ؼ�
			TranslateMessage(&msg);
			// �� ����(������ ���ν��� �Լ� ȣ��)
			DispatchMessage(&msg);
		}
		else
		{
			// �̹��� �׸���
			Draw();
		}
	}

	// â ��� ����
	UnregisterClass(className.c_str(), hInstance);

	return 0;
}

// DX ����̽� �ʱ�ȭ
void InializeDevice()
{
	unsigned int Flag = 0;

#if _DEBUG
	// ����� ����� ���
	// ��ġ ���� �������� ������ �߻����� �� ����� ������ �� ���� �����ش޶�� �ɼ� �߰�.
	Flag = D3D11_CREATE_DEVICE_DEBUG;	// ����׽� ���â�� DX������ ����ش�.
#endif

	Flag |= D3D11_CREATE_DEVICE_BGRA_SUPPORT; // BGRA ����

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
	if (auto error = (D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, nullptr, Flag, level, ARRAYSIZE(level), D3D11_SDK_VERSION, &device, &finaFeature, &context)))
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
		MessageBox(nullptr, GetErrorMessage(error).c_str(), TEXT("Error"), MB_OK);
		exit(-1);
	}

	GUID guid = {};
	// QueryInterface �� Dx�ֻ��� ��ü�� IUnKnown ��ü�� �Լ��̸�, ù��° ������ Ŭ������ �������ִ� ��Ȱ�� �Ѵ�.
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
	swapchainDesc.Scaling/*�� ������ ũ�Ⱑ ��� ��°� ���� ���� ��� ũ�� ���� ���� - > ������ �°� �ø���.*/= DXGI_SCALING_STRETCH;
	swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapchainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	swapchainDesc.Flags = 0;

	if (auto error = FAILED(dxgiFactory->CreateSwapChainForHwnd(device, hwnd, &swapchainDesc, nullptr, nullptr, &swapChain)))
	{
		MessageBox(nullptr, GetErrorMessage(error).c_str(), TEXT("Error"), MB_OK);
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

	// ����(render,�׸���,draw) Ÿ��(�����) - > �츮�� �̹����� �׸� ����(�޸�)
	ID3D11Texture2D* backbuffer = nullptr;
	// �׷���ī�尡 ���� ����� ������ �����´�.
	if (auto error = FAILED(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backbuffer))))
	{
		MessageBox(nullptr, GetErrorMessage(error).c_str(), TEXT("Error"), MB_OK);
		exit(-1);
	}

	// Create Render Target View(aka.RTV)
	if (auto error = FAILED(device->CreateRenderTargetView(backbuffer, nullptr/*���ۿ� �̹� ����ִ�.*/, &RTV)))
	{
		MessageBox(nullptr, GetErrorMessage(error).c_str(), TEXT("Error"), MB_OK);
		exit(-1);
	}

	// backbuffer ����
	// COM ������ �Ǿ��ִ�. Component Object Model
	backbuffer->Release();

	// �׻� ������ �ϰ� �Ҵ��� �ϴ����� �Ѵ�.

	context->OMSetRenderTargets(1/*����*/, &RTV/*RTV*/, nullptr/*DSV*/);

	// ȭ�鼳�� (viewport)	���� ���̰��� 0~1 ������ ������ ����ȭ�� ���� �־��ش�.
	// viewport�� �����ϱ⿡ ���� ȭ���� �����Ѵٵ��� �پ��ϴ�.
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

void InitializeScene()
{
	// ����(Vertex) ������ ����
	struct Vertex
	{
		float x, y, z;
	};

	// �� ������		// ����Ʈ ��ǥ�踦 ����. Ŭ���̾�Ʈ ������ �߾��� 0.0 �� 1.0 �� -1.0 �� 1.0 �� - 1.0 NDC
	Vertex vertices[] =
	{
		{0.f,0.5f,0.5f},
		{0.5f,-0.5f,0.5f},
		{-0.5f,-0.5f,0.5f}
	};

	::vertexByteWidth = sizeof(Vertex);
	::vertexCount = ARRAYSIZE(vertices);

	D3D11_BUFFER_DESC VertexBufferDesc = {};
	VertexBufferDesc.ByteWidth /*��ü ����Ʈ ũ��*/ = vertexByteWidth * vertexCount;
	VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA VertexData = {};
	VertexData.pSysMem/*���ؽ����۸� �о�� ��������*/ = vertices;

	// Create VertexBuffer
	if (auto error = device->CreateBuffer(/*������ ������*/&VertexBufferDesc,/*������ ���� ������*/&VertexData,/*��ȯ ����*/&Vertexbuffer))
	{
		MessageBox(nullptr, GetErrorMessage(error).c_str(), TEXT("Error"), MB_OK);
		exit(-1);
	}

	// ���̴�(shader - �׷��� ī�忡�� ����ϴ� ���α׷�) ���� ( ���� ���̴�(VertexShader)/ �ȼ� ���̴�(PixelShader))
	// 1. ������
	// 2. �����ϵ� ���� ���� �ε�

	 // VS
	ID3DBlob* vertexShaderBuffer = nullptr;
	if (auto error = D3DCompileFromFile(TEXT("Shader//VertexShader.hlsl"), nullptr, nullptr, "main", "vs_5_0", 0, 0,/*�����ϵ� ��������*/&vertexShaderBuffer,/*�޸�*/nullptr))
	{
		MessageBox(nullptr, GetErrorMessage(error).c_str(), TEXT("Error"), MB_OK);
		exit(-1);
	}
	// 3. ���̴� ����
	if (auto error = ::device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), nullptr, &::vertexShader))
	{
		MessageBox(nullptr, GetErrorMessage(error).c_str(), TEXT("Error"), MB_OK);
		exit(-1);
	}

	// PS
	ID3DBlob* PixelShaderBuffer = nullptr;
	if (auto error = D3DCompileFromFile(TEXT("Shader//PixelShader.hlsl"), nullptr, nullptr, "main", "ps_5_0", 0, 0,/*�����ϵ� ��������*/&PixelShaderBuffer,/*�޸�*/nullptr))
	{
		MessageBox(nullptr, GetErrorMessage(error).c_str(), TEXT("Error"), MB_OK);
		exit(-1);
	}
	// 3. ���̴� ����
	if (auto error = ::device->CreatePixelShader(PixelShaderBuffer->GetBufferPointer(), PixelShaderBuffer->GetBufferSize(), nullptr, &::pixelShader))
	{
		MessageBox(nullptr, GetErrorMessage(error).c_str(), TEXT("Error"), MB_OK);
		exit(-1);
	}




	// D3D11_INPUT_ELEMENT_DESC 
	/*
	LPCSTR	SemanticName; �ø�ƽ�� ���ڿ��� �޶�� ���̴�.
	UINT	SemanticIndex; �ø�ƽ ���� ���ڸ� ����Ѵ�.
	DXGI_FORMAT Format; ������ ����Ʈ
	UINT InputSlot; �ش� �������� �ε���
	UINT AlignedByteOffset; ���ۿ� ��ġ,��,�ؽ�ó ��� �����Ͱ� ���µ� ����������� ������ �о�� �ϴ��� ������ byte�� �����ּҸ� �Ѱ�����Ѵ�. ���� ���x
	D3D11_INPUT_CLASSIFICATION InputSlotClass; �ν��Ͻ��� ����Ұ�����
	UINT InstanceDataStepRate;
	*/

	// �ν��Ͻ� = ���� �𵨸� �����͸� ��� ó���ؾ��Ѵ�.
	D3D11_INPUT_ELEMENT_DESC inputElementDecs[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0u,0u,D3D11_INPUT_PER_VERTEX_DATA,0u},
	};

	// �Է� ���̾ƿ� ���� (�Է� = ����, ������ �����)
	if (auto error = device->CreateInputLayout(inputElementDecs, ARRAYSIZE(inputElementDecs), vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &inputlayout))
	{
		MessageBox(nullptr, GetErrorMessage(error).c_str(), TEXT("Error"), MB_OK);
		exit(-1);
	}


}

void Draw()
{
	// ���� ���� swapCahin���� ����ü�� ����Ʈ���� ������� ������ ������ ���� �ϸ� ����� �Ѵ�. ���� ���� Present1�� ���� �ٽ� ������ ������ �÷��� ������ �ؾ��Ѵ�.
	//context->OMSetRenderTargets(1, &RTV, nullptr);

	//���ҽ��� �����Ҷ� device�� ����, ����� �� context�� ����Ѵ�.
	// 1. beginrender	-> ��� �����.
	float Clearcolor[] = { 0.5f,0.5f ,1.f ,1.f };	// ������ ��Ӽ����� �������� �Ǹ� ���� ��� ������ Ⱥ���̵ȴ�.
	context->ClearRenderTargetView(RTV, Clearcolor);
	// 2. render		-> ��� �׸���.
	{
		//������ /���̴� ���� (�� �����ϵ� ��� x)
		{
			// ���� �����ؼ� ���� ���� �� ������ �Ǵ� ����� ������
			context->IASetPrimitiveTopology(/*������ ������ �������� �׸��� ����� �����Ѵ�. -> ������ ������� 3���� �ﰢ���� �׸���.*/D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			/*��ο��� ������ ����-���� �ݺ��� �ٿ��ش�.*/static unsigned int stride /*xyzw(��ġ)xyzw(��).. ��� 4���� �������*/= ::vertexByteWidth;
			/*��ο��� ������ ����-���� �ݺ��� �ٿ��ش�.*/static unsigned int offset/**/= 0u;
			context->IASetVertexBuffers(0,1,&::Vertexbuffer,&stride,&offset);
			context->IASetInputLayout(::inputlayout);

			// ���̴� ����
			context->VSSetShader(::vertexShader, nullptr,0);
			context->PSSetShader(::pixelShader, nullptr, 0);
		}
	}

	context->Draw(vertexCount,0); // ��ο� ��  ��ο����� �ϸ� ������ ���������� ���� �����ӿ�ũ�� ����.

	// Endrender	-> ����ü�� ��ȯ.
	swapChain->Present(/*vSync �������(����� �ֻ����� ����ȭ�� �Ұ��ΰ�) = ����Ѵ� 1*/1u,0u);
}
