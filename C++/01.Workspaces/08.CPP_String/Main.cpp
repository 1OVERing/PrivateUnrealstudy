#include "../Global.h"


int main()
{
	const char* name = "이호근";
	const wchar_t* wname = L"이호근";
	const char16_t* wname16 = u"이호근";
	const char32_t* wname32 = U"이호근";

	std::cout << &wname << std::endl;
	std::cin.get();
}