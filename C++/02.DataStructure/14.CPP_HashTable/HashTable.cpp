#include "HashTable.h"

HashTable::HashTable()
{
}

HashTable::~HashTable()
{
}

// HashFunction
int GenerateKey(const std::string& skey)
{
	int key = 0;
	for (size_t i = 0; i < skey.length(); ++i)
	{key = key * 31 + skey[i];}

	return std::abs(key);
}

bool HashTable::IsEmpty() const
{
	size_t sum = 0;
	for (int i = 0; i < bucketCount; ++i)
		sum += table[i].Count();

	return 0 == sum;
}

void HashTable::Add(const std::string& key, const std::string& value)
{
	int hash_key = GenerateKey(key);
	int bucketIndex = GetHash(hash_key);

	TLinkedList<Entry>& position = table[bucketIndex];
	for (size_t i = 0; i < position.Count(); ++i)
	{
		if (position[i]->data.key == key)
		{
			std::cout << "이미 동일한 키의 데이터가 저장돼 있습니다.\n";
			return;
		}
	}

	position.PushLast(Entry(key, value));
}

void HashTable::Delete(const std::string& key)
{
	int hash_key = GenerateKey(key);
	int bucketIndex = GetHash(hash_key);

	auto& position = table[bucketIndex];

	for (size_t i = 0; i < position.Count(); i++)
	{
		if (position[i]->data.key == key)
		{
			position.Delete(position[i]->data);
			std::cout << "항목이 삭제되었습니다.\n";
			return;
		}
	}
	std::cout << "삭제할 데이터를 찾지 못했습니다.\n";
}

HashTable::Entry HashTable::Find(const std::string& key)
{
	int hashKey = GenerateKey(key);

	int bucketIndex = GetHash(hashKey);

	if (table[bucketIndex].Count() == 0)
	{
		std::cout << "해당 키로 데이터를 찾지 못했습니다.\n";
		return Entry("", "");
	}

	for (size_t i = 0; i < table[bucketIndex].Count(); ++i)
	{
		if (table[bucketIndex][i]->data.key == key)
		{
			return table[bucketIndex][i]->data;
		}
	}

	std::cout << "해당 키로 데이터를 찾지 못했습니다.\n";
	return Entry("", "");
}

void HashTable::Print()
{
	for (int ix = 0; ix < bucketCount; ++ix)
	{
		if (table[ix].Count() == 0)
		{
			continue;
		}

		for (size_t jx = 0; jx < table[ix].Count(); ++jx)
		{
			std::cout << "키: " << table[ix][jx]->data.key << " 값: " << table[ix][jx]->data.value << std::endl;
		}
	}
}

int HashTable::GetHash(int key)
{
	return key % bucketCount;
}
