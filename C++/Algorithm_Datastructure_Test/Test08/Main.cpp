/*
- ���� pair<std::string, std::string>�� �����ϴ� �ؽ����̺��� �����Ѵ�. (���ǳ�Ʈ ����)
- ����ڿ��� ���̵�/�н����带 �Է¹ް�, �Է¹��� ���̵� �ؽ����̺� ������ �����͸� �߰��ϰ�,
	�ߺ��� ���̵� ������ �����̵� �̹� ��� ���Դϴ١� �޽����� ����ϴ� ���α׷��� �ۼ�����.
*/
#include "../Global.h"
#include "HashTable.h"

int main()
{
	HashTable Table;
	std::string ID = {};
	std::string PS = {};

	while (true)
	{
		system("cls");
		cout << "���̵� �Է��� �ּ��� ���� :q" << endl;
		cin >> ID;
		system("cls");
		if ("q" == ID || "Q" == ID)
			break;
		cout << "��й�ȣ�� �Է��� �ּ���" << endl;
		cin >> PS;
		if (Table.Find(ID).first != "")
			cout << "�ش� ���̵�� ���� ������Դϴ�." << endl;
		else
		{
			Table.Add(ID, PS);
			cout << "���̵� �߰� �Ϸ�" << endl;
		}

		Pause;
	}
}