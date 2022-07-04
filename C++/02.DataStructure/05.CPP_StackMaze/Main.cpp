//#include "../Global.h"
//#include "Stack.h"
//
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
//
//bool IsValidLocation(size_t row, size_t column)
//{
//	if (row >= MAZE_SIZE || column >= MAZE_SIZE)
//		return false;
//
//	return map[row][column] == '0' || map[row][column] == 'x';
//}
//class Location
//{
//public:
//	size_t row;		// 열
//	size_t column;	// 행
//
//
//public:
//
//
//public:
//	Location(size_t row = 0, size_t column = 0) : row(row), column(column)
//	{}
//	~Location() {}
//};
//
//
//int main()
//{
//	size_t startRow = 0u;
//	size_t startColumn = 0u;
//	
//	// 출발시 탐색
//	{
//		for (size_t i = 0; i < MAZE_SIZE; i++)
//		{
//			for (size_t j = 0; j < MAZE_SIZE; j++)
//			{
//				cout << map[i][j] << " ";
//				if (map[i][j] == 'e')
//				{
//					startRow = i;
//					startColumn = j;
//				}
//			}
//		}
//	}
//
//	// 시작 지점 저장
//	Stack<Location, MAZE_SIZE> locationStack;
//	//locationStack.push(Location(startRow, startColumn));
//
//	//size_t count = 0;
//	//// 미로탐색
//	//while (!locationStack.IsEmpty())
//	//{
//	//	// 현재위치 반환.
//	//	auto here = locationStack.pop();
//
//	//	// 현재 탐색한 위치 출력
//	//	cout << "(" << here.row << ", " << here.column << ") ";
//	//	count++;
//
//	//	// 가로 10칸 출력 했으면 다음칸에 출력
//	//	if (count == 10)
//	//	{
//	//		count = 0;
//	//		cout << endl;
//	//	}
//	//	
//	//	// 출구에 도착했는지 확인
//	//	if (map[here.row][here.column] == 'x')
//	//	{
//	//		cout << "\n 미로 탐색 성공 \n";
//
//	//		cin.get();
//	//		return 0;
//	//	}
//
//	//	// 출구가 아닌 경우
//	//	map[here.row][here.column] = '.';
//
//	//	// 이동처리
//	//	if (IsValidLocation(here.row - 1, here.column))
//	//	{
//	//		locationStack.push(Location(here.row - 1, here.column));
//	//	}
//	//	if (IsValidLocation(here.row + 1, here.column))
//	//	{
//	//		locationStack.push(Location(here.row + 1, here.column));
//	//	}
//	//	if (IsValidLocation(here.row, here.column -1))
//	//	{
//	//		locationStack.push(Location(here.row, here.column - 1));
//	//	}
//	//	if (IsValidLocation(here.row, here.column + 1))
//	//	{
//	//		locationStack.push(Location(here.row, here.column + 1));
//	//	}
//	//}
//	//cout << "미로 탐색 실패" << endl;
//	//cin.get();
//
//	return 0;
//}
#include "Stack.h"
#include <stack>
int exploration(Stack<int>& stack)
{
	int value = 0;
	std::vector<int> vec;
	for (;!stack.IsEmpty();)
	{
		int a = stack.pop();

		if (a == 0)
		{
			stack.pop();
		}
		else
		{
			vec.push_back(a);
		}
	}

	for (auto iter : vec)
	{
		value += iter;
	}
	return value;
}


int main()
{
	// 1번 문제
	//{
	//	int count;
	//	cin >> count;
	//	Stack<int> ivalue;

	//	for (int i = 0; i < count; i++)
	//	{
	//		int num = 0;
	//		cin >> num;
	//		ivalue.push(num);
	//	}

	//	cout << "총 합계 : " << exploration(ivalue) << endl;
	//	cin.get();

	//	system("cls");
	//}
	
	// 2번 문제
	{
		std::string ivalue;
		Stack<int> stack;
		cin >> ivalue;
		bool Ispush = false;
		int count = std::stoi(ivalue);
		for (int i = 0; i < count; i++)
		{
			cin >> ivalue;
			if (Ispush)
			{
				stack.push(std::stoi(ivalue));
				Ispush = false;
			}
			if ("push" == ivalue)
			{
				i--;
				Ispush = true;
				continue;
			}
			if ("pop" == ivalue)
			{
				stack.pop();
			}
			if ("size" == ivalue)
			{
				cout << stack.Count() << endl;
			}
			if ("empty" == ivalue)
			{
				cout << stack.IsEmpty() << endl;
			}
		}
		// std::stoi -> 문자열을 숫자로 변환해주는 함수
		cin.get();
	}

}