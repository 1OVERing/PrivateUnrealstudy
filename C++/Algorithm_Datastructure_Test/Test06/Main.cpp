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

		cout << "Vector 타입으로 10 ~ 100 까지 10의 단위씩 들어가 있다." << endl << endl;
		for (auto iter : vec)
			cout << iter << ", ";
		cout << endl;

		cout << "뒤집을 첫번째 범위 값을 입력하세요" << endl << endl;
		int num1 = 0;
		cin >> num1;

		cout << "뒤집을 두번째 범위 값을 입력하세요" << endl << endl;
		int num2 = 0;
		cin >> num2;

		auto iter1 = std::find(vec.begin(), vec.end(), num1);
		auto iter2 = std::find(vec.begin(), vec.end(), num2);
		std::reverse(iter1, ++iter2);

		cout << endl;
		cout << endl;
		system("cls");
		cout << num1 << "값 부터 " << num2 << "값 까지 뒤집기 완료." << endl << endl;
		for (auto iter : vec)
			cout << iter << ", ";
		cout << endl << endl;

		cout << "두번째 문제로 이동" << endl << endl;
		Pause;
		system("cls");
		//====================================================================================================== 2 번째 문제
		cout << "Vector 타입으로 10 ~ 100 까지 특정 범위로 리버스된 상태로 들어가 있다." << endl << endl;
		for (auto iter : vec)
			cout << iter << ", ";
		cout << endl << endl;

		cout << "특정 값 사이의 데이터의 개수를 구합니다. 특정 데이터 2개를 입력해주세요" << endl << endl;
		cout << "첫번째 범위 값을 입력하세요" << endl << endl;
		num1 = 0;
		cin >> num1;

		cout << "두번째 범위 값을 입력하세요" << endl << endl;
		num2 = 0;
		cin >> num2;

		int count = 0;
		for (auto& iter : vec)
		{
			if (num1 < iter && iter < num2)
				count++;
		}
		cout << num1 << " 와 " << num2 << "사이의 데이터 개수는 " << count << "개 입니다." << endl << endl;

		cout << "세번째 문제로 이동" << endl << endl;
		Pause;
		system("cls");
	}

	{
		std::vector<Point> points({ Point(1,1), Point(2,2), Point(3,3), Point(4,4), Point(5,5) });

		// std::for_each를 사용해 모든 원소의 x, y에 10씩 증가시킨다.
		std::for_each(points.begin(), points.end(), [](Point& p) {p.x += 10; p.y += 10; });

		// 결과 출력.
		for (auto& point : points)
		{
			point.Print();
		}

		std::cin.get();
	}
}