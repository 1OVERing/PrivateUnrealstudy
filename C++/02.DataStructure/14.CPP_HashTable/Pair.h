#pragma once

template<typename KeyType, typename ValueType>
class TPair
{
public:
	KeyType		key;
	ValueType	value;


public:
	bool operator==(const TPair<KeyType, ValueType>& other)
	{return key == other.key && value == other.value;}
	bool operator!=(const TPair<KeyType, ValueType>& other)
	{return key != other.key && value != other.value;}
	bool operator>(const TPair<KeyType, ValueType>& other)
	{return key > other.key}
	bool operator<(const TPair<KeyType, ValueType>& other)
	{return key > other.key}
	bool operator>=(const TPair<KeyType, ValueType>& other)
	{return key >= other.key}
	bool operator<=(const TPair<KeyType, ValueType>& other)
	{return key <= other.key}
public:
	TPair() : key(),value() {}
	TPair(const KeyType& Key, const ValueType& Value) : key(Key),value(Value){}
	~TPair() {}
};