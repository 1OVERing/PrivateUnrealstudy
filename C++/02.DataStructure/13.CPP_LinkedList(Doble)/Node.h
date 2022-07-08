#pragma once

template<typename T>
class Node
{
	template<typename T>
	friend class LinkedList;	// ���� ���� (forward declaration).

public:
	Node()
		:data(), next(nullptr), previous(nullptr)
	{

	}
private:
	T data;
	Node<T>* next;
	Node<T>* previous;
};