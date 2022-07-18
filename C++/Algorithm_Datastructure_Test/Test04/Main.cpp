#include <iostream>
#include <string>
#include <map>

using namespace std;

struct Item
{
	string name;				// �̸�
	unsigned short kind;		// ����
	int price;					// ���� ����
	int skillCode;				// ��ų �ڵ�
};

int main()
{
	{
		map<string, Item, greater<string>> items;

		Item item1 = { "��Į", 1, 200, 0 };
		Item item2 = { "�������� ����", 2, 1000, 4 };
		Item item3 = { "�ظ�", 1, 500, 0 };

		// Items�� ������ �߰�
		items.insert({ item2.name, item2 });
		items.insert({ item1.name, item1 });

		// Items�� ��� �����ʴٸ�
		if (items.empty() == false)
		{
			cout << "����� ������ ����: " << items.size() << endl;
		}

		for (auto iter = items.begin(); iter != items.end(); ++iter)
		{
			cout << "�̸�: " << iter->first << ", ����: " << iter->second.price << endl;
		}

		auto search = items.find("��Į");
		if (search == items.end())
		{
			cout << "������'��Į'�� �����ϴ�." << endl;
		}

		cout << endl;

		cout << "�ø��������� ���ĵǾ��ִ� map(Key �ڷ������� string ���)" << endl;

		// initialize list�� ����� �ڷ� �߰�.
		map<string, Item, less<string>> items2 =
		{
			{ item2.name, item2 },
			{ item1.name, item1 }
		};

		// operator[]�� ����Ͽ� ����
		items2[item3.name] = item3;

		for (auto iter2 = items2.begin(); iter2 != items2.end(); ++iter2)
		{
			cout << "�̸�: " << iter2->first << ", ����: " << iter2->second.price << endl;
		}

		cout << endl;

		cout << "�ظ��� ������ ��? ";
		search = items2.find("�ظ�");
		if (search != items2.end())
		{
			cout << search->second.price << endl;
		}
		else
		{
			cout << "�ظӴ� �����ϴ�" << endl;
		}

		cout << endl;

		// ������ "��Į"�� �����Ѵ�.
		search = items2.find("��Į");
		if (search != items2.end())
		{
			items2.erase(search);
		}

		cout << "Items2�� �ִ� ������ ����: " << items2.size() << endl;

		cin.get();
		cout << endl << endl << endl;
		cout << "�ƹ� Ű�� ������ items3�� �����Ͽ� ������ ������ �������� �����͸� �޾ƿɴϴ�." << endl << endl;
		system("pause");
	}

	system("cls");
	cout << "�������� ������ Key������ �޾ƿ� ��������(���� �� ����) ����" << endl << endl;
	multimap<int , Item, greater<int>> items3;

	Item item1 = { "��Į", 1, 200, 0 };
	Item item2 = { "�������� ����", 2, 1000, 4 };
	Item item3 = { "�ظ�", 1, 500, 0 };
	Item item4 = { "�Ȱ��� ���� �׽�Ʈ", 1, 500, 0 };

	// Items�� ������ �߰�
	items3.insert({ item2.price, item2 });
	items3.insert({ item1.price, item1 });
	items3.insert({ item3.price, item3 });
	items3.insert({ item4.price, item4 });

	// Items�� ��� �����ʴٸ�
	if (items3.empty() == false)
	{
		cout << "����� ������ ����: " << items3.size() << endl;
	}

	for (auto iter = items3.begin(); iter != items3.end(); ++iter)
	{
		cout << "�̸�: " << iter->second.name << ", ����: " << iter->second.price << endl;
	}

	auto search = items3.find(200);
	if (search == items3.end())
	{
		cout << "200�� ¥�� �������� �����ϴ�." << endl;
	}

	cout << endl;

}