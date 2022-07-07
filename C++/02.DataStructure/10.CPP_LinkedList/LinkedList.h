#pragma once

class Node;
class LinkedList
{
private:
	Node* head;
	size_t count;

public:
	void AddToHead(int data);
	void Insert(int data);
	void DeletData(int data);
	void Print();
	size_t Count() const
	{return count;}



public:
	LinkedList();
	~LinkedList();
};