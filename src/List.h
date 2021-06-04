#ifndef LIST_H
#define LIST_H

#include <iostream>
template <class T>
class List {
private:
	struct Node { //node structure
		T value; // node values
		Node* next; // pointer to next node

		Node(T v) { //node constructor
			value = v;

			next = nullptr;
		}
	};

	Node* head; // start node
	int size; // size of list

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


	class iterator { // iterator
	private:
		friend class List<T>;
		Node* node;

	public:
		iterator(Node* n) {
			node = n;
		}

		iterator();

		iterator& operator++() {
			if (node == nullptr) {
				throw std::runtime_error("Node is empty!");
			}
			node = node->next;
			return *this;
		}

		iterator operator++(int) {
			if (node == nullptr) {
				throw std::runtime_error("Node is empty!");
			}

			Node* old_node = node;
			node = node->next;
			return iterator(old_node);
		}

		T& operator*() {
			if (node == nullptr) {
				throw std::runtime_error("Node is empty!");
			}
			return node->value;
		}

		bool operator == (const iterator& it){
			return node == it.node;
		}

		bool operator != (const iterator& it){
			return !(*this == it);
		}
	};

	List() { // constructor

		head = nullptr;
		size = 0;
	}

	~List() { // destructor
		clear();
	}

	void push_front(T elem) { // add element  to the begining

		Node* new_node = new Node(elem);
		Node* old_node = head;

		head = new_node;
		head->next = old_node;
		size++;
	}
	 
	void push_back(T elem) { // add element  to the end

		if (size != 0) {
			Node* new_node = new Node(elem);
			Node* curr = head;
			for (int i = 0; i < size - 1; i++) {
				curr = curr->next;
			}
			curr->next = new_node;
			size++;
		}

		else {
			push_front(elem);
		}
	}

	void pop_front() { // delete  elemtn from the begining

		if (size == 0) {
			throw std::runtime_error("List is empty!");
		}

		T elem = head->value;
		Node* old_node = head;
		head = head->next;

		size--;

		delete old_node;
	}

	void pop_back() { // delete  elemtn from the end

		if (size == 0) {
			throw std::runtime_error("List is empty!");
		}

		if (size != 1) {
			Node* curr = head;
			for (int i = 0; i < size - 1; i++) {
				curr = curr->next;
			}
			delete curr;
			size--;
		}
		else
			pop_front();
	}

	void insert(T elem, iterator it) { // insert after a specific node

		Node* new_node = new Node(elem);
		Node* curr = it.node;

		Node* next_node = curr->next;
		curr->next = new_node;
		new_node->next = next_node;
		size++;
	}
	void erase(iterator it) { // delete specific node
		if (size == 0) {
			throw std::runtime_error("List is empty!");
		}


		Node* curr_node = it.node;
		Node* del_node = curr_node->next;
		Node* next_node = del_node->next;

		curr_node->next = next_node;

		delete del_node;
		size--;
	}

	iterator begin()  const { // iterator to begin
		return iterator(head);
	}

	iterator end() const { // iterator to end
		return iterator(nullptr);
	}

	int count()  const { // size of list
		return size;
	}

	void clear() { // delete all node
		while (size != 0) {
			pop_front();
		}
	}

	void quick_sort() { // quick sort
		T* arr = new T[size];
		Node* curr = head;
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

	void divide(List<T>& obj1, List<T>& obj2, T num) { // dive list into two list, by divider
		if (this == &obj1 || this == &obj2) {
			throw std::runtime_error("You are using the same object!");
		}

		obj1.clear();
		obj2.clear();

		Node* curr = head;
		for (int i = 0; i < size; i++) {
			if (curr->value > num) {
				obj1.push_front(curr->value);
			}
			else {
				obj2.push_front(curr->value);
			}
			curr = curr->next;
		}

	}

	// Comparison operators

	bool operator == (const List<T>& obj) const  {
		if (this == &obj) {
			return true;
		}

		if (size != obj.size) {
			return false;
		}

		iterator it1= begin();
		iterator it2  = obj.begin();

		while (it1 != end()) {
			it1++;
			it2++;
			if (*it1 != *it2) {
				return false;
			}
		}

		return true;
	}

	bool operator != (const List<T>& obj)  const {
		return !(*this == obj);
	}

	bool operator < (const List<T>& obj) const {
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

	bool operator <= (const List<T>& obj) const {
		return *this < obj || *this == obj;
	}

	bool operator > (const List<T>& obj) const {
		return !(*this < obj) && *this != obj;
	}

	bool operator >= (const List<T>& obj) const {
		return *this > obj || *this == obj;
	}

	friend std::ostream& operator<<(std::ostream& o, const List<T>& list) {
		Node* new_node = list.head;
		for (int i = 0; i < list.size; i++) {
			o << new_node->value << " ";
			new_node = new_node->next;
		}
		o << "\n";
		return o;
	}
};
#endif

