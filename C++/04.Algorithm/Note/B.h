#pragma once
#include "A.h"

class B : public A
{
private: // Member Variable
	int bx;
	int by;
public: // Member Function
	int Bx() const
	{return bx;}
	int By() const
	{return by;}


public: // operator overLoading
	B& operator=(const B& p) = delete; // 복사 이동 연산자 선언    
	B& operator=(B&& p) noexcept = delete; // 이동 복사 연산자 선언   
public: // constructor / destructor
	B();
	~B();
	B(const B& other) = delete;
	B(const B&& other) noexcept = delete;
};