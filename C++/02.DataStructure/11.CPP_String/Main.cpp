#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	//const char* TestChar = "char_t test";
	//std::string str = TestChar + std::string("���ڿ�") + " �Դϴ�.";
	//cout << str << endl;

	//// wide character
	//const wchar_t* wideTestChar = L"wchar_t test";
	//std::wstring Wstr = L"std::wstring test";
	//std::wcout << Wstr << endl;
	//cin.get();
	//system("cls");
	//cout << "������ �Է����ּ��� \n";
	//cin >> str;
	//cout << "�Է��Ͻ� ������ \"" << str << "\"�Դϴ�.\n";

	//cout << "������ �ѹ� �� �Է����ּ���.\n";
	//std::wcin >> Wstr;
	//std::wcout << "�Է��Ͻ� ������ \"" << Wstr << "\"�Դϴ�.\n";

	//auto pos = str.find(" ");
	//cout << "�˻��� ��ġ�� " << pos << "�Դϴ�.\n";
	//system("cls");
	//cin.get();

	// ���ڿ� �ڸ���
	std::string str1 = "0123 45 ";
	std::string str2 = "678 910 ";
	std::string str3 = "11 121314";

	// str2 �� " "������ ��ġ���� ã�� ����
	auto pos = str2.find(" ");
	// ã�� " "���� ���ķ� ���ڿ��� �߶� str1�� �ִ´�.
	str1 = str2.substr(pos + 1);
	
	// str1 �� str 2 �� ���
	cout << str1 << "" << str2 << endl;
}