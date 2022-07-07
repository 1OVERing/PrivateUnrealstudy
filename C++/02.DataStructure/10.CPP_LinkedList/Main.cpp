#include "LinkedList.h"
#include <iostream>
#include <string>
int main()
{
	LinkedList* list = new LinkedList;
	std::string data;


	for (;;)
	{
		std::cout << "추가할 데이터를 입력해주세요 ( 종료는 q )" << std::endl;
		std::cin >> data;
		if (data == "q" || "Q" == data)
		{
			break;
		}
		list->Insert(std::stoi(data));
	}

	list->Print();

	for (;;)
	{
		std::cout << "삭제할 데이터를 입력해주세요 ( 종료는 q )" << std::endl;
		std::cin >> data;
		if (data == "q" || "Q" == data)
		{
			break;
		}

		list->DeletData(std::stoi(data));
	}

	system("cls");
	list->Print();
	delete list;
	std::cin.get();
}