#include <iostream>
#include <Windows.h>
#include "../06.CPP_Queue/TQueue.h"
// 큰 맵
const size_t MAZE_SIZE = 20;
char map[MAZE_SIZE][MAZE_SIZE] =
{
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '0', '1', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '1', '0', '1', '0', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1'},
	{'1', '0', '0', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
	{'1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1'},
	{'e', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1'},
	{'1', '0', '1', '0', '1', '1', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '0', '1', '1', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', 'x'},
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
};

class Location2D
{
public:
	Location2D(size_t row = 0, size_t col = 0)
		: row(row), col(col)
	{
	}

public:
	size_t row;
	size_t col;
};



void V(size_t xpos, size_t ypos, const int seconds = 500)
{
	Sleep(seconds); // 시스템 1000 -> 1초 재우기

	system("cls");
	for (size_t i = 0; i < MAZE_SIZE; i++)
	{
		for (size_t j = 0; j < MAZE_SIZE; j++)
		{
			if (i == xpos && j == ypos)
			{
				cout << "P ";
				continue;
			}
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
}


bool IsValidLocation(size_t row, size_t col)
{
	if (row >= MAZE_SIZE || col >= MAZE_SIZE)
	{
		return false;
	}

	return map[row][col] == '0' || map[row][col] == 'x';
}

int main()
{
	// 시작 지점을 저장하기 위한 변수 선언.
	size_t startRow = 0;
	size_t startCol = 0;

	// 미로 출력 및 시작 지점 검색.
	for (size_t ix = 0; ix < MAZE_SIZE; ++ix)
	{
		for (size_t jx = 0; jx < MAZE_SIZE; ++jx)
		{
			std::cout << map[ix][jx] << " ";

			// 시작 지점인 경우 저장.
			if (map[ix][jx] == 'e')
			{
				startRow = ix;
				startCol = jx;
			}
		}

		std::cout << std::endl;
	}

	// 시작 지점을 스택에 삽입.
	TQueue<Location2D, MAZE_SIZE> locationStack;
	locationStack.Enqueue(Location2D(startRow, startCol));

	// 미로 탐색.
	size_t count = 0;
	while (locationStack.IsEmpty() == false)
	{
		// 현재 위치 반환.	
		Location2D here = locationStack.Dequeue();

		size_t row = here.row;
		size_t col = here.col;

		// 현재 탐색한 위치 출력
		//std::cout << "(" << row << "," << col << ") ";

		V(here.row, here.col, 500);

		// 가로 10칸 출력했을 때 다음칸에 출력하기 위한 코드.
		count++;
		if (count == 10)
		{
			count = 0;
			std::cout << std::endl;
		}

		// 출구에 도착했으면, 탐색 성공.
		if (map[row][col] == 'x')
		{
			std::cout << " \n미로 탐색 성공\n";
			std::cin.get();
			return 0;
		}

		// 출구가 아닌 경우에는, 탐색한 위치를 방문한 위치로 표시.
		map[row][col] = '.';

		// 상/하/좌/우 위치 중 이동 가능한 위치는 스택에 삽입.
		if (IsValidLocation(row - 1, col) == true)
		{
			locationStack.Enqueue(Location2D(row - 1, col));
		}
		if (IsValidLocation(row + 1, col) == true)
		{
			locationStack.Enqueue(Location2D(row + 1, col));
		}
		if (IsValidLocation(row, col - 1) == true)
		{
			locationStack.Enqueue(Location2D(row, col - 1));
		}
		if (IsValidLocation(row, col + 1) == true)
		{
			locationStack.Enqueue(Location2D(row, col + 1));
		}
	}

	std::cout << " \n미로 탐색 실패\n";
}