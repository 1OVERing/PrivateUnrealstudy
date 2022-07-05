#pragma once
#include "../Global.h"

const int MAX_QUEUE_SIZE = 10;


class Queue
{
protected:
	int front;
	int rear;
	int data[MAX_QUEUE_SIZE];



public:
	bool IsEmpty() const
	{return front == rear;}
	bool IsFull() const
	{return ((rear + 1) % MAX_QUEUE_SIZE) == front;}
	void Enqueue(int value)
	{
		if (IsFull())
		{
			cout << " Error : 큐가 가득 찼습니다." << endl;
			return;
		}
		rear = (rear + 1) % MAX_QUEUE_SIZE;
		data[rear] = value;
	}
	int Dequeue()
	{
		if (IsEmpty())
		{
			cout << " Error : 큐가 비어있습니다." << endl;
			return -1;
		}

		front = (front + 1) % MAX_QUEUE_SIZE;
		return data[front];
	}
	int Peek()
	{
		if (IsEmpty())
		{
			cout << " Error : 큐가 비어있습니다." << endl;
			return -1;
		}
		return data[(front + 1) % MAX_QUEUE_SIZE];
	}
	void Display()
	{
		cout << "큐 내용 출력 : ";

		// 인덱스 최대 값 계산
		int Max = (front < rear) ? rear : rear + MAX_QUEUE_SIZE;
		for (int i = front + 1; i <= Max; ++i)
		{
			cout << " " << data[i % MAX_QUEUE_SIZE];
		}
		cout << endl;
	}
public:
	Queue() : front(0), rear(0)
	{
		memset(data, 0, sizeof(int) * MAX_QUEUE_SIZE);
	}
	virtual ~Queue() {}
};