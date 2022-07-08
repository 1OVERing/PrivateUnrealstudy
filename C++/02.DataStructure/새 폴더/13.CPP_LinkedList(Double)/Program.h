#pragma once

#include "LinkedList.h"
#include <string>

class Program
{
private:
	LinkedList<std::string>* list;
public:
	void InsertLoop();
	void DeleteLoop();
public:
	Program();
	~Program();
};

