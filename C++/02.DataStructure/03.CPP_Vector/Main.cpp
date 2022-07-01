#include "../Global.h"
template< typename T>
void VectorSwap(T& front, T& back)
{
	T tmp = std::move(front);
	front = std::move(back);
	back = std::move(tmp);
}

template<typename T>
class Vector
{
private: // member variable
	size_t size;
	size_t capacity;
	T* data;


public: // member func
	void PushBack(const T& value)
	{
		if (size == capacity)
		{
			ReAllocate(capacity + (capacity / 2));
		}

		data[size] = value;
		size++;
	}
	
	size_t Size() const
	{
		return size;
	}
	size_t Capacity() const
	{
		return capacity;
	}
private:
	void ReAllocate(size_t newCapacity)
	{
		// 새로운 메모리 공간 할당
		// 할당된 메모리 공간에 데이터 복사
		// 기존 메모리 공간 삭제
		T* newBlock = new T[newCapacity];
		// memset(&newBlock, 0, newCapacity);

		if (newCapacity < size)
		{
			size = newCapacity;
		}
		for (size_t i = 0; i < size; i++)
		{
			newBlock[i] = data[i];
		}
		delete[] data;
		data = newBlock;
		capacity = newCapacity;
	}



public: // operator overloading
	T& operator[](size_t index)
	{
		if (index >= size)
		{
			__debugbreak();
		}
		return data[index];
	}
public: // constructor destructor
	Vector() :size(0), capacity(0), data(nullptr)
	{
		ReAllocate(2);
	}
	~Vector()
	{
		if (nullptr != data)
		{
			delete[] data;
		}
	}
};

int main()
{
	Vector<int> vec;
	vec.PushBack(1);
	vec.PushBack(2);
	vec.PushBack(3);
	vec.PushBack(3);
	vec.PushBack(3);

	VectorSwap(vec[0], vec[3]);

	for (size_t i = 0; i < vec.Size(); i++)
	{
		cout << vec[i] << " ";
	}
	cout << endl;
	
	const int& element = vec[3];
	cout << " 3th element : " << element << endl;
	vec[3] = 80;
	cout << " 3th element : " << element << endl;

	cin.get();
}