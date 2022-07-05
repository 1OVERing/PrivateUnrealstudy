#pragma once	// 헤더 중복 include 방지
#include "../06.CPP_Queue/Queue.h"



class Deque : public Queue
{
public:
	void AddRear(int value)
	{Enqueue(value);}
	void DeleteFront()
	{Dequeue();}

	int GetFront()
	{
		return Peek();
	}
	void AddFront(int value)
	{
		if (IsFull())
			return;
		data[front] = value;
		front = ((front - 1) + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	}
	int DeleteRear()
	{
		if (IsFull())
			return - 1;

		int value = data[rear];

		rear = (rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;

		return value;
	}
	int GetRear()
	{
		if (IsFull())
			return - 1;
		
		return data[rear];
	}
	void Display()
	{
		cout << "덱의 내용 출력 : ";
		// 인덱스 최대 값 계산
		int Max = (front < rear) ? rear : rear + MAX_QUEUE_SIZE;
		for (int i = front + 1; i <= Max; ++i)
		{
			cout << " " << data[i % MAX_QUEUE_SIZE];
		}
		cout << endl;
	}

public:
	Deque() : Queue()
	{}
	~Deque()
	{}
};