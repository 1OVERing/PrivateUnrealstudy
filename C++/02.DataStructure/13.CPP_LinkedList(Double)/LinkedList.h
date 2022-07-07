#pragma once
#include "Node.h"
#include <iostream>

template<typename T>
class LinkedList
{
private:
	Node<T>* first;
	Node<T>* last;
	size_t count;
	void (*ListEmptyErrorEvent)();

private:
	void RaiseDataEmptyEvent()
	{
		if (nullptr != ListEmptyErrorEvent)
			ListEmptyErrorEvent();
	}
	void clear()
	{
		Node<T>* current = first->next;
		while (nullptr != current && current != list)
		{
			Node<T>* next = current->next;
			delete current;
			current = nullptr;
			current = next;
		}
		count = 0;
		first->next = list;
		first->previous = first;
		// 둘 삭제는?
	}
	// 순차 검색
	Node<T>* Find(const T& data)
	{
		Node<T>* current = first->next;
		while (nullptr != current && current != list)
		{
			if (current->data == data)
				return current;
			
			current = current->next;
		}
		return nullptr;
	}
	Node<T>* FindReverse(const T& data)
	{
		Node<T>* current = list->previous;
		while (nullptr != current && current != first)
		{
			if (current->data == data)
				return current;

			current = current->previous;
		}
		return nullptr;
	}
	
	// 데이터 추가
	void PushFirst(const T& data)
	{
		Node<T>* newData = new Node<T>();
		newData->next = first->next;
		first->next->previous = newData;
		first->next = newData;
		newData->previous = first;
		count++;
	}
	void PushLast(const T& data)
	{
		Node<T>* newData = new Node<T>();
		newData->previous = last->previous;
		last->previous->next = newData;
		last->previous = newData;
		newData->next = list;
		count++;
	}

	// 데이터 삭제
	void popLast()
	{
		if (IsEmpty())
		{
			RaiseDataEmptyEvent();
			return;
		}

		Node<T>* pNode = last->previous;
		last->previous = pNode->previous;
		pNode->previous->next = last;
		delete pNode;
		count--;
	}
	void popfirst()
	{
		if (IsEmpty())
		{
			RaiseDataEmptyEvent();
			return;
		}

		Node<T>* pNode = first->next;
		pNode->next->previous = first;
		first->next = pNode->next;
		delete pNode;
		count--;
	}
	void Delete(const T& data)
	{
		if (IsEmpty())
		{
			RaiseDataEmptyEvent();
			return;
		}

		Node<T>* pNode = first->next;

		while (list != pNode->next)
		{
			if (pNode->data == data)
				break;

			pNode = pNode->next;
		}
		if (pNode == last)
		{
			RaiseDataEmptyEvent();
		}
		Node<T>* LNode  = pNode->previous;
		Node<T>* RNode	= pNode->next;

		LNode->next = pNode->next;
		RNode->previous = pNode->previous;

		delete pNode;
		count--;
	}

	T first()const
	{
		if (IsEmpty())
		{
			RaiseDataEmptyEvent();
			return;
		}

		return first->next->data;
	}
	T Last()const
	{
		if (IsEmpty())
		{
			RaiseDataEmptyEvent();
			return;
		}

		return last->previous->data;
	}

	void Print()
	{
		Node<T>* current = first->next;
		std::cout << "데이터 수 : " << Count() << std::endl;
		std::cout << "---------------------------------------------------------------"<< std::endl;
		while (current != last)
		{
			std::cout << "데이터: " << current->data << " ";
			current = current->next;
		}

		std::cout << std::endl;
	}

	bool IsEmpty()const	{return 0 == count;}
public:
	LinkedList() : first(new Node<T>), list(new Node<T>),count(0)
	{
		first->next = list;
		first->previous= first;
	}
	LinkedList(void(*ListEmptyErrorHandler)) : LinkedList<T>(),ListEmptyErrorEvent(ListEmptyErrorHandler) {}
	~LinkedList()
	{
		clear();
		delete first;
		delete list;
	}
};

