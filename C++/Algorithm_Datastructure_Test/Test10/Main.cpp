#include "../Global.h"



int main()
{
	std::array<int, 10> arr;
	cout << "ũ�Ⱑ 10�� �迭���� ���������� �ߺ��� ���� �����մϴ�. �迭�� �Է����ּ���" << endl;
	Pause;
	for (int i = 0; i < 10; ++i)
	{
		system("cls");
		cout << "�迭 " << i << "��°�� �����͸� �Է����ּ��� : 0 ~ 9" << endl;
		cin >> arr[i];
	}
	system("cls");
	cout << "Array: ";
	for (auto iter: arr)
		cout << iter << ", ";
	cout << endl;

	Pause;
	system("cls");
	cout << "�ߺ� ���� �Ϸ�" << endl;
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