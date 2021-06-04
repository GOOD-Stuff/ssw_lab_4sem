#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <iostream>


template <class T>
class DoubleList {
private:
	struct node
	{
		T value;

		node* prev{ nullptr };
		node* next{ nullptr };

		node(T value)
		{
			this->value = value;
		}
	};

	node* head;
	node* tail;

	int size{ 0 };

	void quick_sort_arr(T* arr, int sz) { // hoare sort
		int i = 0;
		int j = sz - 1;
		T middle = arr[sz / 2];

		do {
			while (arr[i] < middle) {
				i++;
			}

			while (arr[j] > middle) {
				j--;
			}

			if (i <= j) {
				std::swap(arr[i++], arr[j--]);
			}
		} while (i <= j);

		if (j > 0) {
			quick_sort_arr(arr, j + 1);
		}

		if (i < sz) {
			quick_sort_arr(arr + i, sz - i);
		}
	}


public:
	class iterator;
	friend class iterator;

	DoubleList() {
		head = nullptr;
		tail = nullptr;
	}

	~DoubleList()
	{
		clear();
	}

	void push_front(T value)
	{
		node* new_node = new node(value);

		if (head != nullptr)
		{
			head->prev = new_node;
		}

		new_node->next = head;
		head = new_node;

		if (size == 0)
		{
			tail = head;
		}

		size++;
	}

	void push_back(T value)
	{
		if (size == 0)
		{
			return push_front(value);
		}

		node* new_node = new node(value);
		tail->next = new_node;
		new_node->prev = tail;

		tail = new_node;
		size++;
	}

	void pop_front()
	{
		if (size == 0)
		{
			throw std::runtime_error("List is empty!");
		}

		node* old_head = head;
		head = head->next;

		if (head != nullptr)
		{
			head->prev = nullptr;
		}

		delete old_head;
		size--;
	}

	void pop_back()
	{
		if (size == 0)
		{
			throw std::runtime_error("List is empty!");
		}

		if (size == 1)
		{
			return pop_front();
		}

		node* old_tail = tail;
		tail = tail->prev;
		tail->next = nullptr;

		delete old_tail;
		size--;
	}

	void insert(iterator it, T value)
	{
		if (it == begin())
		{
			return push_front(value);
		}
		else if (it == end())
		{
			return push_back(value);
		}

		node* new_node = new node(value);
		node* current_node = it.node_ptr;
		node* left_node = current_node->prev;

		left_node->next = new_node;
		new_node->prev = left_node;

		new_node->next = current_node;
		current_node->prev = new_node;

		size++;
	}

	void erase(iterator it)
	{
		if (size == 0)
		{
			throw std::runtime_error("List is empty!");
		}

		if (it == begin())
		{
			return pop_front();
		}

		if (it == end() - 1)
		{
			return pop_back();
		}

		node* deleted_node = it.node_ptr;
		node* left_node = deleted_node->prev;
		node* right_node = deleted_node->next;

		left_node->next = right_node;
		right_node->prev = left_node;

		delete deleted_node;
		size--;
	}

	iterator begin() const
	{
		return iterator(head, const_cast<DoubleList<T>&>(*this));
	}

	iterator end() const
	{
		return iterator(nullptr, const_cast<DoubleList<T>&>(*this));
	}

	int count() const
	{
		return size;
	}


	void quick_sort() { // quick sort
		T* arr = new T[size];
		node* curr = head;
		for (int i = 0; i < size; i++) {
			arr[i] = curr->value;
			curr = curr->next;
		}

		quick_sort_arr(arr, size);

		int old_size = size;
		clear();

		for (int i = old_size - 1; i >= 0; i--) {
			push_front(arr[i]);
		}

		delete[] arr;
	}

	void divide(DoubleList<T>& obj1, DoubleList<T>& obj2, T num) { // dive list into two list, by divider
		if (this == &obj1 || this == &obj2) {
			throw std::runtime_error("You are using the same object!");
		}

		obj1.clear();
		obj2.clear();

		node* curr = head;
		for (int i = 0; i < size; i++) {
			if (curr->value > num) {
				obj1.push_back(curr->value);
			}
			else {
				obj2.push_front(curr->value);
			}
			curr = curr->next;
		}
	}


