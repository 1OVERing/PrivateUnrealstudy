#include "../global.h"



int main()
{
	std::list<int> list;
	list.push_back(1);
	list.push_back(1);
	
	// ù��° ��ġ ���� �׽�Ʈ
	cout << "�����׽�Ʈ 1��° ��ġ�� 100 ����" << endl << endl;
	list.insert(list.begin(), 100);
	Scan(list);

	cout << "�����׽�Ʈ 2 2��° ��ġ�� 200 2�� ����" << endl << endl;
	std::list<int>::iterator iter = list.begin();
	iter++;
	list.insert(iter,2, 200);
	Scan(list);

	std::list<int>list2;
	list2.push_back(1000);
	list2.push_back(2000);
	list2.push_back(3000);
	list2.push_back(4000);

	cout << "�����׽�Ʈ 3 2��° ��ġ�� list2�� ��� ������ ����" << endl << endl;
	iter = list.begin();
	iter++;
	list.insert(iter,list2.begin(),list2.end());
	Scan(list);

	cout << "�����׽�Ʈ 1 remove�� �̿��� ������ ����\n\n";
	iter = list.begin();
	list.remove(*iter);
	Scan(list);
}