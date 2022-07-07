#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	//const char* TestChar = "char_t test";
	//std::string str = TestChar + std::string("문자열") + " 입니다.";
	//cout << str << endl;

	//// wide character
	//const wchar_t* wideTestChar = L"wchar_t test";
	//std::wstring Wstr = L"std::wstring test";
	//std::wcout << Wstr << endl;
	//cin.get();
	//system("cls");
	//cout << "문장을 입력해주세요 \n";
	//cin >> str;
	//cout << "입력하신 문장은 \"" << str << "\"입니다.\n";

	//cout << "문장을 한번 더 입력해주세요.\n";
	//std::wcin >> Wstr;
	//std::wcout << "입력하신 문장은 \"" << Wstr << "\"입니다.\n";

	//auto pos = str.find(" ");
	//cout << "검색된 위치는 " << pos << "입니다.\n";
	//system("cls");
	//cin.get();

	// 문자열 자르기
	std::string str1 = "0123 45 ";
	std::string str2 = "678 910 ";
	std::string str3 = "11 121314";

	// str2 의 " "공백의 위치값을 찾아 보관
	auto pos = str2.find(" ");
	// 찾은 " "공백 이후로 문자열을 잘라서 str1에 넣는다.
	str1 = str2.substr(pos + 1);
	
	// str1 과 str 2 를 출력
	cout << str1 << "" << str2 << endl;
}