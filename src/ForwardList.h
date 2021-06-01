#ifndef CLASS_FORWARD_LIST_H
#define CLASS_FORWARD_LIST_H

#include <stdexcept>
#include <ostream>
#include "QuickSort.h"

template <typename T>
class ForwardList
{
private:
	friend class Iterator;
	static void throw_if(bool condition, const char* message);


	// ForwardList cell (data value, pointer to next cell)
	struct Node
	{
		Node() = delete;
		Node(T value) : data(value) {}

		T data;
		Node* next {nullptr};
	};

	// Number of elements
	size_t size {0};

	// Pointer to first element
	Node* head {nullptr};

public:
	class Iterator;

	ForwardList() = default;

	// Constructor with support initializer list
	ForwardList(const std::initializer_list<T>& list);

	// Copy constructor
	ForwardList(const ForwardList<T>& list) { *this = list; }

	// Move constructor
	ForwardList(ForwardList<T>&& list) noexcept { *this = std::move(list); }

	~ForwardList() { clear(); }

	// Add item to front
	void push_front(T value);

	// Add item to back
	void push_back(T value);

	// Insert element in any position of container
	void insert(Iterator it, T value);

	// Remove first element
	void pop_front();

	// Remove last element
	void pop_back();

	// Remove element from any position of container
	void erase(Iterator it);

	// Get iterator to begin list
	Iterator begin() const { return Iterator(head, const_cast<ForwardList<T>*>(this)); }

	// Get iterator to end list
	Iterator end() const { return Iterator(nullptr, const_cast<ForwardList<T>*>(this)); }

	// Get elements count
	size_t count() const { return size; }

	// Container is empty?
	bool empty() const { return size == 0; }

	// Delete all items from container
	void clear();

	// Individual task 1, variant 3
	ForwardList<T> merge_and_sort(const ForwardList<T>& list) const;

	// Individual task 2, variant 3
	std::pair<T, T> clear_min_max();

	// Copy operator
	ForwardList<T>& operator = (const ForwardList<T>& list);

	// Move operator
	ForwardList<T>& operator = (ForwardList<T>&& list) noexcept;

	// Lexicographic comparison operators
	bool operator == (const ForwardList<T>& list) const;
	bool operator != (const ForwardList<T>& list) const;

	bool operator < (const ForwardList<T>& list) const;
	bool operator > (const ForwardList<T>& list) const;

	bool operator <= (const ForwardList<T>& list) const;
	bool operator >= (const ForwardList<T>& list) const;


	// Class for convenient container passage
	class Iterator
	{
	private:
		friend class ForwardList<T>;

		// Pointer to a container cell
		Node* ptr {nullptr};

		// Pointer to a current List
		ForwardList<T>* list {nullptr};
		
		// Private constructor
		Iterator(Node* p, ForwardList<T>* lst) : ptr(p), list(lst) {}

		// Exceptions control
		void has_errors_control() const
		{
			throw_if(list == nullptr, "The iterator is not bound to a list!");
			throw_if(list->size == 0, "The iterated list is empty!");
			throw_if(ptr == nullptr, "Trying to work with empty pointer!");
		}

		Node* get_prev_node() const
		{
			has_errors_control();
			throw_if(ptr == list->head, "Attempt to go outside the list!");
			
			Node* node = list->head;

			while (node->next != ptr)
				node = node->next;

			return node;
		}

	public:
		Iterator() = default;

		// Prefix operator ++
		Iterator& operator ++ ()
		{
			has_errors_control();

			ptr = ptr->next;
			return *this;
		}

		// Postfix operator ++
		Iterator operator ++ (int)
		{
			has_errors_control();

			Node* old_ptr = ptr;
			ptr = ptr->next;
			return Iterator(old_ptr, list);
		}

		// Operator for getting data
		T& operator * ()
		{
			has_errors_control();
			return ptr->data;
		}

		// Comparison operators
		bool operator == (const Iterator& it) const { return ptr == it.ptr; }
		bool operator != (const Iterator& it) const { return ptr != it.ptr; }
	};
};

template <typename T>
ForwardList<T>::ForwardList(const std::initializer_list<T>& list)
{
	auto it = list.end() - 1;
	size_t i = 0;
	
	while (i++ < list.size())
		push_front(*it--);
}

template <typename T>
void ForwardList<T>::push_front(T value)
{
	Node* node = new Node(value);
	Node* old_head = head;

	head = node;
	node->next = old_head;

	size++;
}

template <typename T>
void ForwardList<T>::push_back(T value)
{
	if (size == 0)
	{
		push_front(value);
		return;
	}

	Node* node = new Node(value);
	Node* it = head;

	while (it->next != nullptr)
		it = it->next;

	it->next = node;
	size++;
}

