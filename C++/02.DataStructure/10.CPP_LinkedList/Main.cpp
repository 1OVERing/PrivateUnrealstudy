#include "LinkedList.h"
#include <iostream>
#include <string>
int main()
{
	LinkedList* list = new LinkedList;
	std::string data;


	for (;;)
	{
		std::cout << "�߰��� �����͸� �Է����ּ��� ( ����� q )" << std::endl;
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
		std::cout << "������ �����͸� �Է����ּ��� ( ����� q )" << std::endl;
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