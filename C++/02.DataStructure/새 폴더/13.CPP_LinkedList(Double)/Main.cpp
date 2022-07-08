#include <iostream>
#include "Program.h"

using std::cout;
using std::cin;
using std::endl;


int main()
{
	Program* Program = new Program();

	Program->InsertLoop();
	Program->DeleteLoop();

	cin.get();
}