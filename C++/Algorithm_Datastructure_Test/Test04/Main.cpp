#include <iostream>
#include <string>
#include <map>

using namespace std;

struct Item
{
	string name;				// 이름
	unsigned short kind;		// 종류
	int price;					// 구입 가격
	int skillCode;				// 스킬 코드
};

int main()
{
	{
		map<string, Item, greater<string>> items;

		Item item1 = { "긴칼", 1, 200, 0 };
		Item item2 = { "성스러운 방패", 2, 1000, 4 };
		Item item3 = { "해머", 1, 500, 0 };

		// Items에 아이템 추가
		items.insert({ item2.name, item2 });
		items.insert({ item1.name, item1 });

		// Items가 비어 있지않다면
		if (items.empty() == false)
		{
			cout << "저장된 아이템 개수: " << items.size() << endl;
		}

		for (auto iter = items.begin(); iter != items.end(); ++iter)
		{
			cout << "이름: " << iter->first << ", 가격: " << iter->second.price << endl;
		}

		auto search = items.find("긴칼");
		if (search == items.end())
		{
			cout << "아이템'긴칼'이 없습니다." << endl;
		}

		cout << endl;

		cout << "올림차순으로 정렬되어있는 map(Key 자료형으로 string 사용)" << endl;

		// initialize list를 사용해 자료 추가.
		map<string, Item, less<string>> items2 =
		{
			{ item2.name, item2 },
			{ item1.name, item1 }
		};

		// operator[]를 사용하여 저장
		items2[item3.name] = item3;

		for (auto iter2 = items2.begin(); iter2 != items2.end(); ++iter2)
		{
			cout << "이름: " << iter2->first << ", 가격: " << iter2->second.price << endl;
		}

		cout << endl;

		cout << "해머의 가격은 얼마? ";
		search = items2.find("해머");
		if (search != items2.end())
		{
			cout << search->second.price << endl;
		}
		else
		{
			cout << "해머는 없습니다" << endl;
		}

		cout << endl;

		// 아이템 "긴칼"을 삭제한다.
		search = items2.find("긴칼");
		if (search != items2.end())
		{
			items2.erase(search);
		}

		cout << "Items2에 있는 아이템 개수: " << items2.size() << endl;

		cin.get();
		cout << endl << endl << endl;
		cout << "아무 키를 누르면 items3를 제작하여 아이템 가격을 기준으로 데이터를 받아옵니다." << endl << endl;
		system("pause");
	}

	system("cls");
	cout << "아이템의 가격을 Key값으로 받아와 내림차순(높은 수 부터) 정렬" << endl << endl;
	multimap<int , Item, greater<int>> items3;

	Item item1 = { "긴칼", 1, 200, 0 };
	Item item2 = { "성스러운 방패", 2, 1000, 4 };
	Item item3 = { "해머", 1, 500, 0 };
	Item item4 = { "똑같은 가격 테스트", 1, 500, 0 };

	// Items에 아이템 추가
	items3.insert({ item2.price, item2 });
	items3.insert({ item1.price, item1 });
	items3.insert({ item3.price, item3 });
	items3.insert({ item4.price, item4 });

	// Items가 비어 있지않다면
	if (items3.empty() == false)
	{
		cout << "저장된 아이템 개수: " << items3.size() << endl;
	}

	for (auto iter = items3.begin(); iter != items3.end(); ++iter)
	{
		cout << "이름: " << iter->second.name << ", 가격: " << iter->second.price << endl;
	}

	auto search = items3.find(200);
	if (search == items3.end())
	{
		cout << "200원 짜리 아이템이 없습니다." << endl;
	}

	cout << endl;

}