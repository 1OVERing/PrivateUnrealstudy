//#include <iostream>
//
//int main()
//{
//	int iNumber = 10;
//	int* pInt = nullptr;
//
//	pInt = &iNumber;
//
//	*pInt = 30;
//
//	std::cin.get();
//}
#include <iostream>
// #define "\"�� �Ʒ��ٵ� #define�� �����̶�� ǥ���̴�.
#define Log(a) \
std::cout << a << "File :"<< __FILE__ << "Line :"<< __LINE__ << std::endl

// Ÿ�� ������
typedef unsigned int int64;

#if _DEBUG
#else
#define Log(a)
#endif

//void Log(int a)
//{
//	std::cout << a << std::endl;
//}

void pIncrement(int* value)
{
	(*value)++;
}
void rIncrement(int& value)
{
	value++;
}

int main()
{
	int a[5] = {10000000,2,3,4,5};

	int b = 1;
	b = b << 5;

	std::cin.get();
	
	return 0;
}