#pragma once

#include "LinkedList.h"
#include <string>
using namespace std;
class Program
{
public:
	// ������.
	Program();
	
	// �Ҹ���.
	~Program();

	// ������ �Լ�.
	void InsertLoop();
	void DeleteLoop();
	
private:
	// ���ڿ� ���� ������ ��ũ�帮��Ʈ.
	LinkedList<string>* list;
};

