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

	//// unroll = for���� ��ó�� Ǯ� �۵��ȴ�. ���� �ӵ� ��ü�� ���� ó���� �� ������. �ٸ� �ǹ̰� �ִ� �ӵ��� �ƴϴ�.
	//for (int i = 0; i < 5; i++)
	//{
	//	std::cout << iarr[i] << std::endl;
	//}

	// Ranged Loop = �ش� �迭�� ��ü�� �ѹ��� ����.
	// �ٸ� ������ �������� �ʴ´�.
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