#include "../Global.h"
#include "Queue.h"
#include "TQueue.h"



int main()
{
	TQueue<int,10> q;
	for (int i = 0; i < 9; i++)
		q.Enqueue(i + 1);


	q.Display();

	for (int i = 0; i < 10; i++)
	{
		q.Dequeue();
		q.Enqueue(i + 1);
		q.Display();

		cin.get();
	}

	cout << "-----------------¿¬»ê ³¡------------------" << endl;
	cin.get();
}