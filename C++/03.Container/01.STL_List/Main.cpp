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


// list sort�� ���� �Լ� ��ü
class itemLessComparer
{
public:
	bool operator()(const item& left, const item& right)
	{return left.itemcode < right.itemcode;}
};

class itemGreaterComparer
{
public:
	bool operator()(const item& left, const item& right)
	{
		return left.itemcode > right.itemcode;
	}
};

int main()
{
	std::list<item> itemlist;

	item item1(1, 100);
	itemlist.push_back(item1);
	item item2(2, 200);
	itemlist.push_back(item2);
	item item3(3, 300);
	itemlist.push_front(item3);
	item item4(4, 400);
	itemlist.push_front(item4);
	Scan(itemlist);

	// ��/�� �߰� �� Ŭ����
	
	{
		itemlist.pop_back();
		Scan(itemlist);

		// �Լ� ��ü�� Ȱ���� sort
		itemLessComparer less;
		itemlist.sort(less);
		Scan(itemlist);

		// ����(���� �Լ�)�� Ȱ���� sort
		itemlist.sort([](const item& left, const item& right)->bool {return left.itemcode > right.itemcode;});
		Scan(itemlist);


		itemlist.clear();
		int count = itemlist.size();
		cout << "Clear ����" << endl;
		cout << "���� �ִ� ������ ����: " << count << endl;
		Pause;
	}
	
}

