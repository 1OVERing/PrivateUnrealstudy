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

		// 프로그램 핸들 을 받아와서 위치값과 함께 커서를 옮겨주는 함수에 넣어준다.
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
	}
}