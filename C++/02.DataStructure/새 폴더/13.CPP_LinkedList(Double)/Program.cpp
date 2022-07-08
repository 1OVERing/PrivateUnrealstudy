#include "Program.h"

using std::cout;
using std::cin;
using std::endl;

void OnListError()
{
	std::cout << "LinkedList���� ������ �߻��߽��ϴ�.\n";
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
	cout << "-----------�������߰�-----------\n";
	std::string name;

	while (true)
	{
		cout << "�߰��� ����ó�� �̸��� �Է��ϼ��� : ����(q)\n";
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
	cout << "-----------�����ͻ���-----------\n";
	std::string name;

	while (true)
	{
		cout << "������ ����ó�� �̸��� �Է��ϼ��� : ����(q)\n";
		cin >> name;

		if ("q" == name || "Q" == name)
			break;

		list->Delete(name);
	}
	list->Print();
}