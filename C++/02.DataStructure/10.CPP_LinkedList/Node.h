#pragma once
#include <iostream>

class Node
{
	friend class LinkedList;
private:
	int Data;
	Node* Next;



private:
	friend std::ostream& operator<< (std::ostream & os, const Node & node);
private:
	Node();
	Node(int data);
	~Node();
};