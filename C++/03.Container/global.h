#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <deque>
#include <unordered_map>
#include <set>
#include <chrono>

using std::cout;
using std::cin;
using std::endl;

#define clean system("cls");
#define Pause system("pause");

template<typename T>
void Scan(const T& container)
{

	for (auto iter : container)
		cout << iter << endl;

	cout << endl;
	Pause;
	clean;
}