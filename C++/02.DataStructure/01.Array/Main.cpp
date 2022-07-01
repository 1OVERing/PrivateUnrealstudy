#include "../Global.h"
template<typename T, size_t size>
class Array
{
public:
	size_t Size() const
	{
		return size;
	}

	// �迭�� �ε����� ������ �а�, ������ ���۷����� ��ȯ�ؾ� �Ѵ�.
	T& operator[](size_t index)
	{
		if (index >= size)
		{
			// ����� ��忡���� �����Ѵ�.
			__debugbreak();
		}

		return data[index];
	}

	const T& operator[](size_t index) const
	{
		if (index >= size)
		{
			// ����� ��忡���� �����Ѵ�.
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