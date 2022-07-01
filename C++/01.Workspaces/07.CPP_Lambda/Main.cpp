#include <iostream>




int main()
{
	char chA = 'A';
	char chB = 'B';
	auto function = [&,chB] (int num) {std::cout << "Hello world" << num << chA << chB << std::endl; };
	function(1);
}