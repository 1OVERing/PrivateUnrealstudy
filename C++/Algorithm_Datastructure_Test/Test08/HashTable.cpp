#include "HashTable.h"

HashTable::HashTable()
{
}

HashTable::~HashTable()
{
}

// HashFunction
int GenerateKey(const std::string& skey, int bucketCount)
{
	int key = 0;
	// ����ġ ���� ���
	for (size_t i = 0; i < skey.length(); ++i)
	{key = key * 31 + skey[i];}
	//JDK���� ����ϴ� ���
	// key = key*31+ skey[i];

	return std::abs(key) % bucketCount;;
}
bool HashTable::IsEmpty() const
{
	size_t sum = 0;
	for (int i = 0; i < bucketCount; ++i)
	{
		if (0 != sum)
			return 0 == sum;

		sum += table[i].size();
	}

	return 0 == sum;
}
void HashTable::Add(const std::string& key, const std::string& value)
{
	int bucketIndex = GenerateKey(key, bucketCount);

	std::list<Entry>& position = table[bucketIndex];

	auto iter = position.begin();
	auto iterEnd = position.end();
	for (; iter != iterEnd; ++iter)
	{
		if (iter->first == key)
		{
			std::cout << "�̹� ������ Ű�� �����Ͱ� ����� �ֽ��ϴ�.\n";
			position.push_back(Entry(key, value));
			std::cout << "������ Ű�� �����Ͱ� ����� �ֽ��ϴ�.\n";
			return;
		}
	}
	position.push_back(Entry(key, value));
}
void HashTable::Delete(const std::string& key)
{
	int bucketIndex = GenerateKey(key, bucketCount);

	auto& position = table[bucketIndex];

	auto iter = position.begin();
	auto iterEnd = position.end();
	
	for (; iter != iterEnd; ++iter)
	{
		if (iter->first == key)
		{
			position.erase(iter);
			std::cout << "�׸��� �����Ǿ����ϴ�.\n";
			return;
		}
	}
	
	std::cout << "������ �����͸� ã�� ���߽��ϴ�.\n";
}
HashTable::Entry HashTable::Find(const std::string& key)
{
	int bucketIndex = GenerateKey(key, bucketCount);

	if (table[bucketIndex].size() == 0)
	{
		return Entry("", "");
	}

	auto iter = table[bucketIndex].begin();
	auto iterEnd = table[bucketIndex].end();

	for (; iter != iterEnd; ++iter)
	{
		if (iter->first == key)
		{
			return Entry(iter->first,iter->second);
		}
	}

	return Entry("", "");
}
void HashTable::Print()
{
	for (int ix = 0; ix < bucketCount; ++ix)
	{
		if (table[ix].size() == 0)
		{
			continue;
		}

		auto iter = table->begin();
		auto iterEnd = table->end();

		for (; iter != iterEnd; ++iter)
			std::cout << "Ű�� :" << iter->first << "  ������ ��:" << iter->second << std::endl;

	}
}