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
//	size_t row;		// ��
//	size_t column;	// ��
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
//	// ��߽� Ž��
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
//	// ���� ���� ����
//	Stack<Location, MAZE_SIZE> locationStack;
//	//locationStack.push(Location(startRow, startColumn));
//
//	//size_t count = 0;
//	//// �̷�Ž��
//	//while (!locationStack.IsEmpty())
//	//{
//	//	// ������ġ ��ȯ.
//	//	auto here = locationStack.pop();
//
//	//	// ���� Ž���� ��ġ ���
//	//	cout << "(" << here.row << ", " << here.column << ") ";
//	//	count++;
//
//	//	// ���� 10ĭ ��� ������ ����ĭ�� ���
//	//	if (count == 10)
//	//	{
//	//		count = 0;
//	//		cout << endl;
//	//	}
//	//	
//	//	// �ⱸ�� �����ߴ��� Ȯ��
//	//	if (map[here.row][here.column] == 'x')
//	//	{
//	//		cout << "\n �̷� Ž�� ���� \n";
//
//	//		cin.get();
//	//		return 0;
//	//	}
//
//	//	// �ⱸ�� �ƴ� ���
//	//	map[here.row][here.column] = '.';
//
//	//	// �̵�ó��
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
//	//cout << "�̷� Ž�� ����" << endl;
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
	// 1�� ����
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

	//	cout << "�� �հ� : " << exploration(ivalue) << endl;
	//	cin.get();

	//	system("cls");
	//}
	
	// 2�� ����
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
		// std::stoi -> ���ڿ��� ���ڷ� ��ȯ���ִ� �Լ�
		cin.get();
	}

}