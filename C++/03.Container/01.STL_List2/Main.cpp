#include "../global.h"



int main()
{
	std::list<int> list;
	list.push_back(1);
	list.push_back(1);
	
	// 첫번째 위치 삽입 테스트
	cout << "삽입테스트 1번째 위치에 100 삽입" << endl << endl;
	list.insert(list.begin(), 100);
	Scan(list);

	cout << "삽입테스트 2 2번째 위치에 200 2개 삽입" << endl << endl;
	std::list<int>::iterator iter = list.begin();
	iter++;
	list.insert(iter,2, 200);
	Scan(list);

	std::list<int>list2;
	list2.push_back(1000);
	list2.push_back(2000);
	list2.push_back(3000);
	list2.push_back(4000);

	cout << "삽입테스트 3 2번째 위치에 list2의 모든 데이터 삽입" << endl << endl;
	iter = list.begin();
	iter++;
	list.insert(iter,list2.begin(),list2.end());
	Scan(list);

	cout << "삭제테스트 1 remove을 이용한 데이터 삭제\n\n";
	iter = list.begin();
	list.remove(*iter);
	Scan(list);
}