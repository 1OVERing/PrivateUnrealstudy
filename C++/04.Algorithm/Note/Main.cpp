// Up/down_casting
/*#include"A.h"
#include"B.h"
#include"C.h"
#include <vector>


int main()
{
	std::vector<A*> Aarr;
	B* b = new B;
	C* c = new C;
	Aarr.emplace_back(static_cast<A*>(b));
	Aarr.emplace_back(c);

	int bx = static_cast<B*>(Aarr[0])->Bx();
	int by = static_cast<B*>(Aarr[0])->By();

	int cx = static_cast<C*>(Aarr[1])->Cx();
	int cy = static_cast<C*>(Aarr[1])->Cy();

	delete b;
	delete c;
}*/

#include <iostream>
#include <random>

//using namespace std;
//
//inline int Partition(int* array, int left, int right)
//{
//	int pivot = array[right];
//
//	int kx = left - 1;
//	for (int ix = left; ix < right; ++ix)
//	{
//		if (array[ix] < pivot)
//		{
//			kx++;
//			int temp = array[ix];
//			array[ix] = array[kx];
//			array[kx] = temp;
//		}
//	}
//
//	array[right] = array[kx + 1];
//	array[kx + 1] = pivot;
//	return kx + 1;
//}
//
//// �� ���� : �迭�� left ~ right �׸���� ������������ �����ϴ� �Լ�
//inline void QuickSort(int* array, int left, int right)
//{
//	if (left < right)
//	{
//		int partition = Partition(array, left, right);
//
//		QuickSort(array, left, partition - 1);
//		QuickSort(array, partition + 1, right);
//	}
//}
//
//int main()
//{
//	random_device rd;
//	mt19937 gen(rd());
//
//	uniform_int_distribution<int> dist(0, 10);
//
//	int container[10];
//
//	cout << "���õ� ��: \n";
//	for (int ix = 0; ix < 10; ++ix)
//	{
//		int value = dist(gen);
//		cout << value << " ";
//		container[ix] = value;
//	}
//
//	cout << endl << endl;
//
//
//	QuickSort(container, 0, 9);
//
//	cout << "�� ���� �� ������ Ȯ��\n";
//	for (int ix = 0; ix < 10; ++ix)
//	{
//		cout << container[ix] << " ";
//	}
//
//	cout << endl;
//
//	cin.get();
//}

