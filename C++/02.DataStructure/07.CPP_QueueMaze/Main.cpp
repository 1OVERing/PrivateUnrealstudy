#include <iostream>
#include <Windows.h>
#include "../06.CPP_Queue/TQueue.h"
// ū ��
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
	Sleep(seconds); // �ý��� 1000 -> 1�� ����

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
	// ���� ������ �����ϱ� ���� ���� ����.
	size_t startRow = 0;
	size_t startCol = 0;

	// �̷� ��� �� ���� ���� �˻�.
	for (size_t ix = 0; ix < MAZE_SIZE; ++ix)
	{
		for (size_t jx = 0; jx < MAZE_SIZE; ++jx)
		{
			std::cout << map[ix][jx] << " ";

			// ���� ������ ��� ����.
			if (map[ix][jx] == 'e')
			{
				startRow = ix;
				startCol = jx;
			}
		}

		std::cout << std::endl;
	}

	// ���� ������ ���ÿ� ����.
	TQueue<Location2D, MAZE_SIZE> locationStack;
	locationStack.Enqueue(Location2D(startRow, startCol));

	// �̷� Ž��.
	size_t count = 0;
	while (locationStack.IsEmpty() == false)
	{
		// ���� ��ġ ��ȯ.	
		Location2D here = locationStack.Dequeue();

		size_t row = here.row;
		size_t col = here.col;

		// ���� Ž���� ��ġ ���
		//std::cout << "(" << row << "," << col << ") ";

		V(here.row, here.col, 500);

		// ���� 10ĭ ������� �� ����ĭ�� ����ϱ� ���� �ڵ�.
		count++;
		if (count == 10)
		{
			count = 0;
			std::cout << std::endl;
		}

		// �ⱸ�� ����������, Ž�� ����.
		if (map[row][col] == 'x')
		{
			std::cout << " \n�̷� Ž�� ����\n";
			std::cin.get();
			return 0;
		}

		// �ⱸ�� �ƴ� ��쿡��, Ž���� ��ġ�� �湮�� ��ġ�� ǥ��.
		map[row][col] = '.';

		// ��/��/��/�� ��ġ �� �̵� ������ ��ġ�� ���ÿ� ����.
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

	std::cout << " \n�̷� Ž�� ����\n";
}