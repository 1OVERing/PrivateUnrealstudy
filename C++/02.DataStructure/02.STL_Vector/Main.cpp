#include "../Global.h"

template< typename T>
void VectorSwap(T& front, T& back)
{
	T tmp = std::move(front);
	front = std::move(back);
	back = std::move(tmp);
}

void printArray(int* intarr, int _count = 0)
{
	int count = _count;
	if (0 == count)
	{
		count = sizeof(intarr) / sizeof(intarr[0]);
	}
	cout << endl;

	for (size_t i = 0; i < count; i++)
	{
		cout << intarr[i] << " ";
	}
	cout << endl;
}

int main()
{
	std::vector<int> data = {1,2,3,4,5,6,7,8,9,10};

	// 탐색 1
	// 일반 순회
	for (size_t i = 0; i < data.size(); i++)
	{
		cout << data[i] << " ";
	}
	cout << endl;

	// 탐색 2
	// iterator 순회
	// std::vector<int>::iterator iter = data.begin();
	auto iter = data.begin();
	for (;iter != data.end(); ++iter)
	{
		cout << (*iter) << " ";
	}
	cout << endl;

	iter = data.begin();
	iter = iter + 5;
	data.insert(iter,100);

	VectorSwap(data[0], data[1]);
	// 탐색 3
	// Ranged Loop 를 활용한
	// Range-based Loop 순회
	// 자료구조가 begin과 end 함수를 지원해야함
	for (auto& iter:data)
	{
		cout << iter << " ";
	}
	cout << endl;


	//int Arr[3] = {};
	//data.push_back(10);
	//data.push_back(20);
	//data.push_back(30);
	//data.push_back(40);
	//data.push_back(50);
	//data.push_back(60);
	//data.push_back(70);
	//auto A = data.begin();
	//data.insert(A,10);
	//data.reserve(data.size());
	//printArray(&data[0],data.size());
	//cout << "Size : " << data.size() << "   Capacity : " << data.capacity() << endl;
	cin.get();
}