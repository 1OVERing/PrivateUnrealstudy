#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

struct User
{
	int uid;
	int level;
	int money;
};

struct AddUserMoney
{
	User operator()(const User& user1, const User& user2)
	{
		User User = {};
		// 여기 작성.
		User.money = user1.money + user2.money;
		return User;
	}
};

int main()
{
	User user1{ 1, 10, 2000 };
	User user2{ 2, 11, 2050 };
	User user3{ 3, 12, 2200 };
	User user4{ 4,  5, 1000 };
	User user5{ 5,  9, 2030 };

	vector<User> users{ user1, user2, user3, user4, user5 };
	for (const auto& user : users)
	{
		cout << user.uid << " : " << user.money << ", ";
	}

	cout << endl << endl;

	// 여기 작성.
	// 알고리즘 적용후 결과 출력.
	
	vector<int> vec1 = {1,2,3,4,5,6,7,8,9};
	User result = {};
	AddUserMoney s;
	result = accumulate(users.begin(), users.end(),result, AddUserMoney());
	cout << result.money;
}