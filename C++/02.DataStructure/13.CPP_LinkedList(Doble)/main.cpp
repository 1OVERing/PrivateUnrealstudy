#include <iostream>
#include "Program.h"
using namespace std;
int main()
{
	//locale::global(locale("korea"));

	Program* program = new Program();

	program->InsertLoop();
	program->DeleteLoop();

	delete program;

	cin.get();
}