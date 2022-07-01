#include <iostream>
#include <vector>


int main()
{
	int iarr[10] = {1,2,3,4,5,6,7,8,9,10};

	//std::cout << iarr[0] << std::endl;
	//std::cout << iarr[1] << std::endl;
	//std::cout << iarr[2] << std::endl;
	//std::cout << iarr[3] << std::endl;
	//std::cout << iarr[4] << std::endl;

	//// unroll = for에서 위처럼 풀어서 작동된다. 순수 속도 자체는 위의 처리가 더 빠르다. 다만 의미가 있는 속도는 아니다.
	//for (int i = 0; i < 5; i++)
	//{
	//	std::cout << iarr[i] << std::endl;
	//}

	// Ranged Loop = 해당 배열을 전체를 한번씩 돈다.
	// 다만 순서는 보장하지 않는다.
	std::vector<int> vec = {};
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);
	vec.push_back(6);
	auto test = 10;
	auto test2 = 1.1;
	for (const auto& i : vec)
	{
		std::cout << i << std::endl;
	}


	int* idarray = new int[10];
	for (int i = 0; i < 10; i++)
	{
		idarray[i] = (i + 1) * 10;
	}
	
	delete[] idarray;
	std::cin.get();
}