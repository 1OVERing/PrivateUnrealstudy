#include "GameEngine.h"
#include "Util.h"
#include "Map.h"
#include "../04.CPP_Stack/stack.h"
#include "../Global.h"
#include <iostream>

const char* tile[] = { "  ","■","□", "X ", "P ", "G " };


enum class TileType
{
	Path,
	Wall,
	Empty,
	Passed,
	Player,
	Goal
};

Stack<Position, 100> stack;

void GameEngine::Initialize()
{
	for (int i = 0; i < MAZE_SIZE; i++)
	{
		for (int j = 0; j < MAZE_SIZE; j++)
		{
			if (map[i][j] == '1')
				cout << tile[(int)TileType::Wall];

			else if (map[i][j] == '0')
				cout << tile[(int)TileType::Path];

			else if (map[i][j] == 'e')
			{
				cout << tile[(int)TileType::Player];
				PlayerPosition.x = i;
				PlayerPosition.y = j;
			}
			else if (map[i][j] == 'x')
				cout << tile[(int)TileType::Goal];

			else if (map[i][j] == '.')
				cout << tile[(int)TileType::Passed];

		}
		cout << endl;
		stack.Push(PlayerPosition);
	}
}
void GameEngine::Run()
{
	while(!IsGameEnd())
	{
		Position CurrentPos = stack.Pop();

		Update(CurrentPos);
		Render(CurrentPos);
		PostRender(CurrentPos);

		if (isGameEnd)
		{
			break;
		}
		else
		{
			isGameEnd = stack.IsEmpty();
		}

		Util::Delay(delayTime);
	}
}
void GameEngine::Update(const Position& CurPos)
{
	int x = CurPos.x;
	int y = CurPos.y;

	if (map[x][y] == 'x')
	{
		cout << "미로 탐색 성공.";
		cin.get();
		isGameEnd = true;
		return;
	}

	// map[x][y] = 'P';
}
void GameEngine::Render(const Position& CurPos)
{
	Util::SetPosition(0,0);

	for (int i = 0; i < MAZE_SIZE; i++)
	{
		for (int j = 0; j < MAZE_SIZE; j++)
		{

			switch (map[i][j])
			{
			case '0':
				cout << tile[(int)TileType::Path];
				break;
			case '1':
				cout << tile[(int)TileType::Wall];
				break;
			case '.':
				cout << tile[(int)TileType::Passed];
				break;
			case  'e':
				cout << tile[(int)TileType::Player];
				break;
			case 'x':
				cout << tile[(int)TileType::Goal];
				break;
			default:
				break;
			}
		}
		cout << endl;
	}
}
void GameEngine::PostRender(const Position& CurPos)
{
	int x = CurPos.x;
	int y = CurPos.y;

	if (IsValidPosition(x - 1, y))
	{
		stack.Push(Position(x - 1, y));
	}
	if (IsValidPosition(x + 1, y))
	{
		stack.Push(Position(x + 1, y));
	}
	if (IsValidPosition(x, y - 1))
	{
		stack.Push(Position(x, y - 1));
	}
	if (IsValidPosition(x, y + 1))
	{
		stack.Push(Position(x, y + 1));
	}

	map[x][y] = '.';
}

bool GameEngine::IsValidPosition(int x, int y)
{
	return IsValidPosition(Position(x, y));
}
bool GameEngine::IsValidPosition(const Position& CurPos)
{

	if (CurPos.x < 0 || CurPos.y < 0 || CurPos.x >= MAZE_SIZE || CurPos.y >= MAZE_SIZE)
		return false;

	return map[CurPos.x][CurPos.y] == '0' || map[CurPos.x][CurPos.y] == 'x';
}

