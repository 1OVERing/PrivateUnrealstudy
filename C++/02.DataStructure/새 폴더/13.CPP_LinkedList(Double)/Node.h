#pragma once

template<typename T>
class TNode
{
private:
	template<T>
	friend class LinkedList;
	// forward declaration / 전방선언
private:
	T data;
	TNode<T>* next;
	TNode<T>* previous;


public:
	TNode() : data(),next(nullptr), previous(nullptr)
	{};
	~TNode()
	{}
};

