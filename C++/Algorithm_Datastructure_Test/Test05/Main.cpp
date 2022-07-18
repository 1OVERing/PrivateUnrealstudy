#include "../Global.h"



int main()
{
	std::deque<int> de;
	std::deque<int> temp;

	cout << "deque에 데이터 1 2 3 4 5 6 을 입력했다 가정하고 데이터 입력" << endl;
	de.push_back(1);
	de.push_back(2);
	de.push_back(3);
	de.push_back(4);
	de.push_back(5);
	de.push_back(6);
	
	cout << "데이터 추가 완료" << endl;
	for (auto iter : de)
		cout << iter << " ";
	cout << endl << endl << endl;
	

	while (true)
	{
		system("cls");
		cout << "현재 데이터 : ";
		for (auto iter : de)
			cout << iter << ", ";

		cout << endl;
		cout << "Undo / Redo 을 입력하여 데이터를 빼거나 다시 추가해주세요 / 종료 :q" << endl;
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

	cout << " 프로그램을 종료합니다. " << endl;
	cin.get();
}