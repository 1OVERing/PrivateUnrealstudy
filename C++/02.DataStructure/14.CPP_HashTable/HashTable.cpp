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

		sum += table[i].Count();
	}

	return 0 == sum;
}
void HashTable::Add(const std::string& key, const std::string& value)
{
	int bucketIndex = GenerateKey(key, bucketCount);

	TLinkedList<Entry>& position = table[bucketIndex];
	for (size_t i = 0; i < position.Count(); ++i)
	{
		if (position[i]->data.key == key)
		{
			std::cout << "�̹� ������ Ű�� �����Ͱ� ����� �ֽ��ϴ�.\n";
			position.PushLast(Entry(key, value));
			std::cout << "������ Ű�� �����Ͱ� ����� �ֽ��ϴ�.\n";
			return;
		}
	}

	position.PushLast(Entry(key, value));
}
void HashTable::Delete(const std::string& key)
{
	int bucketIndex = GenerateKey(key, bucketCount);

	auto& position = table[bucketIndex];

	for (size_t i = 0; i < position.Count(); i++)
	{
		if (position[i]->data.key == key)
		{
			position.Delete(position[i]->data);
			std::cout << "�׸��� �����Ǿ����ϴ�.\n";
			return;
		}
	}
	std::cout << "������ �����͸� ã�� ���߽��ϴ�.\n";
}
HashTable::Entry HashTable::Find(const std::string& key)
{
	int bucketIndex = GenerateKey(key, bucketCount);

	if (table[bucketIndex].Count() == 0)
	{
		std::cout << "�ش� Ű�� �����͸� ã�� ���߽��ϴ�.\n";
		return Entry("", "");
	}

	for (size_t i = 0; i < table[bucketIndex].Count(); ++i)
	{
		if (table[bucketIndex][i]->data.key == key)
		{
			return table[bucketIndex][i]->data;
		}
	}

	std::cout << "�ش� Ű�� �����͸� ã�� ���߽��ϴ�.\n";
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
			std::cout << "Ű: " << table[ix][jx]->data.key << " ��: " << table[ix][jx]->data.value << std::endl;
		}
	}
}