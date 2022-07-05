#include "Deque.h"
#include <deque>
// #include <synchapi.h>
#include <Windows.h>


int main()
{
	CRITICAL_SECTION SC;
	InitializeCriticalSection(&SC);
	EnterCriticalSection(&SC);
	Deque d;
	for (size_t i = 0; i < 10; i++)
	{
		if (i % 2 == 0)
			d.AddFront((int)i);
		else
			d.AddRear((int)i);
	}
	d.Display();

	LeaveCriticalSection(&SC);
	DeleteCriticalSection(&SC);
}