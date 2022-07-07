#pragma once


namespace Util
{
	void ClearScreen();
	// 1/1000초 단위로 실행 대기 기능
	void Delay(unsigned long milliseconds);
	// 콘솔 화면의 좌표를 이동할 때 사용
	void SetPosition(short x, short y);
	
}