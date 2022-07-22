#pragma once
#include <Core/Core.h>

namespace STL
{
	class ENGINE_API Window
	{
	private: // Member Variable
		std::wstring classname;		// 창 등록시 사용할 클래스 이름
		std::wstring title;			// 창 제목
		HINSTANCE hInstance;			// 창을 생성하는 프로그램의 포인터(주소)
		HWND handle;				// 생성된 창을 가리키는 포인터(주소)
		uint32 width;				// 창의 가로 크기
		uint32 height;				// 창의 세로 크기
		WNDPROC procedure;			// 창 이벤트(클릭,키보드 입력 등)를 처리할 함수 포인터

	public: // Member Varuable Set/Get
		std::wstring Title() const { return title; }
		HINSTANCE Instance() const { return hInstance; }
		HWND Handle() const { return handle; }
		uint32 Width() const { return width; }
		uint32 Height() const { return height; }



		void SetTitle(const std::wstring& newTitle);
	public: // Member Function
		void Intialize();



	public: // operator overLoading
		Window& operator=(const Window& p) = delete; // 복사 이동 연산자 선언
		Window& operator=(Window&& p) noexcept = delete; // 이동 복사 연산자 선언
	public: // constructor / destructor
		Window(HINSTANCE hinstance, uint32 w, uint32 h, const std::wstring& title, WNDPROC procedure);
		~Window();
		Window(const Window& other) = delete;
		Window(const Window&& other) noexcept = delete;
	};
}
