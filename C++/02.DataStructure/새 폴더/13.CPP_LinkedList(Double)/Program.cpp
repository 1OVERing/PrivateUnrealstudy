#include "Program.h"

using std::cout;
using std::cin;
using std::endl;

void OnListError()
{
	std::cout << "LinkedList에서 오류가 발생했습니다.\n";
}

Program::Program()
{
	list = new LinkedList<std::string>(OnListError);
}

Program::~Program()
{
	delete list;
}


void Program::InsertLoop()
{
	system("cls");
	cout << "-----------데이터추가-----------\n";
	std::string name;

	while (true)
	{
		cout << "추가할 연락처의 이름을 입력하세요 : 종료(q)\n";
		cin >> name;

		if ("q" == name || "Q" == name)
			break;

		list->PushLast(name);
	}
	list->Print();
}

void Program::DeleteLoop()
{
	system("cls");
	cout << "-----------데이터삭제-----------\n";
	std::string name;

	while (true)
	{
		cout << "삭제할 연락처의 이름을 입력하세요 : 종료(q)\n";
		cin >> name;

		if ("q" == name || "Q" == name)
			break;

		list->Delete(name);
	}
	list->Print();
}