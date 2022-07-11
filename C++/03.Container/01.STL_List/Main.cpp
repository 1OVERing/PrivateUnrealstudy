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
	return os << "아이템 코드 : " << item.itemcode << ", 가격 : " << item.price;
}


// list sort를 위한 함수 객체
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

	// 앞/뒤 추가 및 클리어
	
	{
		itemlist.pop_back();
		Scan(itemlist);

		// 함수 객체를 활용한 sort
		itemLessComparer less;
		itemlist.sort(less);
		Scan(itemlist);

		// 람다(무명 함수)를 활용한 sort
		itemlist.sort([](const item& left, const item& right)->bool {return left.itemcode > right.itemcode;});
		Scan(itemlist);


		itemlist.clear();
		int count = itemlist.size();
		cout << "Clear 실행" << endl;
		cout << "남아 있는 아이템 개수: " << count << endl;
		Pause;
	}
	
}

