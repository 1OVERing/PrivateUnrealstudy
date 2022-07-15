#pragma once
#include "A.h"
class C : public A
{
private: // Member Variable
	int cx;
	int cy;
public: // Member Function
	int Cx() const
	{
		return cx;
	}
	int Cy() const
	{
		return cy;
	}


public: // operator overLoading
	C& operator=(const C& p) = delete; // 복사 이동 연산자 선언    
	C& operator=(C&& p) noexcept = delete; // 이동 복사 연산자 선언   
public: // constructor / destructor
	C();
	~C();
	C(const C& other) = delete;
	C(const C&& other) noexcept = delete;
};