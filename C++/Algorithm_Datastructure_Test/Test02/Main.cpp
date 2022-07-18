#include "../Global.h"

using std::pair;

int main()
{
	std::list<pair<char, pair<int, int>>> list;

	cout << "데이터 A를 입력해주세요" << endl;
	int AData[1] = {};
	cin >> AData[0];
	cin >> AData[1];
	list.push_back(std::make_pair('A', std::make_pair(AData[0], AData[1])));

	system("cls");
	cout << "데이터 B를 입력해주세요" << endl;
	int BData[1] = {};
	cin >> BData[0];
	cin >> BData[1];
	list.push_back(std::make_pair('B', std::make_pair(BData[0], BData[1])));
	system("cls");
	cout << "데이터 C를 입력해주세요" << endl;
	int CData[1] = {};
	cin >> CData[0];
	cin >> CData[1];
	list.push_back(std::make_pair('C', std::make_pair(CData[0], CData[1])));
	system("cls");
	cout << "데이터 D를 입력해주세요" << endl;
	int DData[1] = {};
	cin >> DData[0];
	cin >> DData[1];
	list.push_back(std::make_pair('D', std::make_pair(DData[0], DData[1])));
	system("cls");
	cout << "데이터 E를 입력해주세요" << endl;
	int EData[1] = {};
	cin >> EData[0];
	cin >> EData[1];
	list.push_back(std::make_pair('E', std::make_pair(EData[0], EData[1])));
	system("cls");
	cout << "데이터 입력 완료" << endl;
	
	for (auto iter : list)
		cout << "데이터 위치 : " << iter.first << ", 데이터 :" << iter.second.first << ", " << iter.second.second << endl;
	
	system("pause");
	system("cls");
	cout << "데이터 F를 입력해주세요" << endl;
	int FData[1] = {};
	cin >> FData[0];
	cin >> FData[1];
	list.push_back(std::make_pair('F', std::make_pair(FData[0], FData[1])));
	system("cls");
	cout << "데이터 F 추가 입력 완료" << endl << endl;

	for (auto iter : list)
		cout << "데이터 위치 : " << iter.first << ", 데이터 :" << iter.second.first << ", " << iter.second.second << endl;

	system("pause");
	system("cls");
	cout << "D 데이터 변경 값을 입력해주세요." << endl;
	int C[1] = {};
	cin >> C[0];
	cin >> C[1];

	auto iter = list.begin();
	auto iterEnd = list.end();
	for (; iter != iterEnd;++iter)
	{
		if (iter->first == 'D')
		{
			list.erase(iter);
			break;
		}
	}

	iter = list.begin();
	iterEnd = list.end();
	for (; iter != iterEnd; ++iter)
	{
		if (iter->first == 'E')
		{
			list.insert(iter, 1, std::make_pair('D', std::make_pair(C[0], C[1])));
			break;
		}
	}

	cout << "데이터 D 수정 완료" << endl;

	for (auto iter : list)
		cout << "데이터 위치 : " << iter.first << ", 데이터 :" << iter.second.first << ", " << iter.second.second << endl;

	system("pause");
	system("cls");

	iter = list.begin();
	iterEnd = list.end();
	for (; iter != iterEnd; ++iter)
	{
		if (iter->first == 'C')
		{
			list.erase(iter);
			break;
		}
	}

	cout << "데이터 C 삭제 완료" << endl;

	for (auto iter : list)
		cout << "데이터 위치 : " << iter.first << ", 데이터 :" << iter.second.first << ", " << iter.second.second << endl;


	cin.get();
	return 0;
}