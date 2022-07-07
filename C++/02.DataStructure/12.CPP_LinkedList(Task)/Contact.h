#pragma once
#include <iostream>
#include <string>

class Contact
{
	friend std::wostream& operator<< (std::wostream& os, const Contact& contact);
	friend class ContactList;
private:
	std::wstring name;
	Contact* next;

public:
	Contact(const std::wstring& name);
	~Contact();

};

