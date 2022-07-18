#include "../Global.h"
#include <Windows.h>

void SetPosition(short x, short y)
{
	COORD position = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

int main()
{
	cout << "문자열을 입력해주세요" << endl;

	std::string str;
	cin >> str;
	std::queue<char> ch;
	for (int i = 0; i < str.length(); ++i)
		ch.push(str[i]);

	cout << str << endl;

	while (true)
	{

		Sleep(200);
		SetPosition(0, 1);
		for(auto iter : ch._Get_container())
			cout << iter;


	}
}