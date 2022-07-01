#include "../Global.h"


int main()
{
	std::vector<int> vec = {};
	int a = vec.capacity();
	vec.resize(5);
	a = vec.capacity();
	std::cin.get();
}