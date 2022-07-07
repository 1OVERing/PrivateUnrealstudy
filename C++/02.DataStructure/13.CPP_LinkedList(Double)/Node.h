#pragma once

template<typename T>
class Node
{
private:
	template<T>
	friend class LinkedList;
	// forward declaration / 전방선언
private:
	T data;
	Node<T>* next;
	Node<T>* previous;


public:
	Node() : data(),next(nullptr),previous(nullptr)
	~Node(){}
};

