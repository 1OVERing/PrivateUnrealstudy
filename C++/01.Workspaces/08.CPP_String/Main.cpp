#include "../Global.h"


int main()
{
	const char* name = "��ȣ��";
	const wchar_t* wname = L"��ȣ��";
	const char16_t* wname16 = u"��ȣ��";
	const char32_t* wname32 = U"��ȣ��";

	std::cout << &wname << std::endl;
	std::cin.get();
}