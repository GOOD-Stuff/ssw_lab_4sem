#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>
template <class T>
class Buffer {
private:
	struct Node { //node structure
		T value; // node values
		Node* next; // pointer to next node
		Node* past; // pointer to past node

		Node(T v) { //node constructor
			value = v;

			next = nullptr;
			past = nullptr;
		}
	};

	Node* head; // start node
	Node* last; // end node

	int size; // real size
	int max_size; // max size

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
		friend class Buffer<T>;
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

		bool operator == (const iterator& it) {
			return node == it.node;
		}

		bool operator != (const iterator& it) {
			return !(*this == it);
		}
	};

	Buffer(int size) { //constructor
		if (size == 0) {
			throw std::runtime_error("Size must be greater than 0");
		}
		head = nullptr;
		last = nullptr;
		max_size = size;
		this->size = 0;
	}
	~Buffer() { //detructor
		clear();
	}

	void clear() { // clear buffer
		while (size != 0) {
			pop();
		}
	}

	void push(T elem) { // add item to the end
		
		Node* new_node = new Node(elem);

		if (size == 0) {
			head = new_node;
			last = new_node;
			size++;
			return;
		}
		last->next = new_node;
		new_node->past = last;
		last = new_node;

		size++;
		if (size > max_size) {
			pop();
		}
	}

	void pop() { // add item in begin
		if (size == 0) {
			throw std::runtime_error("Buffer is empty!");
		}

		Node* old_node = head;
		head = head->next;

		delete old_node;
		size--;

	}

	iterator begin() const { // iterator to begin
		return iterator(head);
	}

	iterator end() const { // iterator to end
		return iterator(last);
	}

	void insert(T elem, iterator it) { // insert  a specific node
		if (it == end() || size == 0){
			push(elem);
			return;
		}

		Node* new_node = new Node(elem);

		Node* curr_node = it.node;
		Node* past_node = curr_node->past;
		
		if (past_node != nullptr) {
			past_node->next = new_node;
		}

		new_node->past = past_node;
		new_node->next = curr_node;
		size++;

		if (size >= max_size) {
			pop();
		}

	}

	void erase(iterator it) { // delete a specific node
		if (size == 0) {
			throw std::runtime_error("Buffer is empty!");
		}
		if (it == begin()) {
			pop();
			return;
		}

		Node* del_node = it.node;
		Node* past_node = del_node->past;
		Node* next_node = del_node->next;

		if (past_node != nullptr) {
			past_node->next = next_node;
		}

		if (next_node != nullptr) {
			next_node->past = past_node;
		}

		if (it == end()) {
			last = past_node;
		}

		size--;
		delete del_node;

	}

	int count() { // return real size
		return size;
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

		for (int i = 0; i < size; i++) {
			push(arr[i]);
		}

		delete[] arr;
	}

	void divide(Buffer<T>& obj1, Buffer<T>& obj2, T num) { // dive list into two list, by divider
		if (this == &obj1 || this == &obj2) {
			throw std::runtime_error("You are using the same object!");
		}

		obj1.clear();
		obj2.clear();

		Node* curr = head;
		for (int i = 0; i < size; i++) {
			if (curr->value > num) {
				obj1.push(curr->value);
			}
			else {
				obj2.push(curr->value);
			}
			curr = curr->next;
		}

	}

	// Comparison operators

	bool operator == (const Buffer<T>& obj) const {
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

	bool operator != (const Buffer<T>& obj)  const {
		return !(*this == obj);
	}

	bool operator < (const Buffer<T>& obj) const {
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

	bool operator <= (const Buffer<T>& obj) const {
		return *this < obj || *this == obj;
	}

	bool operator > (const Buffer<T>& obj) const {
		return !(*this < obj) && *this != obj;
	}

	bool operator >= (const Buffer<T>& obj) const {
		return *this > obj || *this == obj;
	}



	friend std::ostream& operator<<(std::ostream& o, const Buffer<T>& buf) {
		Node* new_node = buf.head;
		for (int i = 0; i < buf.size; i++) {
			o << new_node->value << " ";
			new_node = new_node->next;
		}
		o << "\n";
		return o;
	}
};
#endif