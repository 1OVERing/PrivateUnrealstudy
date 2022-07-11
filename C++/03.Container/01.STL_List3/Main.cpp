#include "../global.h"

class item
{
public:
	int itemcode;
	int price;

	item(int a = 0, int b = 0) : itemcode(a), price(b)
	{

	}
	
};

std::ostream& operator<< (std::ostream& os, const item& item)
{
	return os << "������ �ڵ� : " << item.itemcode << ", ���� : " << item.price;
}


int main()
{
	std::list<int> list1;
	list1.emplace_back(0);
	list1.emplace_back(1);
	list1.emplace_back(2);
	list1.emplace_back(2);
	list1.emplace_back(4);
	list1.emplace_back(5);

	for (auto& value : list1)
		cout << "list 1: " << value << endl;

	cout << "�����׽�Ʈ 1 remove�� �̿��� Ư�� ������ ���� ����\n\n";
	list1.remove(2);
	Scan(list1);

	cout << "�����׽�Ʈ 2 remove�� �̿��� ������ �������� Ȱ���� ����\n\n";
	std::list<item*> itemlist;
	item* item1 = new item(0001, 100);
	item* item2 = new item(0002, 100);
	item* item3 = new item(0003, 100);
	item* item4 = new item(0004, 100);
	item* item5 = new item(0005, 100);
	list1.emplace_back(item1);
	list1.emplace_back(item2);
	list1.emplace_back(item3);
	list1.emplace_back(item4);
	list1.emplace_back(item5);
	itemlist.remove(item3);
	std::make_pair(0,10);
	for (const auto iter : itemlist)
		cout << *iter << endl;

	for (const auto iter : itemlist)
		delete iter;
}