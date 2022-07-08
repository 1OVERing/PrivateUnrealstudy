#pragma once
#include <iostream>
#include <string>
#include "TLinkedList.h"
#include "Pair.h"

class HashTable
{
public:

private:
	using Entry = TPair<std::string, std::string>;
	static constexpr int buketCount = 19;
	TLinkedList<Entry> table[buketCount];
public:

private:
	int GetHash(int key);

public:
	HashTable();
	~HashTable();
};

