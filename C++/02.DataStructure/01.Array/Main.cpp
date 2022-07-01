#include "../Global.h"
template<typename T, size_t size>
class Array
{
public:
	size_t Size() const
	{
		return size;
	}

	// 배열을 인덱스로 접근해 읽고, 쓰려면 레퍼런스로 반환해야 한다.
	T& operator[](size_t index)
	{
		if (index >= size)
		{
			// 디버그 모드에서만 동작한다.
			__debugbreak();
		}

		return data[index];
	}

	const T& operator[](size_t index) const
	{
		if (index >= size)
		{
			// 디버그 모드에서만 동작한다.
			__debugbreak();
		}

		return data[index];
	}

	T* Data()
	{
		return data;
	}

	const T* Data() const
	{
		return data;
	}

private:
	T data[size];
};

int main()
{
	Array<int, 5> data;
	
	memset(data.Data(), 0, data.Size() * sizeof(int));

	std::cin.get();
}