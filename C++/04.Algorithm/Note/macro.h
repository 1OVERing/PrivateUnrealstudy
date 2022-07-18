#pragma once
#include <string>

class RTTI
{
public:
	RTTI() {}
	RTTI(const std::string& name) : className(name) { }
	const std::string& ClassName() const { return className; }

private:
	std::string className;
};

#define RTTI_DECL \
public:  \
static const RTTI rtti; \
virtual const RTTI& RTTI() { return rtti; }

#define RTTI_IMPL_NOPARENT(name) \
	const RTTI name::rtti(#name);

#define RTTI_IMPL(name, parent)  \
	const RTTI name::rtti(#name, parent::rtti);
