#include "../Global.h"
// 경험치를 저장할 수 있는 최대 개수
const int MAX_EXP_COUNT = 100;

class ExpStack
{

private:
	float Data[MAX_EXP_COUNT];
	int Head = 0;

public:
	void Clear() // 초기화 ( 데이터 모두 삭제
	{Head = 0;}
	int Count() // 스택에 저장된 요소의 개수
	{return Head;}
	bool IsEmpty()
	{return Head == 0 ? true : false;}
	bool Push(float exp)
	{
		// 가득 차있는지 확인
		if (Head >= MAX_EXP_COUNT)
			return false;

		Data[Head++] = exp;
		return true;
	}
	float pop()
	{
		if (0 == Head)
			return -1.f; // 0일 경우 경험치가 0이 될 수도 있기 때문에 오해의 소지가 없게 보통 음수값 -1를 리턴해준다.
		return Data[--Head];
	}
public:
	ExpStack() {}
	~ExpStack() {}
};




int main()
{
	ExpStack Stack;

	cout << "첫 번째 게임 종료 - 현재의 경험치 145.5f" << endl;
	Stack.Push(145.5f);


	cout << "두 번째 게임 종료 - 현재의 경험치 183.21f" << endl;
	Stack.Push(183.21f);


	cout << "세 번째 게임 종료 - 현재의 경험치 162.3f" << endl;
	Stack.Push(162.3f);

	int count = Stack.Count();
	for (size_t i = 0; i < count; i++)
	{
		cout << "현재 경험치 : " << Stack.pop() << endl;
	}

	cin.get();
}