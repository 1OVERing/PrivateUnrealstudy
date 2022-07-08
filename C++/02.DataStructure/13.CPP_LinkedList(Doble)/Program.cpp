#include "Program.h"
#include <iostream>
using namespace std;
// ���� �߻����� �� ����� �Լ�.
void OnListError()
{
	cout << "������ �߻��߽��ϴ�." << endl;
}

Program::Program()
{
	// ����Ʈ ����.
	// �Լ� ������ ����.
	list = new LinkedList<string>(OnListError);

	//// ���� ����.
	//list = new LinkedList<string>([]()
	//	{
	//		cout << "����Ʈ���� ������ �߻��߽��ϴ�." << endl;
	//	});
}

Program::~Program()
{
	delete list;
}

// �Է��� �ް�, ����Ʈ�� ������ �߰��ϴ� ����.
void Program::InsertLoop()
{
	// �Է��� �ޱ� ���� ����.
	string name;

	// ���� ó�� ����.
	while (true)
	{
		cout << "�߰��� ����ó�� �̸��� �Է��ϼ���(����� q)." << endl;

		// �Է� ���� ������(���ڿ�)�� name ������ ����.
		cin >> name;

		// �Է¹��� ���ڰ� q �Ǵ� Q�� �� ���� ����.
		if (name == "Q" || name == "q")
		{
			break;
		}

		// �� �������� ������ �߰�.
		list->PushLast(name);

		// ���.
		list->Print();
	}
}

// �Է��� �ް�, ����Ʈ���� �����͸� �����ϴ� ����.
void Program::DeleteLoop()
{
	// �Է��� �ޱ� ���� ����.
	string name;

	// ���� ó�� ����.
	while (true)
	{
		cout << "������ ����ó�� �̸��� �Է��ϼ���(����� q)." << endl;

		// �Է� ���� ������(���ڿ�)�� name ������ ����.
		cin >> name;

		// �Է¹��� ���ڰ� q �Ǵ� Q�� �� ���� ����.
		if (name == "Q" || name == "q")
		{
			break;
		}

		// ������ ����.
		list->Delete(name);

		// ���.
		list->Print();
	}
}