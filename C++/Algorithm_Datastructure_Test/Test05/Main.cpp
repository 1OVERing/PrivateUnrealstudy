#include "../Global.h"



int main()
{
	std::deque<int> de;
	std::deque<int> temp;

	cout << "deque�� ������ 1 2 3 4 5 6 �� �Է��ߴ� �����ϰ� ������ �Է�" << endl;
	de.push_back(1);
	de.push_back(2);
	de.push_back(3);
	de.push_back(4);
	de.push_back(5);
	de.push_back(6);
	
	cout << "������ �߰� �Ϸ�" << endl;
	for (auto iter : de)
		cout << iter << " ";
	cout << endl << endl << endl;
	

	while (true)
	{
		system("cls");
		cout << "���� ������ : ";
		for (auto iter : de)
			cout << iter << ", ";

		cout << endl;
		cout << "Undo / Redo �� �Է��Ͽ� �����͸� ���ų� �ٽ� �߰����ּ��� / ���� :q" << endl;
		std::string str;
		cin >> str;

		if ("q" == str || "Q" == str)
		{
			break;
		}
		
		if ("Undo" == str || "undo" == str)
		{
			temp.push_back(de.front());
			de.pop_front();
		}
		else if ("Redo" == str || "redo" == str)
		{
			de.push_front(temp.back());
			temp.pop_back();
		}

		cin.get();
	}

	cout << " ���α׷��� �����մϴ�. " << endl;
	cin.get();
}