/*
- 먼저 pair<std::string, std::string>을 저장하는 해시테이블을 구현한다. (강의노트 복습)
- 사용자에게 아이디/패스워드를 입력받고, 입력받은 아이디가 해시테이블에 없으면 데이터를 추가하고,
	중복된 아이디가 있으면 “아이디가 이미 사용 중입니다” 메시지를 출력하는 프로그램을 작성하자.
*/
#include "../Global.h"
#include "HashTable.h"

int main()
{
	HashTable Table;
	std::string ID = {};
	std::string PS = {};

	while (true)
	{
		system("cls");
		cout << "아이디 입력해 주세요 종료 :q" << endl;
		cin >> ID;
		system("cls");
		if ("q" == ID || "Q" == ID)
			break;
		cout << "비밀번호를 입력해 주세요" << endl;
		cin >> PS;
		if (Table.Find(ID).first != "")
			cout << "해당 아이디는 현재 사용중입니다." << endl;
		else
		{
			Table.Add(ID, PS);
			cout << "아이디 추가 완료" << endl;
		}

		Pause;
	}
}