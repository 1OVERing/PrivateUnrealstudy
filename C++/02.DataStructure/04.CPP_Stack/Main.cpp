#include "../Global.h"
// ����ġ�� ������ �� �ִ� �ִ� ����
const int MAX_EXP_COUNT = 100;

class ExpStack
{

private:
	float Data[MAX_EXP_COUNT];
	int Head = 0;

public:
	void Clear() // �ʱ�ȭ ( ������ ��� ����
	{Head = 0;}
	int Count() // ���ÿ� ����� ����� ����
	{return Head;}
	bool IsEmpty()
	{return Head == 0 ? true : false;}
	bool Push(float exp)
	{
		// ���� ���ִ��� Ȯ��
		if (Head >= MAX_EXP_COUNT)
			return false;

		Data[Head++] = exp;
		return true;
	}
	float pop()
	{
		if (0 == Head)
			return -1.f; // 0�� ��� ����ġ�� 0�� �� ���� �ֱ� ������ ������ ������ ���� ���� ������ -1�� �������ش�.
		return Data[--Head];
	}
public:
	ExpStack() {}
	~ExpStack() {}
};




int main()
{
	ExpStack Stack;

	cout << "ù ��° ���� ���� - ������ ����ġ 145.5f" << endl;
	Stack.Push(145.5f);


	cout << "�� ��° ���� ���� - ������ ����ġ 183.21f" << endl;
	Stack.Push(183.21f);


	cout << "�� ��° ���� ���� - ������ ����ġ 162.3f" << endl;
	Stack.Push(162.3f);

	int count = Stack.Count();
	for (size_t i = 0; i < count; i++)
	{
		cout << "���� ����ġ : " << Stack.pop() << endl;
	}

	cin.get();
}