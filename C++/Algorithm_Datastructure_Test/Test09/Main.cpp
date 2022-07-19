/*
- �迭 array�� i��° ���ں��� j��° ���ڱ��� �ڸ� ����, �������� ��, k��°�� �ִ� ���� ���غ���.
- ���� ���, array = [6, 3, 2, 7, 9, 8, 1], i = 1, j = 5, k = 3�� ���
    1. array�� 1��°���� 5��°���� �ڸ��� [6, 3, 2, 7, 9]
    2. 1���� �ڸ� �迭�� �����ϸ� [2, 3, 6, 7, 9]
    3. 2���� ������ �迭�� 3��° ���� 6
*/
#include "../Global.h"

int main()
{
    {
		cout << "����1 Array = {6,3,2,7,9,8,1,8,7,9}���� i��°���� j��° ���� �ڸ��� �����ϰ� k��° ���� ������" << endl;
		cout << "i = 3, j = 8, k = 2��� �����Ѵ�." << endl;
		std::array<int, 10> arr = { 6,3,2,7,9,8,1,8,7,9 };
		cout << endl;
		cout << "Array: ";
		for (int i = 0; i < 7; ++i)
			cout << arr[i] << ", ";
		cout << endl;
		int a = 0;
		int count = 0;
		for (int i = 0; i < 10; i++)
		{
			if (3 < i && 8 > i)
			{
				arr[count] = arr[i];
				count++;
			}
		}
		for (int i = count; i < 10; i++)
		{
			arr[i] = 0;
		}
		auto iter = arr.begin();
		for (; *iter != 0; ++iter)
		{
		}
		std::sort(arr.begin(), iter);

		cout << "�߶󳻱� �� ���� ���" << endl;
		cout << "Array : ";
		for (auto iterstart = arr.begin(); iterstart != iter; ++iterstart)
			cout << *iterstart << ", ";
		cout << endl;

		cout << endl << endl << "2��° ������ ���" << endl;
		cout << "������ :" << arr[2] << endl;

		cout << endl << endl << "2�� 2���� ������ �̵� ";
		Pause;
    }
	{
		system("cls");
		cout << "2������ : �迭 array, [i, j, k]�� ���ҷ� ����\n \
2���� �迭 commands�� �Ű������� �־��� �� commands�� ��� ���ҿ� ���� \n \
������ ������ ������ �������� �� ���� ����� �迭�� ��� ��ȯ�ϴ� �Լ� GetResult�� �ۼ��غ���." << endl << endl << endl;

		std::array<int, 10> arr;

		for(int i = 0; i < 10; ++i)
		{
			system("cls");
			cout << "�� 10���� �������� "<<i << "��° �����͸� �Է����ּ���" << endl;
			cin >> arr[i];
		}
		system("cls");
		cout << "������ �Է� �Ϸ� " << endl;
		cout << "������ : ";
		for (auto iter : arr)
			cout << iter << ", ";
		cout << endl;
		Pause;
		int com[3] = {};
		for (int  i = 0; i < 3; ++i)
		{
			system("cls");
			cout << "Ŀ�Ǵ� "<< i + 1 << " �� �Է����ּ��� : 1 = �ڸ� ���� ���� 2 = �ڸ� ������ ���� 3 = ������ ��� �ε���" << endl;
			cin >> com[i];
		}
		system("cls");
		cout << "�ڸ� ������ : ";
		for(int i= com[0];i < com[1];++i)
		{
			cout << arr[i] << ", ";
		}
		int out = 0;
		for (int i = com[0]; i < com[1]; ++i)
		{
			if (out == com[2])
			{
				out = arr[--i];
				break;
			}
			out++;
		}

		cout << endl;
		cout << "��� " << com[2] << "��° ������ : " << out << endl;
		Pause;
	}

	return 0;
}