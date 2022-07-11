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
		cout << "�޴��� �Է����ּ���\n";
		cout << "#������ �߰� #������ ���� #������ �˻� #������ ���� #����\n";
		cin >> key;
		
		if ("����" == key)
			break;

		std::string key2 = {};
		cin >> key2;
		key += " ";
		key += key2;
		if ("������ �߰�" == key)
		{
			system("cls");
			cout << "�߰��Ͻ� �������� KEY ���� �Է����ּ���\n";
			cin >> key;
			system("cls");
			cout << "�߰��Ͻ� �������� �Է����ּ���\n";
			cin >> value;
			table.Add(key, value);

			cout << "\n���� : �ڷΰ���\n";
			system("PAUSE");
		}
		else if ("������ ����" == key)
		{
			system("cls");
			cout << "�����Ͻ� �������� KEY ���� �Է����ּ���\n";
			cin >> key;
			system("cls");
			table.Delete(key);

			cout << "\n���� : �ڷΰ���\n";
			system("PAUSE");
		}

		else if ("������ �˻�" == key)
		{
			system("cls");
			cout << "�˻��Ͻ� �������� KEY ���� �Է����ּ���\n";
			cin >> key;
			system("cls");

			auto find = table.Find(key);

			if (find.value.size() > 0)
			{
				std::cout << "�˻� ���: " << find.key << ", " << find.value << std::endl;
			}

			cout << "\n���� : �ڷΰ���\n";
			system("PAUSE");
		}
		else if ("������ ����" == key)
		{
			system("cls");
			cout << "--------------------- ������ ���� ---------------------\n";
			table.Print();

			cout << "\n���� : �ڷΰ���\n";
			system("PAUSE");
		}

	}
	system("cls");
	cout << "���α׷��� �����ϰڽ��ϴ�.\n";
	std::cin.get();
}
