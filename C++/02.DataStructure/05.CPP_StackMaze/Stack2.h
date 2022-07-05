#pragma once
#include <vector>

template<typename T,typename container = std::vector<T>, size_t Size = 30>
class Stack2
{

private:
	int top;
	container c{};
public:
	Stack2()
		: top(0)
	{
	}
	~Stack2() {}

public:
	_NODISCARD const container& _Get_container() const noexcept 
	{return c;}
	void Clear()
	{
		top = 0;
	}

	bool IsEmpty() const
	{
		return top == 0;
	}

	bool IsFull() const
	{
		return top >= Size;
	}

	bool Push(const T& value)
	{
		if (IsFull() == true)
		{
			__debugbreak();
			return false;
		}
		c.push_back(value);
		top++;

		return true;
	}

	T Pop()
	{
		if (IsEmpty() == true)
		{
			__debugbreak();
		}

		top--;
		return c[top];
	}

	T Top() const
	{
		if (IsEmpty() == true)
		{
			__debugbreak();
		}

		return c[top - 1];
	}

	size_t Capacity() const
	{
		return Size;
	}

};
