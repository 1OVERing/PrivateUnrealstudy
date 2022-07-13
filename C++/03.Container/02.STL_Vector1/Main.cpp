#include "../global.h"

struct RoomUser
{
	int userCode;
	int level;


	RoomUser(int code =0,int lv = 0) : userCode(code),level(lv){}
	~RoomUser(){}
};

int main()
{
	std::vector<RoomUser> vecUser;
	vecUser.reserve(10);
	vecUser.emplace_back(RoomUser(1, 10));
	vecUser.emplace_back(RoomUser(2, 20));
	vecUser.emplace_back(RoomUser(3, 30));

	for (size_t i = 0; i < vecUser.size(); i++)
	{
		//if (0 == vecUser[i].userCode)
		//	continue;

		cout << "����� �ڵ� : " << vecUser[i].userCode << "  ���� : " << vecUser[i].level << endl;
	}
	cout << endl << endl;

	for(auto iter:vecUser)
		cout << "����� �ڵ� : " << iter.userCode << "  ���� : " << iter.level << endl;


	cout << endl << endl;
	Pause;
	Clean;

	for(auto iter = vecUser.rbegin(); iter != vecUser.rend();++iter)
		cout << "����� �ڵ� : " << iter->userCode << "  ���� : " << iter->level << endl;

	cout << endl << endl;
	Pause;
	Clean;

	vecUser.clear();
	if (vecUser.empty() == true)
		cout << "�����Ͱ� �����ϴ�." << endl << endl;
	Pause;
}