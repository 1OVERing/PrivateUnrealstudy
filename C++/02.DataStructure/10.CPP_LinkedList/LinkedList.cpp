#include "LinkedList.h"
#include "Node.h"
LinkedList::LinkedList() : head(nullptr), count(0)
{
}
LinkedList::~LinkedList()
{
}

void LinkedList::AddToHead(int data)
{
	Node* newnode = new Node(data);

	if (nullptr == head)
		head = newnode;
	else
	{
		newnode->Next = head;
		head = newnode;
	}

	count++;
}
void LinkedList::Insert(int data)
{
	Node* NewNode = new Node(data);

	if (nullptr == head)
		head = NewNode;
	else
	{
		Node* current = head;
		Node* trail = nullptr;

		while (nullptr != current->Next)
		{
			if (current->Data >= data)
			{
				break;
			}
			trail = current;
			current = current->Next;
		}
		
		if (current == head)
		{
			current->Next = NewNode;
			//head = NewNode;
		}
		else
		{
			NewNode->Next = current;
			trail->Next = NewNode;
		}
	}

	count++;
}
void LinkedList::DeletData(int data)
{
	if (nullptr == head)
	{
		std::cout << "리스트가 비어있습니다.";
		return;
	}

	Node* current = head;
	Node* trail = nullptr;

	while (nullptr != current)
	{
		if (current->Data == data)
		{
			break;
		}
		else 
		{
			trail = current;
			current = current->Next;
		}
	}
	if (nullptr == current)
	{
		std::cout << "값 : " << data << " 를 찾지 못했습니다." << std::endl;
		return;
	}
	if (head == current)
	{
		head = head->Next;
	}
	else
	{
		trail->Next = current->Next;
	}
	
	delete current;
	count--;
}

void LinkedList::Print()
{
	Node* current = head;
	for (;nullptr != current;)
	{
		std::cout << current->Data << " ";
		current = current->Next;
	}
	std::cout << std::endl;
}