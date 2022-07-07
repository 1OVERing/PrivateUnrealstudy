#include "Program.h"
#include <iostream>



int main()
{
	std::locale::global(std::locale("kor"));
	ContactList* list = new ContactList();

	Program* program = new Program();

	program->InsertLoop(&list);
	program->DeleteLoop(&list);

	delete program;
	delete list;

	std::cin.get();
}