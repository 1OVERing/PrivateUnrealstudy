#include "../Global.h"
#include <Windows.h>

void SetPosition(short x, short y)
{
	COORD position = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void QueueSwap(std::queue<char>& Q)
{
	char chf = Q.front();
	Q.pop();
	Q.push(chf);
}

int main()
{
	cout << "���ڿ��� �Է����ּ���" << endl;

	std::string str;
	cin >> str;
	std::queue<char> ch;
	for (int i = 0; i < str.length(); ++i)
		ch.push(str[i]);

	cout << str << endl;

	while (true)
	{
		Sleep(200);
		system("cls");
		cout << "���ڿ� ȸ��!!!!" << endl;
		SetPosition(0, 1);
		QueueSwap(ch);
		for(auto iter : ch._Get_container())
		 	cout << iter;
	

	}
}