		void clear()
		{
			while (size != 0)
			{
				pop_front();
			}
		}

		DoubleList<T>& operator = (const DoubleList<T> & lst)
		{
			if (this == std::addressof(lst))
			{
				return *this;
			}

			clear();

			for (auto value : lst)
			{
				push_back(value);
			}
		}

		DoubleList<T>& operator = (DoubleList<T> && lst) noexcept
		{
			if (this == std::addressof(lst))
			{
				return *this;
			}

			clear();

			head = lst.head;
			tail = lst.tail;
			size = lst.size;

			lst.head = nullptr;
			lst.tail = nullptr;
			lst.size = 0;
		}

		// Comparison operators

		bool operator == (const DoubleList<T>& obj) const {
			if (this == &obj) {
				return true;
			}

			if (size != obj.size) {
				return false;
			}

			iterator it1 = begin();
			iterator it2 = obj.begin();

			while (it1 != end()) {
				it1++;
				it2++;
				if (*it1 != *it2) {
					return false;
				}
			}

			return true;
		}

		bool operator != (const DoubleList<T>& obj)  const {
			return !(*this == obj);
		}

		bool operator < (const DoubleList<T>& obj) const {
			if (this == &obj) {
				return false;
			}


			for (iterator it1 = begin(), it2 = obj.begin(); it1 != end(); ++it1, ++it2)
			{
				if (*it1 != *it2)
				{
					return *it1 < *it2;
				}
			}


			return size < obj.size;
		}

		bool operator <= (const DoubleList<T>& obj) const {
			return *this < obj || *this == obj;
		}

		bool operator > (const DoubleList<T>& obj) const {
			return !(*this < obj) && *this != obj;
		}

		bool operator >= (const DoubleList<T>& obj) const {
			return *this > obj || *this == obj;
		}

		class iterator
		{
		private:
			friend class DoubleList<T>;

			DoubleList<T>& lst;
			node* node_ptr{ nullptr };

			iterator(node* p_node, DoubleList<T>& list_ref) : lst(list_ref), node_ptr(p_node) {}

		public:
			iterator() = default;

			iterator& operator ++ ()
			{
				if (node_ptr == nullptr)
				{
					throw std::runtime_error("Current node is empty!");
				}

				node_ptr = node_ptr->next;
				return *this;
			}

			iterator operator ++ (int)
			{
				if (node_ptr == nullptr)
				{
					throw std::runtime_error("Current node is empty!");
				}

				node* old_ptr = node_ptr;
				node_ptr = node_ptr->next;
				return iterator(old_ptr, lst);
			}

			iterator& operator -- ()
			{
				if (node_ptr == nullptr)
				{
					node_ptr = lst.tail;
					return *this;
				}

				node_ptr = node_ptr->prev;
				return *this;
			}

			iterator operator -- (int)
			{
				if (node_ptr == nullptr)
				{
					return iterator(lst.tail, lst);
				}

				node* old_ptr = node_ptr;
				node_ptr = node_ptr->prev;
				return iterator(old_ptr, lst);
			}

			iterator operator + (int offset)
			{
				iterator it(node_ptr, lst);

				for (int i = 0; i < offset; i++)
				{
					++it;
				}

				return it;
			}

			iterator operator - (int offset)
			{
				iterator it(node_ptr, lst);

				for (int i = 0; i < offset; i++)
				{
					--it;
				}

				return it;
			}

			iterator& operator = (const iterator& it)
			{
				lst = it.lst;
				node_ptr = it.node_ptr;

				return *this;
			}

			T& operator * ()
			{
				if (node_ptr == nullptr)
				{
					throw std::runtime_error("Current node is empty!");
				}

				return node_ptr->value;
			}

			bool operator == (const iterator& it) const
			{
				return node_ptr == it.node_ptr;
			}

			bool operator != (const iterator& it) const
			{
				return node_ptr != it.node_ptr;
			}
		};

		friend std::ostream& operator << (std::ostream & out, const DoubleList<T> & lst)
		{
			for (auto& value : lst)
			{
				out << value << " ";
			}

			return out;
		}
};

#endif