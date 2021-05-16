#ifndef CLASS_LIST_H
#define CLASS_LIST_H

#include <stdexcept>
#include <ostream>
#include "QuickSort.h"

template <typename T>
class List
{
private:
	friend class Iterator;
	static void throw_if(bool condition, const char* message);
	void destroy();


	// List cell (data value, pointer to prev cell, pointer to next cell)
	struct Node
	{
		Node() = default;
		Node(T value) : data(value) {}

		T data {};

		Node* prev {nullptr};
		Node* next {nullptr};
	};

	// Number of elements
	size_t size {0};

	// Pointer to first element
	Node* head {nullptr};

	// Pointer to last element
	Node* tail {new Node};

public:
	class Iterator;

	List() = default;

	// Constructor with support initializer list
	List(const std::initializer_list<T>& list);

	// Copy constructor
	List(const List<T>& list) { *this = list; }

	// Move constructor
	List(List<T>&& list) noexcept { *this = std::move(list); }

	~List() { destroy(); }

	// Add item to front
	void push_front(T value);

	// Add item to back
	void push_back(T value);

	// Insert element in any position of container
	void insert(const Iterator& it, T value);

	// Remove first element
	void pop_front();

	// Remove last element
	void pop_back();

	// Remove element from any position of container
	void erase(const Iterator& it);

	// Get iterator to begin list
	Iterator begin() const { return (head != nullptr) ? head : tail; }

	// Get iterator to end list
	Iterator end() const { return tail; }

	// Get elements count
	size_t count() const { return size; }

	// Container is empty?
	bool empty() const { return size == 0; }

	// Delete all items from container
	void clear();

	// Individual task 1, variant 3
	List<T> merge_and_sort(const List<T>& list);

	// Individual task 2, variant 3
	std::pair<T, T> clear_min_max();

	// Copy operator
	List<T>& operator = (const List<T>& list);

	// Move operator
	List<T>& operator = (List<T>&& list) noexcept;

	// Lexicographic comparison operators
	bool operator == (const List<T>& list);
	bool operator != (const List<T>& list);

	bool operator < (const List<T>& list);
	bool operator > (const List<T>& list);

	bool operator <= (const List<T>& list);
	bool operator >= (const List<T>& list);


	// Class for convenient container passage
	class Iterator
	{
	private:
		friend class List<T>;

		// Pointer to a container cell
		Node* ptr {nullptr};

		// Private constructor
		Iterator(Node* p) : ptr(p) {}

	public:
		Iterator() = default;

		// Prefix operator ++
		Iterator& operator ++ ()
		{
			throw_if(ptr == nullptr, "Trying to work with empty pointer!");

			ptr = ptr->next;
			return *this;
		}

		// Postfix operator ++
		Iterator operator ++ (int)
		{
			throw_if(ptr == nullptr, "Trying to work with empty pointer!");

			Node* old_ptr = ptr;
			ptr = ptr->next;
			return old_ptr;
		}

		// Shift operator
		Iterator operator + (size_t offset)
		{
			throw_if(ptr == nullptr, "Trying to work with empty pointer!");

			Iterator it(ptr);

			for (size_t i = 0; i < offset; i++)
				++it;

			return it;
		}

		// Prefix operator ++
		Iterator& operator -- ()
		{
			throw_if(ptr == nullptr, "Trying to work with empty pointer!");

			ptr = ptr->prev;
			return *this;
		}

		// Postfix operator ++
		Iterator operator -- (int)
		{
			throw_if(ptr == nullptr, "Trying to work with empty pointer!");

			Node* old_ptr = ptr;
			ptr = ptr->prev;
			return old_ptr;
		}

		// Shift operator
		Iterator operator - (size_t offset)
		{
			throw_if(ptr == nullptr, "Trying to work with empty pointer!");

			Iterator it(ptr);

			for (size_t i = 0; i < offset; i++)
				--it;

			return it;
		}

		// Operator for getting data
		T& operator * ()
		{
			throw_if(ptr == nullptr, "Trying to work with empty pointer!");
			return ptr->data;
		}

		// Comparison operators
		bool operator == (const Iterator& it) { return ptr == it.ptr; }
		bool operator != (const Iterator& it) { return ptr != it.ptr; }
	};
};

template <typename T>
List<T>::List(const std::initializer_list<T>& list)
{
	for (auto& element : list)
		push_back(element);
}

template <typename T>
void List<T>::push_front(T value)
{
	Node* node = new Node(value);
	Node* old_head = head;

	head = node;
	node->next = old_head;

	if (old_head != nullptr)
		old_head->prev = head;
	
	if (size == 0)
	{
		tail->prev = head;
		head->next = tail;
	}

	size++;
}

template <typename T>
void List<T>::push_back(T value)
{
	if (size == 0)
		return push_front(value);

	Node* node = new Node(value);
	Node* tail_prev = tail->prev;

	tail_prev->next = node;
	node->prev = tail_prev;

	node->next = tail;
	tail->prev = node;

	size++;
}

