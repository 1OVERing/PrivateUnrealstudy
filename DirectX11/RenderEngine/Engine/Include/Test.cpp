#include "Test.h"

__declspec(dllexport) void STL::Show(const wchar_t* message)
{
	MessageBox(nullptr, message, L"STL Engine", MB_OK);
}