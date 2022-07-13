#include "../global.h"


int main()
{
	std::vector<int> vec1;
	vec1.reserve(10);

	cout << "============= ���� �׽�Ʈ0 =============\n";
	vec1.emplace_back(10);
	vec1.emplace_back(20);
	vec1.emplace_back(30);
	vec1.emplace_back(40);
	vec1.emplace_back(50);
	Scan(vec1);

	cout << "============= ���� �׽�Ʈ1 =============\n";

	auto iter = vec1.begin();

	vec1.insert(iter, 1);
	Scan(vec1);

	cout << "============= ���� �׽�Ʈ 2 =============" << endl;
	iter = vec1.begin();
	vec1.insert(++iter, 2, 2);
	Scan(vec1);

	cout << "============= ���� �׽�Ʈ 3 =============" << endl;
	std::vector<int> vec2({ 1000 ,2000 ,3000 ,4000 });
	iter = vec1.begin();
	vec1.insert(++iter, vec2.begin(), vec2.end());
	Scan(vec1);

	cout << "============= ���� �׽�Ʈ 4 =============" << endl;
	iter = vec1.begin();
	vec1.insert(iter, { 100,200,300,400 });
	Scan(vec1);


}