#pragma once
#include "../Global.h"

template<typename T, size_t capacity = 10>
class TQueue
{
private:
	int front;
	int rear;
	size_t size;
	T data[capacity + 1];



public:
	bool IsEmpty() const
	{
		return front == rear;
	}
	bool IsFull() const
	{
		return ((rear + 1) % capacity) == front;
	}
	void Enqueue(const T& value)
	{
		if (IsFull())
		{
			cout << " Error : 큐가 가득 찼습니다." << endl;
			return;
		}
		rear = (rear + 1) % capacity;
		data[rear] = value;
	}
	T Dequeue()
	{
		if (IsEmpty())
		{
			cout << " Error : 큐가 비어있습니다." << endl;
			return -1;
		}

		front = (front + 1) % capacity;
		return data[front];
	}
	T Peek()
	{
		if (IsEmpty())
		{
			cout << " Error : 큐가 비어있습니다." << endl;
			return -1;
		}
		return data[(front + 1) % capacity];
	}
	void Display()
	{
		cout << "큐 내용 출력 : ";

		// 인덱스 최대 값 계산
		int Max = (front < rear) ? rear : rear + capacity;
		for (int i = front + 1; i <= Max; ++i)
		{
			cout << " " << data[i % capacity];
		}
		cout << endl;
	}
public:
	TQueue() : front(0), rear(0), size(capacity + 1)
	{
		memset(data, 0, sizeof(T) * size);
	}
	~TQueue() {}
};