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
	static constexpr int bucketCount = 10;
	TLinkedList<Entry> table[bucketCount];
public:
	bool IsEmpty() const;
	void Add(const std::string& key, const std::string& value);
	void Delete(const std::string& key);
	Entry Find(const std::string& key);
	void Print();

private:
	int GetHash(int key);

public:
	HashTable();
	~HashTable();
};

