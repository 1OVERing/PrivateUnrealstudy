#include "Core.h"
#include "Test.h"

namespace Ronnie
{
	void Show(const wchar_t* message)
	{
		MessageBox(nullptr, message, L"STL Engine", 0);
	}
}