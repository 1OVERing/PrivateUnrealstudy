#include "User.h"

GameRoomUser::GameRoomUser()
{
	users.reserve(6);
}

GameRoomUser::~GameRoomUser()
{
}

bool GameRoomUser::AddUser(UserInfo& userInfo)
{
	if (users.empty())
		masterUserName = userInfo.userName;

	users.emplace_back(userInfo);
	return true;
}

bool GameRoomUser::DeleteUser(const char* userName)
{
	auto iter = users.begin();
	auto iterEnd = users.end();

	for (; iter != iterEnd; ++iter)
	{
		if (iter->userName == userName)
		{
			users.erase(iter);
			return true;
		}

	}
	return false;
}

bool GameRoomUser::IsEmpty()
{
	return users.empty();
}

bool GameRoomUser::IsFull()
{
	return users.size() >= 6;
}

UserInfo& GameRoomUser::GetUserOfName(const char* userName)
{
	for (size_t i = 0 ; i != users.size(); ++i)
	{
		if (users[i].userName == userName)
		{
			return users[i];
		}
	}
}

UserInfo& GameRoomUser::GetMasterUser()
{
	return users[0];
}

UserInfo& GameRoomUser::GetUserOfLastOrder()
{
	return *(--users.end());
	// // O: 여기에 return 문을 삽입합니다.
}

bool GameRoomUser::BanUser(int orderNum)
{
	auto iter = users.begin();
	if (users.size() >= orderNum - 1)
	{
		for (size_t i = 0; i < users.size(); ++i)
		{
			if (i == orderNum - 1)
			{
				users.erase(iter);
				return true;
			}
			iter++;
		}
	}

	if (masterUserName != users[0].userName)
		masterUserName = users[0].userName;

	return false;
}

void GameRoomUser::Clear()
{
	users.clear();
}
