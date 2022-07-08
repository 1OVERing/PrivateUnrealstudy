#pragma once
#include <iostream>

template<typename T>
class TNode
{
	template<typename T>
	friend class TLinkedList;	// ���� ���� (forward declaration).

public:
	Node():data(), next(nullptr), previous(nullptr)
	{}
	~Node()
	{}
private:
	T data;
	TNode<T>* next;
	TNode<T>* previous;
};

template<typename T>
class TLinkedList
{
public:
	TLinkedList()
		:first(new TNode<T>()), last(new TNode<T>()), count(0)
	{
		first->next = last;
		last->previous = first;
	}

	TLinkedList(void(*ListEmptyErrorHandler)()) :TLinkedList<T>()
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
		// first�� ���� ������ ����.
		TNode<T>* current = first->next;

		// ������ ��ȸ.
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
	// �ε����� �˻�
	TNode<T>* operator[](size_t target)
	{
		TNode<T>* current = first->next;
		size_t index = 0;
		if (IsEmpty())
		{
			RaiseDataEmptyEvent();
			return nullptr;
		}

		while (current != last && index < target)
		{
			current = current->next;
			++index;
		}

		return current;
	}

	// ������ �˻�.
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

	// �� �տ� ������ �߰�.
	void PushFirst(const T& data)
	{
		// ��� ����.
		TNode<T>* newTNode = new TNode<T>();
		newTNode->data = data;

		// ������ ���� ó��.
		// first->next ���� newTNode.
		newTNode->next = first->next;
		first->next->previous = newTNode;

		// newTNode�� ���� first->next ���.
		first->next = newTNode;
		newTNode->previous = first;

		// ������ ���� ���� ó��.
		++count;
	}

	// �� �ڿ� ������ �߰�.
	void PushLast(const T& data)
	{
		// �� ��� ����.
		TNode<T>* newTNode = new TNode<T>();
		newTNode->data = data;

		// ������ ���� ó��.
		// last->previous ���� newTNode.
		TNode<T>* previous = last->previous;
		previous->next = newTNode;
		newTNode->previous = previous;

		// last ���� newTNode.
		newTNode->next = last;
		last->previous = newTNode;

		// ������ ���� �߰� ó��.
		++count;
	}

	// ����Ʈ�� ������� Ȯ��.
	// �Լ� �̸� �ڿ� const�� ���̸� �Լ� ����(����)���� ���� ������ �� �� ����.
	bool IsEmpty()const
	{
		return count == 0;
	}

	// ���� ����.
	// �� �ڿ��� ����.
	void PopLast()
	{
		// ����Ʈ�� ������� Ȯ��.
		// ������� ���� �̺�Ʈ �߻�.
		if (IsEmpty() == true)
		{
			RaiseDataEmptyEvent();
			return;
		}

		// ������ ���� ó��.
		TNode<T>* deleteTNode = last->previous;
		TNode<T>* previous = deleteTNode->previous;

		previous->next = last;
		last->previous = previous;

		// ������ ��� ����.
		delete deleteTNode;

		// ������ ���� ���� ó��.
		--count;
	}

	// �� �տ��� ����.
	void PopFirst()
	{
		// ����Ʈ�� ������� Ȯ��.
		// ������� ���� �̺�Ʈ �߻�.
		if (IsEmpty() == true)
		{
			RaiseDataEmptyEvent();
			return;
		}

		// ������ ���� ó��.
		TNode<T>* deleteTNode = first->next;
		TNode<T>* next = deleteTNode->next;

		first->next = next;
		next->previous = first;

		// ù��° ��� ����.
		delete deleteTNode;

		// ������ ���� ���� ó��.
		--count;
	}

	// Ư�� ��ġ�� ��� ����
	void Delete(const T& data)
	{
		// ����Ʈ�� ������� Ȯ��.
		// ������� ���� �̺�Ʈ �߻�.
		if (IsEmpty() == true)
		{
			RaiseDataEmptyEvent();
			return;
		}

		// ������ ��� �˻�.
		TNode<T>* deleteTNode = first->next;

		// ������ �˻�.
		while (deleteTNode != nullptr && deleteTNode != last)
		{
			// ���� ���� ����Ÿ�� ���� �����͸� ���� ��尡 �ִ��� ��.
			if (deleteTNode->data == data)
			{
				// ������ ���� ����.
				break;
			}

			// ���� ��� �˻�.
			deleteTNode = deleteTNode->next;
		}

		// �˻� ���������� ���� �̺�Ʈ �߻�.
		if (deleteTNode == nullptr || deleteTNode == last)
		{
			RaiseDataEmptyEvent();
			return;
		}

		// �˻� ���������� �ش� ��� ����.
		deleteTNode->previous->next = deleteTNode->next;
		deleteTNode->next->previous = deleteTNode->previous;

		delete deleteTNode;

		// ������ ���� ���� ó��.
		--count;
	}

	// ������ ��ȯ.
	// ù��° ������ ��ȯ.
	T First()const
	{
		// ����Ʈ�� ������� ���� �̺�Ʈ �߻�.
		if (IsEmpty() == true)
		{
			RaiseDataEmptyEvent();
			return -1;
		}

		// ù��° ����� ������ ��ȯ.
		return first->next->data;
	}

	// ������ ������ ��ȯ.
	T Last()const
	{
		// ����Ʈ�� ������� ���� �̺�Ʈ �߻�.
		if (IsEmpty() == true)
		{
			RaiseDataEmptyEvent();
			return -1;
		}

		// ������ ����� ������ ��ȯ.
		return last->previous->data;
	}

	size_t Count()const
	{
		return count;
	}

	// ������ ���.
	void Print()
	{
		// ���������� ��ȸ�ϸ鼭 ������ ���.
		TNode<T>* current = first->next;

		// ����Ʈ�� ����� ������ �׸� �� ���.
		cout << "����Ʈ �׸� ��: " << Count() << endl;
		// ������ ��ȸ�ϸ鼭 ������ �� ���.
		while (current != last)
		{
			cout << "������: " << current->data << " ";
			current = current->next;
		}

		// ��� ������ ��� �Ϸ��ϰ� Enter.
		cout << endl;
	}

private:
	// �����Ͱ� ����� �� �߻��ϴ� ���� �̺�Ʈ.
	void RaiseDataEmptyEvent()
	{
		// �Լ� �����Ͱ� �Ҵ�� ������, �ش� �Լ� ȣ��.
		if (ListEmptyErrorEvent != nullptr)
		{
			ListEmptyErrorEvent();
		}
	}

private:
	TNode<T>* first;
	TNode<T>* last;
	size_t count;

	// �Լ� ������.
	// �ݹ� ����.
	void (*ListEmptyErrorEvent)();
};


