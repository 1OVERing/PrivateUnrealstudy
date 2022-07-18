#include "../Global.h"
#include <algorithm>

struct Point
{
	Point(int x, int y) : x(x), y(y) { }

	void Print()
	{
		std::cout << x << ", " << y << std::endl;
	}

	int x;
	int y;
};

int main()
{
	{
		std::vector<int> vec;
		for (int i = 10; i <= 100; i += 10)
			vec.push_back(i);

		cout << "Vector Ÿ������ 10 ~ 100 ���� 10�� ������ �� �ִ�." << endl << endl;
		for (auto iter : vec)
			cout << iter << ", ";
		cout << endl;

		cout << "������ ù��° ���� ���� �Է��ϼ���" << endl << endl;
		int num1 = 0;
		cin >> num1;

		cout << "������ �ι�° ���� ���� �Է��ϼ���" << endl << endl;
		int num2 = 0;
		cin >> num2;

		auto iter1 = std::find(vec.begin(), vec.end(), num1);
		auto iter2 = std::find(vec.begin(), vec.end(), num2);
		std::reverse(iter1, ++iter2);

		cout << endl;
		cout << endl;
		system("cls");
		cout << num1 << "�� ���� " << num2 << "�� ���� ������ �Ϸ�." << endl << endl;
		for (auto iter : vec)
			cout << iter << ", ";
		cout << endl << endl;

		cout << "�ι�° ������ �̵�" << endl << endl;
		Pause;
		system("cls");
		//====================================================================================================== 2 ��° ����
		cout << "Vector Ÿ������ 10 ~ 100 ���� Ư�� ������ �������� ���·� �� �ִ�." << endl << endl;
		for (auto iter : vec)
			cout << iter << ", ";
		cout << endl << endl;

		cout << "Ư�� �� ������ �������� ������ ���մϴ�. Ư�� ������ 2���� �Է����ּ���" << endl << endl;
		cout << "ù��° ���� ���� �Է��ϼ���" << endl << endl;
		num1 = 0;
		cin >> num1;

		cout << "�ι�° ���� ���� �Է��ϼ���" << endl << endl;
		num2 = 0;
		cin >> num2;

		int count = 0;
		for (auto& iter : vec)
		{
			if (num1 < iter && iter < num2)
				count++;
		}
		cout << num1 << " �� " << num2 << "������ ������ ������ " << count << "�� �Դϴ�." << endl << endl;

		cout << "����° ������ �̵�" << endl << endl;
		Pause;
		system("cls");
	}

	{
		std::vector<Point> points({ Point(1,1), Point(2,2), Point(3,3), Point(4,4), Point(5,5) });

		// std::for_each�� ����� ��� ������ x, y�� 10�� ������Ų��.
		std::for_each(points.begin(), points.end(), [](Point& p) {p.x += 10; p.y += 10; });

		// ��� ���.
		for (auto& point : points)
		{
			point.Print();
		}

		std::cin.get();
	}
}