/*
- 배열 array의 i번째 숫자부터 j번째 숫자까지 자른 다음, 정렬했을 때, k번째에 있는 수를 구해보자.
- 예를 들어, array = [6, 3, 2, 7, 9, 8, 1], i = 1, j = 5, k = 3인 경우
    1. array의 1번째부터 5번째까지 자르면 [6, 3, 2, 7, 9]
    2. 1에서 자른 배열을 정렬하면 [2, 3, 6, 7, 9]
    3. 2에서 정렬한 배열의 3번째 수는 6
*/
#include "../Global.h"

int main()
{
    {
		cout << "문제1 Array = {6,3,2,7,9,8,1,8,7,9}에서 i번째부터 j번째 까지 자르고 정렬하고 k번째 수를 구하자" << endl;
		cout << "i = 3, j = 8, k = 2라고 가정한다." << endl;
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

		cout << "잘라내기 후 정렬 출력" << endl;
		cout << "Array : ";
		for (auto iterstart = arr.begin(); iterstart != iter; ++iterstart)
			cout << *iterstart << ", ";
		cout << endl;

		cout << endl << endl << "2번째 데이터 출력" << endl;
		cout << "데이터 :" << arr[2] << endl;

		cout << endl << endl << "2번 2차원 문제로 이동 ";
		Pause;
    }
	{
		system("cls");
		cout << "2번문제 : 배열 array, [i, j, k]를 원소로 가진\n \
2차원 배열 commands가 매개변수로 주어질 때 commands의 모든 원소에 대해 \n \
위에서 설명한 연산을 적용했을 떄 나온 결과를 배열에 담아 반환하는 함수 GetResult를 작성해보자." << endl << endl << endl;

		std::array<int, 10> arr;

		for(int i = 0; i < 10; ++i)
		{
			system("cls");
			cout << "총 10개의 데이터중 "<<i << "번째 데이터를 입력해주세요" << endl;
			cin >> arr[i];
		}
		system("cls");
		cout << "데이터 입력 완료 " << endl;
		cout << "데이터 : ";
		for (auto iter : arr)
			cout << iter << ", ";
		cout << endl;
		Pause;
		int com[3] = {};
		for (int  i = 0; i < 3; ++i)
		{
			system("cls");
			cout << "커맨더 "<< i + 1 << " 를 입력해주세요 : 1 = 자를 시작 지점 2 = 자를 마지막 지점 3 = 정렬후 출력 인덱스" << endl;
			cin >> com[i];
		}
		system("cls");
		cout << "자른 데이터 : ";
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
		cout << "출력 " << com[2] << "번째 데이터 : " << out << endl;
		Pause;
	}

	return 0;
}