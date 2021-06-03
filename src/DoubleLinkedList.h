#ifndef CLASS_DOUBLE_LINKED_LIST_H
#define CLASS_DOUBLE_LINKED_LIST_H

#include <initializer_list>
#include <ostream>

template <class T>
class DoubleLinkedList
{
private:
	struct Item
	{
		T data;
		Item* pNext{ nullptr };
		Item* pPrev{ nullptr };
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
	DoubleLinkedList() {}

	DoubleLinkedList(const std::initializer_list<T>& list){
		for (auto& element : list)
		{
			push_back(element);
		}
	}

	~DoubleLinkedList(){
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

		if (pStart)
		{
			pStart->pPrev = newItem;
		}

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
		newItem->pPrev = pFinish;

		pFinish->pNext = newItem;
		pFinish = newItem;

		size++;
	}

	void pop_front(){
		Item* oldStart = pStart;
		pStart = oldStart->pNext;

		if (pStart != nullptr)
		{
			pStart->pPrev = nullptr;
		}

		delete oldStart;
		size--;
	}

	void pop_back(){
		if (size == 1)
		{
			pop_front();
			return;
		}

		Item* oldFinish = pFinish;

		pFinish = pFinish->pPrev;
		pFinish->pNext = nullptr;

		delete oldFinish;
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
		Item* leftItem = it.pItem->pPrev;

		newItem->data = value;
		leftItem->pNext = newItem;
		newItem->pPrev = leftItem;
		newItem->pNext = it.pItem;
		it.pItem->pPrev = newItem;

		size++;
	}

	void erase(int index){
		iterator it = begin() + index;

		if (it == begin())
		{
			pop_front();
			return;
		}
		else if (it == end() - 1)
		{
			pop_back();
			return;
		}

		Item* leftItem = it.pItem->pPrev;
		Item* rightItem = it.pItem->pNext;

		leftItem->pNext = rightItem;
		rightItem->pPrev = leftItem;

		delete it.pItem;
		size--;
	}

	void merge_sort(){
		pStart = sort(pStart);
        

		Item* tmp_1 = pStart;
		Item* tmp_2 = pStart->pNext;
		for (int i = 0; i < size; i++)
		{
			if (i == 0)
			{
				tmp_1->pPrev = nullptr;
			}
			else
			{
				tmp_2->pPrev = tmp_1;
				tmp_1 = tmp_1->pNext;
				tmp_2 = tmp_2->pNext;
			}
		}

		iterator it = begin() + (size - 1);
		pFinish = it.pItem;
		pFinish->pNext = nullptr;
		return;
	}

	class iterator{
	private:
		friend class DoubleLinkedList<T>;

		Item* pItem{ nullptr };
		DoubleLinkedList<T>* pList{ nullptr };

		iterator(Item* ptrItem, DoubleLinkedList<T>* ptrList){
			pItem = ptrItem;
			pList = ptrList;
		}

	public:
		iterator() {}

		iterator& operator++(){
			pItem = pItem->pNext;
			return *this;
		}

		iterator operator++(int){
			Item* oldItem = pItem;
			pItem = pItem->pNext;
			return oldItem;
		}

		iterator operator+(int shift){
			iterator it(pItem, pList);

			for (int i = 0; i < shift; i++)
			{
				++it;
			}

			return it;
		}

		iterator& operator--(){
			if (pItem == nullptr)
			{
				pItem = pList->pFinish;
				return *this;
			}

			pItem = pItem->pPrev;
			return *this;
		}

		iterator operator--(int){
			if (pItem == nullptr)
			{
				return iterator(pList->pFinish, pList);
			}

			Item* oldItem = pItem;
			pItem = pItem->pPrev;
			return oldItem;
		}

		iterator operator-(int shift){
			iterator it(pItem, pList);

			for (int i = 0; i < shift; i++)
			{
				--it;
			}

			return it;
		}

		T& operator*(){
			return pItem->data;
		}

		bool operator==(const iterator& it) const{
			return pItem == it.pItem;
		}

		bool operator!=(const iterator& it) const{
			return pItem != it.pItem;
		}
	};

	iterator begin() const{
		return iterator(pStart, const_cast<DoubleLinkedList<T>*>(this));
	}

	iterator end() const{
		return iterator(nullptr, const_cast<DoubleLinkedList<T>*>(this));
	}

	bool operator==(const DoubleLinkedList<T>& list) const{
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

	bool operator!=(const DoubleLinkedList<T>& list) const{
		return !(*this == list);
	}

	bool operator<(const DoubleLinkedList<T>& list) const{
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

	bool operator>(const DoubleLinkedList<T>& list) const{
		return !(*this < list) && (*this != list);
	}

	bool operator<=(const DoubleLinkedList<T>& list) const{
		return (*this < list) || (*this == list);
	}

	bool operator>=(const DoubleLinkedList<T>& list) const{
		return (*this > list) || (*this == list);
	}

	void merge_sort(const DoubleLinkedList<T>& list){

	}
};

template <typename T>
std::ostream& operator << (std::ostream& stream, const DoubleLinkedList<T>& list){
	for (auto& element : list)
		stream << element << "\n";

	return stream;
}

#endif