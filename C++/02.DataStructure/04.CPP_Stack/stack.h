#pragma once

#include <iostream>

//const int MAX_COUNT = 100;

template<typename T, size_t capacity>
class Stack
{
public:
	Stack()
		: top(0)
	{
	}

	~Stack()
	{
	}

	void Clear()
	{
		top = 0;
	}

	// 스택에 저장된 데이터 요소의 수.
	size_t Count() const
	{
		return top;
	}

	// 스택이 비었는지 확인.
	bool IsEmpty() const
	{
		return top == 0;
	}

	// 스택이 가득찼는지 확인.
	bool IsFull() const
	{
		return top == capacity;
	}

	// 데이터 추가.
	bool Push(const T& value)
	{
		// 저장 가능한지 확인.
		if (top >= capacity)
		{
			__debugbreak();
			return false;
		}

		// 저장.
		data[top] = value;
		++top;

		return true;
	}

	// 데이터 추출.
	T Pop()
	{
		// 저장된 데이터가 있는지 확인.
		if (IsEmpty() == true)
		{
			__debugbreak();
			return 0;
		}

		// 추출.
		--top;
		return data[top];
	}

private:
	// 데이터 정의.
	T data[capacity];
	size_t top;
};