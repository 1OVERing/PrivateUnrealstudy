// 미로탐색
#include "Stack.h"
#include <Windows.h>
#include <iostream>
#include "../Global.h"
// 큰 맵.
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


//// 작은 맵.
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
		Stack<Location2D, MAZE_SIZE> locationStack;
		locationStack.Push(Location2D(startRow, startCol));

		// 미로 탐색.
		size_t count = 0;
		while (locationStack.IsEmpty() == false)
		{
			// 현재 위치 반환.	
			Location2D here = locationStack.Pop();

			size_t row = here.row;
			size_t col = here.col;

			// 현재 탐색한 위치 출력
			//std::cout << "(" << row << "," << col << ") ";

			V(here.row, here.col,100);

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
				Sleep(5000);
				break;
			}

			// 출구가 아닌 경우에는, 탐색한 위치를 방문한 위치로 표시.
			map[row][col] = '.';

			// 상/하/좌/우 위치 중 이동 가능한 위치는 스택에 삽입.
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

		std::cout << " \n미로 탐색 실패\n";
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
//	// 1번 문제
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
//		cout << "총 합계 : " << exploration(ivalue) << endl;
//		cin.get();
//	
//		system("cls");*/
//	}
//	
//	// 2번 문제
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
//		//// std::stoi -> 문자열을 숫자로 변환해주는 함수
//		//cin.get();
//	}
//
//	// _Getcontainer 함수 테스트
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
