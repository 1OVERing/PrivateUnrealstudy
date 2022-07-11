#include <iostream>
#include <Windows.h>
#include "Hashtable.h"
using std::cout;
using std::cin;
using std::endl;

int main()
{
	HashTable table;
	while (true)
	{
		std::string key = {};
		std::string value = {};
		system("cls");
		cout << "메뉴를 입력해주세요\n";
		cout << "#데이터 추가 #데이터 삭제 #데이터 검색 #데이터 열람 #종료\n";
		cin >> key;
		
		if ("종료" == key)
			break;

		std::string key2 = {};
		cin >> key2;
		key += " ";
		key += key2;
		if ("데이터 추가" == key)
		{
			system("cls");
			cout << "추가하실 데이터의 KEY 값을 입력해주세요\n";
			cin >> key;
			system("cls");
			cout << "추가하실 데이터을 입력해주세요\n";
			cin >> value;
			table.Add(key, value);

			cout << "\n엔터 : 뒤로가기\n";
			system("PAUSE");
		}
		else if ("데이터 삭제" == key)
		{
			system("cls");
			cout << "제거하실 데이터의 KEY 값을 입력해주세요\n";
			cin >> key;
			system("cls");
			table.Delete(key);

			cout << "\n엔터 : 뒤로가기\n";
			system("PAUSE");
		}

		else if ("데이터 검색" == key)
		{
			system("cls");
			cout << "검색하실 데이터의 KEY 값을 입력해주세요\n";
			cin >> key;
			system("cls");

			auto find = table.Find(key);

			if (find.value.size() > 0)
			{
				std::cout << "검색 결과: " << find.key << ", " << find.value << std::endl;
			}

			cout << "\n엔터 : 뒤로가기\n";
			system("PAUSE");
		}
		else if ("데이터 열람" == key)
		{
			system("cls");
			cout << "--------------------- 데이터 열람 ---------------------\n";
			table.Print();

			cout << "\n엔터 : 뒤로가기\n";
			system("PAUSE");
		}

	}
	system("cls");
	cout << "프로그램을 종료하겠습니다.\n";
	std::cin.get();
}
