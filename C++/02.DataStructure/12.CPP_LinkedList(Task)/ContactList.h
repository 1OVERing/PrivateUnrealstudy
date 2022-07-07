#pragma once
#include "Contact.h"

class ContactList
{
private:
	Contact* head;
	size_t size;

public:
	void AddToHead(const std::wstring& name);
	void Print();
	void Insert(const std::wstring& name);
	void DeleteNode(const std::wstring& name);

public:
	ContactList();
	~ContactList();
};

