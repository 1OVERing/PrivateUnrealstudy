#pragma once

#include "Core.h"

namespace Ronnie
{
	class ENGINE_API Window
	{
	public:
		Window() = default;
		~Window() = default;

		// √ ±‚»≠.
		bool Initialize(
			HINSTANCE hInstance,
			uint32 width,
			uint32 height,
			const std::wstring& title,
			WNDPROC wndproc
		);

		HINSTANCE Instance();
		HWND WindowHandle();
		uint32 Width();
		uint32 Height();
		std::wstring Title();
		void SetTitle(const std::wstring& title);

	private:
		HINSTANCE instance;
		HWND windowHandle;
		uint32 width;
		uint32 height;
		std::wstring title;
	};
}