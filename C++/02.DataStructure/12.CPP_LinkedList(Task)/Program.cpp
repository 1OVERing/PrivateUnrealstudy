#include "Program.h"
#include <Windows.h>
void Program::InsertLoop(ContactList** list)
{
	std::wstring name;

	while (true)
	{
		std::wcout << L"추가할 연락처의 이름을 입력하세요 *종료는 q\n";
		std::wcin >> name;
		if (name == L"q" || name == L"Q")
			break;

		(*list)->Insert(name);
		(*list)->Print();
	}
}

void Program::DeleteLoop(ContactList** list)
{
	std::wstring name;

	while (true)
	{
		std::wcout << L"삭제할 연락처의 이름을 입력하세요 *종료는 q\n";
		std::wcin >> name;

		if (name == L"q" || name == L"Q")
			break;

		(*list)->DeleteNode(name);
		(*list)->Print();
	}
}
