#pragma once
class A
{
private: // Member Variable
	int ax;
	int ay;
public: // Member Function
	int Ax() const
	{return ax;}
	int Ay() const
	{return ax;}

public: // operator overLoading
	A& operator=(const A& p) = delete; // 복사 이동 연산자 선언    
	A& operator=(A&& p) noexcept = delete; // 이동 복사 연산자 선언   
public: // constructor / destructor
	A();
	~A();
	A(const A& other) = delete;
	A(const A&& other) noexcept = delete;
};