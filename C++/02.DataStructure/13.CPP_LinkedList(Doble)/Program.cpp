#include "Program.h"
#include <iostream>
using namespace std;
// 오류 발생했을 때 실행될 함수.
void OnListError()
{
	cout << "오류가 발생했습니다." << endl;
}

Program::Program()
{
	// 리스트 생성.
	// 함수 포인터 전달.
	list = new LinkedList<string>(OnListError);

	//// 람다 예시.
	//list = new LinkedList<string>([]()
	//	{
	//		cout << "리스트에서 오류가 발생했습니다." << endl;
	//	});
}

Program::~Program()
{
	delete list;
}

// 입력을 받고, 리스트에 데이터 추가하는 로직.
void Program::InsertLoop()
{
	// 입력을 받기 위한 변수.
	string name;

	// 로직 처리 루프.
	while (true)
	{
		cout << "추가할 연락처의 이름을 입력하세요(종료는 q)." << endl;

		// 입력 받은 데이터(문자열)를 name 변수에 저장.
		cin >> name;

		// 입력받은 글자가 q 또는 Q일 때 루프 종료.
		if (name == "Q" || name == "q")
		{
			break;
		}

		// 맨 마지막에 데이터 추가.
		list->PushLast(name);

		// 출력.
		list->Print();
	}
}

// 입력을 받고, 리스트에서 데이터를 삭제하는 로직.
void Program::DeleteLoop()
{
	// 입력을 받기 위한 변수.
	string name;

	// 로직 처리 루프.
	while (true)
	{
		cout << "삭제할 연락처의 이름을 입력하세요(종료는 q)." << endl;

		// 입력 받은 데이터(문자열)를 name 변수에 저장.
		cin >> name;

		// 입력받은 글자가 q 또는 Q일 때 루프 종료.
		if (name == "Q" || name == "q")
		{
			break;
		}

		// 데이터 삭제.
		list->Delete(name);

		// 출력.
		list->Print();
	}
}