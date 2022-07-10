/*--------------------------function Point--------------------------*/
//#include <iostream>
//class A
//{
//public:
//	int(*Addfunc)(int);
//	int count;
//
//public:
//	A(int (*addfunc)(int)) : count(0)
//	{
//		Addfunc = addfunc;
//	}
//	~A() {}
//};
//
//
//int Add(int a)
//{
//	std::cout << " Test Add \n";
//	return ++a;
//}
//
//
//int main()
//{
//	std::forward_list<int> B;
//	A a = A(Add);
//	a.count = a.Addfunc(a.count);
//
//	for(;a.count < 10;)
//		a.count = a.Addfunc(a.count);
//
//	std::cin.get();
//}
/*--------------------------forward_list--------------------------*/
#include <iostream>
int main()
{
	std::hash<char> b;

	size_t hash = 0;
	hash = b._Do_hash('a');

	float a = (int)hash;
	a = std::abs(a);

	std::cin.get();
}