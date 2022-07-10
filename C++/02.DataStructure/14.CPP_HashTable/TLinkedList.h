#pragma once

#include <iostream>

#pragma once

template<typename T>
class TNode
{
	template<typename T>
	friend class TLinkedList;

public:
	TNode()
		: data(), next(nullptr), previous(nullptr)
	{
	}

public:
	T data;						// 데이터 필드.
	TNode<T>* next;				// 다음 노드 가리킴.
	TNode<T>* previous;			// 이전 노드 가리킴.
};

template<typename T>
class TLinkedList
{
public:
	TLinkedList()
		: first(new TNode<T>()), last(new TNode<T>()), count(0)
	{
		first->next = last;
		last->previous = first;
	}
	TLinkedList(void (*ListEmptyErrorHandler)()): TLinkedList<T>()
	{
		this->ListEmptyErrorEvent = ListEmptyErrorHandler;
	}
	~TLinkedList()
	{
		Clear();

		delete first;
		delete last;
	}

	void Clear()
	{
		// first의 다음 노드부터 시작.
		TNode<T>* current = first->next;

		// 루프로 순회.
		while (current != nullptr && current != last)
		{
			TNode<T>* next = current->next;
			delete current;
			current = next;
		}

		count = 0;
		first->next = last;
		last->previous = first;
	}
	TNode<T>* Find(const T& data)
	{
		TNode<T>* current = first->next;

		while (current != nullptr && current != last)
		{
			if (current->data == data)
			{
				return current;
			}

			current = current->next;
		}

		return nullptr;
	}
	TNode<T>* FindReverse(const T& data)
	{
		TNode<T>* current = last->previous;

		while (current != nullptr && current != first)
		{
			if (current->data == data)
			{
				return current;
			}

			current = current->previous;
		}

		return nullptr;
	}
	void PushFirst(const T& data)
	{
		// 노드 생성.
		TNode<T>* newTNode = new TNode<T>();
		newTNode->data = data;

		// 포인터 연산 처리.
		// first->next 노드와 newTNode.
		TNode<T>* next = first->next;
		//newTNode->next = first->next;
		newTNode->next = next;
		//first->next->previous = newTNode;
		next->previous = newTNode;

		// newTNode와 원래 first 노드.
		first->next = newTNode;
		newTNode->previous = first;

		// 데이터 개수 증가 처리.
		++count;
	}
	void PushLast(const T& data)
	{
		// 새 노드 생성.
		TNode<T>* newTNode = new TNode<T>();
		newTNode->data = data;

		// 포인터 연산 처리.
		// last->previous노드와 newTNode
		TNode<T>* previous = last->previous;
		previous->next = newTNode;
		newTNode->previous = previous;

		// last 노드와 newTNode
		newTNode->next = last;
		last->previous = newTNode;

		// 데이터 개수 추가 처리.
		++count;
	}
	bool IsEmpty() const
	{
		return count == 0;
	}
	void PopLast()
	{
		// 리스트가 비었는지 확인.
		// 비었으면 오류 이벤트 발생.
		if (IsEmpty() == true)
		{
			RaiseDataEmptyEvent();
			return;
		}

		// 포인터 연산 처리.
		TNode<T>* deleteTNode = last->previous;
		TNode<T>* previous = deleteTNode->previous;

		previous->next = last;
		last->previous = previous;

		// 마지막 노드 삭제.
		delete deleteTNode;

		// 데이터 개수 감소 처리.
		--count;
	}
	void PopFirst()
	{
		// 리스트가 비었는지 확인.
		// 비었으면 오류 이벤트 발생.
		if (IsEmpty() == true)
		{
			RaiseDataEmptyEvent();
			return;
		}

		// 포인터 연산 처리.
		TNode<T>* deleteTNode = first->next;
		TNode<T>* next = deleteTNode->next;

		first->next = next;
		next->previous = first;

		// 첫번째 노드 삭제.
		delete deleteTNode;

		// 데이터 개수 감소 처리.
		--count;
	}
	void Delete(const T& data)
	{
		// 리스트가 비었는지 확인.
		// 비었으면 오류 이벤트 발생.
		if (IsEmpty() == true)
		{
			RaiseDataEmptyEvent();
			return;
		}

		// 삭제할 노드 검색.
		TNode<T>* deleteTNode = first->next;

		// 순방향 검색.
		while (deleteTNode != nullptr && deleteTNode != last)
		{
			// 전달 받은 데이터와 같은 데이터를 가진 노드가 있는지 비교.
			if (deleteTNode->data == data)
			{
				// 있으면 루프 종료.
				break;
			}

			// 다음 노드 검색.
			deleteTNode = deleteTNode->next;
		}

		// 검색 실패했으면 오류 이벤트 발생.
		if (deleteTNode == nullptr || deleteTNode == last)
		{
			RaiseDataEmptyEvent();
			return;
		}

		// 검색 성공했으면 해당 노드 삭제.
		deleteTNode->previous->next = deleteTNode->next;
		deleteTNode->next->previous = deleteTNode->previous;

		delete deleteTNode;

		// 데이터 개수 감소 처리.
		--count;
	}
	T First() const
	{
		// 리스트가 비었으면 오류 이벤트 발생.
		if (IsEmpty() == true)
		{
			RaiseDataEmptyEvent();
			return -1;
		}

		// 첫번째 노드의 데이터 반환.
		return first->next->data;
	}
	T Last() const
	{
		// 리스트가 비었으면 오류 이벤트 발생.
		if (IsEmpty() == true)
		{
			RaiseDataEmptyEvent();
			return -1;
		}

		// 마지막 노드의 데이터 반환.
		return last->previous->data;
	}
	size_t Count() const
	{
		return count;
	}
	void Print()
	{
		// 순방향으로 순회하면서 데이터 출력.
		TNode<T>* current = first->next;

		// 리스트에 저장된 데이터 항목 수 출력.
		std::cout << "리스트 항목 수: " << Count() << std::endl;
		// 루프로 순회하면서 데이터 값 출력.
		while (current != last)
		{
			std::cout << "데이터: " << current->data << " ";
			current = current->next;
		}

		// 모든 데이터 출력 완료하고 Enter.
		std::cout << std::endl;
	}

public:
	TNode<T>* operator[](size_t targetIndex)
	{
		TNode<T>* current = first->next;
		size_t index = 0;
		if (IsEmpty() == true)
		{
			RaiseDataEmptyEvent();
			return nullptr;
		}

		while (current != last && index < targetIndex)
		{
			current = current->next;
			++index;
		}

		return current;
	}
private:
	void RaiseDataEmptyEvent()
	{
		// 함수 포인터가 할당돼 있으면, 해당 함수 호출.
		if (ListEmptyErrorEvent != nullptr)
		{
			ListEmptyErrorEvent();
		}
	}

	TNode<T>* first;
	TNode<T>* last;
	size_t count;

	void (*ListEmptyErrorEvent)();
};