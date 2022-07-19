#include "../Global.h"



int main()
{
	std::array<int, 10> arr;
	cout << "크기가 10인 배열에서 연속적으로 중복된 값을 제거합니다. 배열을 입력해주세요" << endl;
	Pause;
	for (int i = 0; i < 10; ++i)
	{
		system("cls");
		cout << "배열 " << i << "번째의 데이터를 입력해주세요 : 0 ~ 9" << endl;
		cin >> arr[i];
	}
	system("cls");
	cout << "Array: ";
	for (auto iter: arr)
		cout << iter << ", ";
	cout << endl;

	Pause;
	system("cls");
	cout << "중복 제거 완료" << endl;
	int temp = 0;

	for (int i = 0; i < arr.size() - 1; ++i)
	{
		if (arr[i] == arr[i + 1])
		{
			temp++;
			arr[i + 1] = 999;
		}
	}

	cout << "Array: ";
	for (auto iter : arr)
	{
		if (999 != iter)
		{
			cout << iter << ", ";
		}
	}


	return 0;
}