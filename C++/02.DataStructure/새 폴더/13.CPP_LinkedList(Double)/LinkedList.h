#pragma once
#include "Node.h"
#include <iostream>

template<typename T>
class LinkedList
{
private:
	TNode<T>* first;
	TNode<T>* last;
	size_t count;
	void (*ListEmptyErrorEvent)();
	void RaiseDataEmptyEvent()
	{
		if (nullptr != ListEmptyErrorEvent)
			ListEmptyErrorEvent();
	}

public:
	void clear()
	{
		TNode<T>* current = first->next;
		while (nullptr != current && current != last)
		{
			TNode<T>* next = current->next;
			delete current;
			current = nullptr;
			current = next;
		}
		count = 0;
		first->next = last;
		first->previous = first;
		// 둘 삭제는?
	}
	// 순차 검색
	TNode<T>* Find(const T& data)
	{
		TNode<T>* current = first->next;
		while (nullptr != current && current != last)
		{
			if (current->data == data)
				return current;
			
			current = current->next;
		}
		return nullptr;
	}
	TNode<T>* FindReverse(const T& data)
	{
		TNode<T>* current = last->previous;
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
		TNode<T>* newData = new TNode<T>();
		newData->next = first->next;
		first->next->previous = newData;
		first->next = newData;
		newData->previous = first;
		count++;
	}
	void PushLast(const T& data)
	{
		TNode<T>* newData = new TNode<T>();
		newData->previous = last->previous;
		last->previous->next = newData;
		last->previous = newData;
		newData->next = last;
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

		TNode<T>* pNode = last->previous;
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

		TNode<T>* pNode = first->next;
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

		TNode<T>* pNode = first->next;

		while (last != pNode->next)
		{
			if (pNode->data == data)
				break;

			pNode = pNode->next;
		}
		if (pNode == last)
		{
			RaiseDataEmptyEvent();
		}
		TNode<T>* LNode  = pNode->previous;
		TNode<T>* RNode	= pNode->next;

		LNode->next = pNode->next;
		RNode->previous = pNode->previous;

		delete pNode;
		count--;
	}

	T First()const
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
		TNode<T>* current = first->next;
		std::cout << "데이터 수 : " << Count() << std::endl;
		std::cout << "---------------------------------------------------------------\n";
		while (current != last)
		{
			std::cout << "데이터: " << current->data << " ";
			current = current->next;
		}

		std::cout << std::endl;
	}

	bool IsEmpty()const	{return 0 == count;}
public:
	LinkedList() : first(new TNode<T>()), last(new TNode<T>()),count(0)
	{
		first->next = last;
		first->previous= first;
	}
	LinkedList(void(*ListEmptyErrorHandler)) : LinkedList<T>()
	{
		this->ListEmptyErrorEvent = ListEmptyErrorHandler;
	}
	~LinkedList()
	{
		clear();
		delete first;
		delete last;
	}
};

