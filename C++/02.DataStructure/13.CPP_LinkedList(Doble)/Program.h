#pragma once

#include "LinkedList.h"
#include <string>
using namespace std;
class Program
{
public:
	// 생성자.
	Program();
	
	// 소멸자.
	~Program();

	// 실행할 함수.
	void InsertLoop();
	void DeleteLoop();
	
private:
	// 문자열 값을 저장할 링크드리스트.
	LinkedList<string>* list;
};

