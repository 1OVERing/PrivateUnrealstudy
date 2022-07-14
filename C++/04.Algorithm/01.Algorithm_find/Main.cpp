#include <iostream>
#include <vector>
#include <algorithm>


struct User
{
	int level;
	int money;
};

struct FindMoneyUser
{
	bool operator() (User& user) const
	{
		return user.money == money;
	}

	int money;
};

int main()
{
	User user1 = { 10, 1000 };
	User user2 = { 20, 2000 };
	User user3 = { 30, 3000 };

	std::vector<User> users = { user1, user2, user3 };
	FindMoneyUser tFindMoneyUser;
	tFindMoneyUser.money = 3000;
	auto search = find_if(users.begin(), users.end(), tFindMoneyUser);
	if (search != users.end())
	{
		std::cout << "�����ϰ� �ִ� ����: " << search->money << "�Դϴ�" << std::endl;
	}else
	{
		std::cout << " �˻� ���� " << std::endl;
	}

	std::cin.get();
}