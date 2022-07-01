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
// #define "\"는 아래줄도 #define의 영역이라는 표시이다.
#define Log(a) \
std::cout << a << "File :"<< __FILE__ << "Line :"<< __LINE__ << std::endl

// 타입 재정의
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