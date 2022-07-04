#pragma once
#include "../Global.h"


// const int MAX_COUNT = 100;


template<typename T,size_t capacity>
class Stack
{
private:
	T data[capacity];
	size_t top; // 제일 위의 인덱스를 가르키는 변수
	



public:
	Stack() : top(0),data()
	{}
	~Stack() {}

public:
	void Clear()
	{top = 0;}
	size_t Count() const
	{return top;}
	bool IsEmpty() const
	{return top == 0;}
	bool IsFull()const
	{return top == capacity;}
	bool push(const T& value)
	{
		if (top >= capacity)
		{
			__debugbreak();
			return false;
		}

		this->data[top++] = value;
		cout << "stack 데이터 입력 : " << value << endl;
		return true;
	}
	T pop()
	{
		if (IsEmpty() == true)
		{
			__debugbreak();
			return 0;
		}

		cout << "stack 데이터 삭제 : " << data[--top] << endl;
		return data[top];
	}
};