template <typename T>
void List<T>::insert(const Iterator& it, T value)
{
	throw_if(size == 0, "Attempt to insert item to empty list!");

	if (const_cast<Iterator&>(it) == begin())
		return push_front(value);
	else if (const_cast<Iterator&>(it) == begin() + size)
		return push_back(value);

	Node* new_node = new Node(value);
	Node* left_node = it.ptr->prev;

	left_node->next = new_node;
	new_node->prev = left_node;

	new_node->next = it.ptr;
	it.ptr->prev = new_node;

	size++;
}

template <typename T>
void List<T>::pop_front()
{
	throw_if(size == 0, "Attempt to delete item from empty list!");

	Node* old_head = head;
	head = head->next;

	if (head != nullptr)
		head->prev = nullptr;

	delete old_head;

	size--;
}

template <typename T>
void List<T>::pop_back()
{
	throw_if(size == 0, "Attempt to delete item from empty list!");

	if (size == 1)
		return pop_front();

	Node* old_prev_tail = tail->prev;
	tail->prev = old_prev_tail->prev;
	old_prev_tail->prev->next = tail;

	delete old_prev_tail;

	size--;
}

template <typename T>
void List<T>::erase(const Iterator& it)
{
	throw_if(size == 0, "Attempt to erase item from empty list!");

	if (const_cast<Iterator&>(it) == begin())
		return pop_front();
	else if (const_cast<Iterator&>(it) == end() - 1)
		return pop_back();

	Node* left_node = it.ptr->prev;
	Node* right_node = it.ptr->next;

	left_node->next = right_node;
	right_node->prev = left_node;

	delete it.ptr;
	size--;
}

template <typename T>
void List<T>::clear()
{
	while (size != 0)
		pop_front();
}

template <typename T>
List<T> List<T>::merge_and_sort(const List<T>& list)
{
	size_t list_size = size + list.size;
	T* temp_storage = new T[list_size];

	size_t idx = 0;

	for (auto& element : *this)
		temp_storage[idx++] = element;

	for (auto& element : list)
		temp_storage[idx++] = element;

	QuickSort<T>(temp_storage, list_size);

	List<T> new_list;

	for (int i = list_size - 1; i >= 0; i--)
		new_list.push_front(temp_storage[i]);

	delete[] temp_storage;

	return new_list;
}

template <typename T>
std::pair<T, T> List<T>::clear_min_max()
{
	throw_if(size < 2, "The number of items in list must be at least 2!");

	auto min_it = begin();
	auto max_it = begin();

	for (auto it = begin() + 1; it != end(); ++it)
	{
		if (*it < *min_it)
			min_it = it;

		if (*it > *max_it)
			max_it = it;
	}

	std::pair<T, T> pair = { *min_it, *max_it };

	erase(min_it);
	erase(max_it);

	return pair;
}

template <typename T>
List<T>& List<T>::operator = (const List<T>& list)
{
	if (&list == this)
		return *this;

	clear();

	for (auto& element : list)
		push_back(element);

	return *this;
}

template <typename T>
List<T>& List<T>::operator = (List<T>&& list) noexcept
{
	if (&list == this)
		return *this;
	
	destroy();

	head = list.head;
	size = list.size;
	tail = list.tail;

	list.head = nullptr;
	list.size = 0;
	list.tail = new Node;
	
	return *this;
}

template <typename T>
bool List<T>::operator == (const List<T>& list)
{
	if (&list == this)
		return true;

	if (size != list.size)
		return false;

	auto this_begin = begin();
	auto list_begin = list.begin();

	while (this_begin != end())
		if (*(this_begin++) != *(list_begin++))
			return false;

	return true;
}

template <typename T>
bool List<T>::operator != (const List<T>& list)
{
	return !(*this == list);
}

template <typename T>
bool List<T>::operator < (const List<T>& list)
{
	if (&list == this)
		return false;

	auto this_begin = begin();
	auto list_begin = list.begin();

	while (this_begin != end() && list_begin != list.end())
	{
		T& this_value = *(this_begin++);
		T& list_value = *(list_begin++);

		if (this_value != list_value)
			return this_value < list_value;
	}

	return size < list.size;
}

template <typename T>
bool List<T>::operator > (const List<T>& list)
{
	return !(*this < list) && *this != list;
}

template <typename T>
bool List<T>::operator <= (const List<T>& list)
{
	return *this < list || *this == list;
}

template <typename T>
bool List<T>::operator >= (const List<T>& list)
{
	return *this > list || *this == list;
}

template <typename T>
void List<T>::throw_if(bool condition, const char* message)
{
	if (condition)
		throw std::runtime_error(message);
}

template <typename T>
void List<T>::destroy()
{
	clear();
	delete tail;
}

// Output operator
template <typename T>
std::ostream& operator << (std::ostream& out, const List<T>& list)
{
	if (list.count() == 0)
		throw "Attempt to display empty list!";

	for (auto& element : list)
		out << element << "\n";

	return out;
}

#endif