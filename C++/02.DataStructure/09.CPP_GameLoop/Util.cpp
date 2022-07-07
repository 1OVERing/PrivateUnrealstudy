#include "Util.h"
#include "../Global.h"
#include <Windows.h>

namespace Util
{
	void Util::ClearScreen()
	{
		system("cls");

	}

	void Util::Delay(unsigned long milliseconds)
	{
		Sleep(milliseconds);
	}

	void Util::SetPosition(short x, short y)
	{
		COORD pos = {x,y};

		// ���α׷� �ڵ� �� �޾ƿͼ� ��ġ���� �Բ� Ŀ���� �Ű��ִ� �Լ��� �־��ش�.
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
	}
}