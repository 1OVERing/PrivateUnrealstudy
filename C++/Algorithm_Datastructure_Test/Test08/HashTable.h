#pragma once
#include <iostream>
#include <string>
#include <list>

class HashTable
{
public:

private:
	using Entry = std::pair<std::string, std::string>;
	static constexpr int bucketCount = 10;
	std::list<Entry> table[bucketCount];
public:
	bool IsEmpty() const;
	void Add(const std::string& key, const std::string& value);
	void Delete(const std::string& key);
	Entry Find(const std::string& key);
	void Print();

public:
	HashTable();
	~HashTable();
};

