// �̷�Ž��
#include "Stack.h"
#include <Windows.h>
#include <iostream>
#include "../Global.h"
// ū ��.
const size_t MAZE_SIZE = 20;
char map[MAZE_SIZE][MAZE_SIZE] =
{
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1'},
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


//// ���� ��.
//const size_t MAZE_SIZE = 6;
//char map[MAZE_SIZE][MAZE_SIZE] =
//{
//	{'1','1','1','1','1','1'},
//	{'e','0','1','0','0','1'},
//	{'1','0','0','0','1','1'},
//	{'1','0','1','0','1','1'},
//	{'1','0','1','0','0','x'},
//	{'1','1','1','1','1','1'}
//};



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
	bool loop = true;
	while (loop)
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
		Stack<Location2D, MAZE_SIZE> locationStack;
		locationStack.Push(Location2D(startRow, startCol));

		// �̷� Ž��.
		size_t count = 0;
		while (locationStack.IsEmpty() == false)
		{
			// ���� ��ġ ��ȯ.	
			Location2D here = locationStack.Pop();

			size_t row = here.row;
			size_t col = here.col;

			// ���� Ž���� ��ġ ���
			//std::cout << "(" << row << "," << col << ") ";

			V(here.row, here.col,100);

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
				Sleep(5000);
				break;
			}

			// �ⱸ�� �ƴ� ��쿡��, Ž���� ��ġ�� �湮�� ��ġ�� ǥ��.
			map[row][col] = '.';

			// ��/��/��/�� ��ġ �� �̵� ������ ��ġ�� ���ÿ� ����.
			if (IsValidLocation(row - 1, col) == true)
			{
				locationStack.Push(Location2D(row - 1, col));
			}
			if (IsValidLocation(row + 1, col) == true)
			{
				locationStack.Push(Location2D(row + 1, col));
			}
			if (IsValidLocation(row, col - 1) == true)
			{
				locationStack.Push(Location2D(row, col - 1));
			}
			if (IsValidLocation(row, col + 1) == true)
			{
				locationStack.Push(Location2D(row, col + 1));
			}
		}

		std::cout << " \n�̷� Ž�� ����\n";
	}
}

//#include <stack>
//#include "Stack.h"
//#include "Stack2.h"
//#include "../Global.h"
//#include <Windows.h>
//
//int exploration(Stack<int>& stack)
//{
//	int value = 0;
//	std::vector<int> vec;
//	for (;!stack.IsEmpty();)
//	{
//		int a = stack.Pop();
//
//		if (a == 0)
//		{
//			stack.Pop();
//		}
//		else
//		{
//			vec.push_back(a);
//		}
//	}
//
//	for (auto iter : vec)
//	{
//		value += iter;
//	}
//	return value;
//}
//
//void PrintLocation()
//{
//	system("cls");
//
//	for (size_t i = 0; i < MAZE_SIZE; i++)
//	{
//
//	}
//
//}
//int main()
//{
//	// 1�� ����
//	{
//		/*int count;
//		cin >> count;
//		Stack<int> ivalue;
//	
//		for (int i = 0; i < count; i++)
//		{
//			int num = 0;
//			cin >> num;
//			ivalue.Push(num);
//		}
//	
//		cout << "�� �հ� : " << exploration(ivalue) << endl;
//		cin.get();
//	
//		system("cls");*/
//	}
//	
//	// 2�� ����
//	{
//		//std::string ivalue;
//		//Stack<int> stack;
//		//cin >> ivalue;
//		//bool Ispush = false;
//		//int count = std::stoi(ivalue);
//		//for (int i = 0; i < count; i++)
//		//{
//		//	cin >> ivalue;
//		//	if (Ispush)
//		//	{
//		//		stack.Push(std::stoi(ivalue));
//		//		Ispush = false;
//		//	}
//		//	if ("push" == ivalue)
//		//	{
//		//		i--;
//		//		Ispush = true;
//		//		continue;
//		//	}
//		//	if ("pop" == ivalue)
//		//	{
//		//		stack.Pop();
//		//	}
//		//	if ("empty" == ivalue)
//		//	{
//		//		cout << stack.IsEmpty() << endl;
//		//	}
//		//}
//		//// std::stoi -> ���ڿ��� ���ڷ� ��ȯ���ִ� �Լ�
//		//cin.get();
//	}
//
//	// _Getcontainer �Լ� �׽�Ʈ
//	{
//		//Stack2<int> Stack;
//		//std::stack<int,std::vector<int>> stack;
//		//for (int i = 1; i < 10; i++)
//		//	Stack.Push(i);
//		//for (int i = 1; i < 10; i++)
//		//	stack.push(i);
//		//int a = *stack._Get_container().begin();
//		//a = *Stack._Get_container().begin();
//		//for (auto iter : Stack._Get_container())
//		//	cout << iter << endl;
//	}
//}
