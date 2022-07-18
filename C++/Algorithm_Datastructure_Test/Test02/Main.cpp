#include "../Global.h"

using std::pair;

int main()
{
	std::list<pair<char, pair<int, int>>> list;

	cout << "������ A�� �Է����ּ���" << endl;
	int AData[1] = {};
	cin >> AData[0];
	cin >> AData[1];
	list.push_back(std::make_pair('A', std::make_pair(AData[0], AData[1])));

	system("cls");
	cout << "������ B�� �Է����ּ���" << endl;
	int BData[1] = {};
	cin >> BData[0];
	cin >> BData[1];
	list.push_back(std::make_pair('B', std::make_pair(BData[0], BData[1])));
	system("cls");
	cout << "������ C�� �Է����ּ���" << endl;
	int CData[1] = {};
	cin >> CData[0];
	cin >> CData[1];
	list.push_back(std::make_pair('C', std::make_pair(CData[0], CData[1])));
	system("cls");
	cout << "������ D�� �Է����ּ���" << endl;
	int DData[1] = {};
	cin >> DData[0];
	cin >> DData[1];
	list.push_back(std::make_pair('D', std::make_pair(DData[0], DData[1])));
	system("cls");
	cout << "������ E�� �Է����ּ���" << endl;
	int EData[1] = {};
	cin >> EData[0];
	cin >> EData[1];
	list.push_back(std::make_pair('E', std::make_pair(EData[0], EData[1])));
	system("cls");
	cout << "������ �Է� �Ϸ�" << endl;
	
	for (auto iter : list)
		cout << "������ ��ġ : " << iter.first << ", ������ :" << iter.second.first << ", " << iter.second.second << endl;
	
	system("pause");
	system("cls");
	cout << "������ F�� �Է����ּ���" << endl;
	int FData[1] = {};
	cin >> FData[0];
	cin >> FData[1];
	list.push_back(std::make_pair('F', std::make_pair(FData[0], FData[1])));
	system("cls");
	cout << "������ F �߰� �Է� �Ϸ�" << endl << endl;

	for (auto iter : list)
		cout << "������ ��ġ : " << iter.first << ", ������ :" << iter.second.first << ", " << iter.second.second << endl;

	system("pause");
	system("cls");
	cout << "D ������ ���� ���� �Է����ּ���." << endl;
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

	cout << "������ D ���� �Ϸ�" << endl;

	for (auto iter : list)
		cout << "������ ��ġ : " << iter.first << ", ������ :" << iter.second.first << ", " << iter.second.second << endl;

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

	cout << "������ C ���� �Ϸ�" << endl;

	for (auto iter : list)
		cout << "������ ��ġ : " << iter.first << ", ������ :" << iter.second.first << ", " << iter.second.second << endl;


	cin.get();
	return 0;
}