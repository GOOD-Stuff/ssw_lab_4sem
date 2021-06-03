#ifndef CLASS_LINKED_LIST_H
#define CLASS_LINKED_LIST_H

#include <initializer_list>
#include <ostream>

template <class T>
class LinkedList
{
private:
	struct Item
	{
		T data;
		Item* pNext{ nullptr };
	};

	Item* pStart{ nullptr };
	Item* pFinish{ nullptr };

	int size{ 0 };

	Item* merge(Item* a, Item* b){
		if (!a) return b;
		if (!b) return a;

		Item* c = 0;
		if (a->data < b->data)
		{
			c = a;
			c->pNext = merge(a->pNext, b);
		}
		else
		{
			c = b;
			c->pNext = merge(a, b->pNext);
		}
		return c;
	}

	Item* sort(Item* pStart){
		if (pStart == nullptr || pStart->pNext == nullptr) return pStart;
		Item* a = pStart, *b = pStart->pNext;
		while ((b != nullptr) && (b->pNext != nullptr))
		{
			pStart = pStart->pNext;
			b = b->pNext->pNext;
		}
		b = pStart->pNext; pStart->pNext = nullptr;
		return merge(sort(a), sort(b));
	}

public:
	LinkedList() {}

	LinkedList(const std::initializer_list<T>& list){
		for (auto& element : list)
		{
			push_back(element);
		}
	}

	~LinkedList(){
		while (size != 0)
		{
			pop_front();
		}
	}

	int count() { return size; }

	void push_front(T value){
		Item* newItem = new Item;

		newItem->data = value;
		newItem->pNext = pStart;

		pStart = newItem;

		if (++size == 1)
		{
			pFinish = pStart;
		}
	}

	void push_back(T value){
		if (size == 0)
		{
			push_front(value);
			return;
		}

		Item* newItem = new Item;

		newItem->data = value;

		pFinish->pNext = newItem;
		pFinish = newItem;

		size++;
	}

	void pop_front(){
		Item* oldStart = pStart;
		pStart = pStart->pNext;

		delete oldStart;
		size--;
	}

	void pop_back(){
		if (size == 1)
		{
			pop_front();
			return;
		}

		Item* previous = pStart;

		for (int i = 0; i < size - 2; i++)
		{
			previous = previous->pNext;
		}

		Item* toDelete = previous->pNext;
		previous->pNext = toDelete->pNext;

		pFinish = previous;

		delete toDelete;
		size--;
	}

	void insert(int index, T value){
		iterator it = begin() + index;

		if (it == begin())
		{
			push_front(value);
			return;
		}
		else if (it == end())
		{
			push_back(value);
			return;
		}

		Item* newItem = new Item;
		newItem->data = value;
		Item* previous = pStart;

		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}

		previous->pNext = newItem;

		size++;
	}

	void erase(int index){

		if (index == 0)
		{
			pop_front();
			return;
		}
		else if (index == size - 1)
		{
			pop_back();
			return;
		}

		Item* leftItem = pStart;

		for (int i = 0; i < index - 1; i++)
		{
			leftItem = leftItem->pNext;
		}

		Item* rightItem = leftItem->pNext;

		leftItem->pNext = rightItem->pNext;

		delete rightItem;
		size--;
	}

	void merge_sort(){
		pStart = sort(pStart);
		iterator it = begin() + (size - 1);
		pFinish = it.pItem;
		return;
	}

	class iterator
	{
	private:
		friend class LinkedList<T>;

		Item* pItem{ nullptr };
		LinkedList<T>* pList{ nullptr };

		iterator(Item* ptrItem, LinkedList<T>* ptrList)
		{
			pItem = ptrItem;
			pList = ptrList;
		}

	public:
		iterator() {}

		iterator& operator++()
		{
			pItem = pItem->pNext;
			return *this;
		}

		iterator operator++(int)
		{
			Item* oldItem = pItem;
			pItem = pItem->pNext;
			return oldItem;
		}

		iterator operator+(int shift)
		{
			iterator it(pItem, pList);

			for (int i = 0; i < shift; i++)
			{
				++it;
			}

			return it;
		}

		T& operator*()
		{
			return pItem->data;
		}

		bool operator==(const iterator& it) const
		{
			return pItem == it.pItem;
		}

		bool operator!=(const iterator& it) const
		{
			return pItem != it.pItem;
		}
	};

	iterator begin() const{
		return iterator(pStart, const_cast<LinkedList<T>*>(this));
	}

	iterator end() const{
		return iterator(nullptr, const_cast<LinkedList<T>*>(this));
	}

	bool operator==(const LinkedList<T>& list) const{
		if (this == &list)
		{
			return true;
		}

		if (size == list.size)
		{
			for (iterator it_1 = begin(), it_2 = list.begin(); it_1 != end(); ++it_1, ++it_2)
			{
				if (*it_1 != *it_2)
				{
					return false;
				}
			}

			return true;
		}

		return false;
	}

	bool operator!=(const LinkedList<T>& list) const{
		return !(*this == list);
	}

	bool operator<(const LinkedList<T>& list) const{
		if (this == &list)
		{
			return false;
		}

		for (iterator it_1 = begin(), it_2 = list.begin(); it_1 != end() && it_2 != list.end(); ++it_1, ++it_2)
		{
			if (*it_1 != *it_2)
			{
				return *it_1 < *it_2;
			}
		}

		return size < list.size;
	}

	bool operator>(const LinkedList<T>& list) const{
		return !(*this < list) && (*this != list);
	}

	bool operator<=(const LinkedList<T>& list) const{
		return (*this < list) || (*this == list);
	}

	bool operator>=(const LinkedList<T>& list) const{
		return (*this > list) || (*this == list);
	}

	
};

template <typename T>
std::ostream& operator << (std::ostream& stream, const LinkedList<T>& list){
	for (auto& element : list)
		stream << element << "\n";

	return stream;
}

#endif
