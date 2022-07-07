#include "Contact.h"

Contact::Contact(const std::wstring& name) : name(name),next(nullptr)
{
}

Contact::~Contact()
{
}

std::wostream& operator<<(std::wostream& os, const Contact& contact)
{
	return os << L"Name: " << contact.name;
}