template <typename T>
void ForwardList<T>::insert(Iterator it, T value)
{
	throw_if(size == 0, "Attempt to insert item to empty list!");

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

	Node* node = new Node(value);
	Node* prev_node = it.get_prev_node();
	
	prev_node->next = node;
	node->next = it.ptr;
	
	size++;
}

template <typename T>
void ForwardList<T>::pop_front()
{
	throw_if(size == 0, "Attempt to delete item from empty list!");

	Node* old_head = head;
	head = head->next;
	
	delete old_head;
	size--;
}

template <typename T>
void ForwardList<T>::pop_back()
{
	throw_if(size == 0, "Attempt to delete item from empty list!");

	if (size == 1)
	{
		pop_front();
		return;
	}

	Node* it = head;
	Node* it_prev = nullptr;

	while (it->next != nullptr)
	{
		it_prev = it;
		it = it->next;
	}

	delete it;
	it_prev->next = nullptr;

	size--;
}

template <typename T>
void ForwardList<T>::erase(Iterator it)
{
	throw_if(size == 0, "Attempt to erase item from empty list!");

	if (it == begin())
	{
		pop_front();
		return;
	}

	it.get_prev_node()->next = it.ptr->next;
	delete it.ptr;

	size--;
}

template <typename T>
void ForwardList<T>::clear()
{
	while (size != 0)
		pop_front();
}

template <typename T>
ForwardList<T> ForwardList<T>::merge_and_sort(const ForwardList<T>& list) const
{
	size_t list_size = size + list.size;
	T* temp_storage = new T[list_size];

	size_t idx = 0;

	for (auto& element : *this)
		temp_storage[idx++] = element;

	for (auto& element : list)
		temp_storage[idx++] = element;

	QuickSort<T>(temp_storage, list_size);

	ForwardList<T> new_list;

	for (int i = list_size - 1; i >= 0; i--)
		new_list.push_front(temp_storage[i]);

	delete[] temp_storage;
	return new_list;
}

template <typename T>
std::pair<T, T> ForwardList<T>::clear_min_max()
{
	throw_if(size < 2, "The number of items in list must be at least 2!");

	// I don't like this implementation... Maybe I'll redo it later

	int current_index = 0;
	int del_index = 0;

	auto delete_found_element = [&]()
	{
		if (del_index == 0)
			pop_front();
		else if (del_index == size - 1)
			pop_back();
		else
			erase(begin() + del_index);
	};

	T min = *begin();

	for (auto it = begin() + 1; it != end(); ++it)
	{
		if (*it < min)
		{
			min = *it;
			del_index = current_index;
		}
		current_index++;
	}

	delete_found_element();
	current_index = 0;

	T max = *begin();

	for (auto it = begin() + 1; it != end(); ++it)
	{
		if (*it > max)
		{
			max = *it;
			del_index = current_index;
		}
		current_index++;
	}

	delete_found_element();

	return { min, max };
}

template <typename T>
ForwardList<T>& ForwardList<T>::operator = (const ForwardList<T>& list)
{
	if (&list == this)
		return *this;

	clear();

	for (auto& element : list)
		push_back(element);

	return *this;
}

template <typename T>
ForwardList<T>& ForwardList<T>::operator = (ForwardList<T>&& list) noexcept
{
	if (&list == this)
		return *this;

	clear();

	head = list.head;
	size = list.size;

	list.head = nullptr;
	list.size = 0;

	return *this;
}

template <typename T>
bool ForwardList<T>::operator == (const ForwardList<T>& list) const
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
bool ForwardList<T>::operator != (const ForwardList<T>& list) const
{
	return !(*this == list);
}

template <typename T>
bool ForwardList<T>::operator < (const ForwardList<T>& list) const
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
bool ForwardList<T>::operator > (const ForwardList<T>& list) const
{
	return !(*this < list) && *this != list;
}

template <typename T>
bool ForwardList<T>::operator <= (const ForwardList<T>& list) const
{
	return *this < list || *this == list;
}

template <typename T>
bool ForwardList<T>::operator >= (const ForwardList<T>& list) const
{
	return *this > list || *this == list;
}

template <typename T>
void ForwardList<T>::throw_if(bool condition, const char* message)
{
	if (condition)
		throw std::runtime_error(message);
}

// Output operator
template <typename T>
std::ostream& operator << (std::ostream& out, const ForwardList<T>& list)
{
	for (auto& element : list)
		out << element << "\n";

	return out;
}

#endif