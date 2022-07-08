#include <iostream>

class A
{
public:
	int(*Addfunc)(int);
	int count;

public:
	A(int (*addfunc)(int)) : count(0)
	{
		Addfunc = addfunc;
	}
	~A() {}
};


int Add(int a)
{
	std::cout << " Test Add \n";
	return ++a;
}


int main()
{
	A a = A(Add);
	a.count = a.Addfunc(a.count);

	for(;a.count < 10;)
		a.count = a.Addfunc(a.count);

	std::cin.get();
}