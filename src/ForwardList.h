#ifndef CLASS_FORWARD_LIST_H
#define CLASS_FORWARD_LIST_H

#include <stdexcept>
#include <ostream>

template <typename T>
class ForwardList
{
private:
	friend class Iterator;
	static void throw_if(bool condition, const char* message);

public:
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

	// Insert element in any position of container (AFTER *it!)
	void insert(const Iterator& it, T value);

	// Remove first element
	void pop_front();

	// Remove last element
	void pop_back();

	// Remove element from any position of container (AFTER *it!)
	void erase(const Iterator& it);

	// Get iterator to begin list
	Iterator begin() const { return head; }

	// Get iterator to end list
	Iterator end() const { return nullptr; }

	// Get elements count
	size_t count() const { return size; }

	// Container is empty?
	bool empty() const { return size == 0; }

	// Delete all items from container
	void clear();

	static ForwardList<T> merge_and_sort(const ForwardList<T>& list_1, const ForwardList<T>& list_2);
	ForwardList<T> merge_and_sort(const ForwardList<T>& list);

	std::pair<T, T> clear_min_max();

	// Copy operator
	ForwardList<T>& operator = (const ForwardList<T>& list);

	// Move operator
	ForwardList<T>& operator = (ForwardList<T>&& list);

	// Lexicographic comparison operators
	bool operator == (const ForwardList<T>& list);
	bool operator != (const ForwardList<T>& list);

	bool operator < (const ForwardList<T>& list);
	bool operator > (const ForwardList<T>& list);

	bool operator <= (const ForwardList<T>& list);
	bool operator >= (const ForwardList<T>& list);

	// Output operator
	friend std::ostream& operator << (std::ostream& out, const ForwardList<T>& list)
	{
		throw_if(list.size == 0, "Attempt to display empty list!");

		for (auto it = list.begin(); it != list.end(); ++it)
			out << *it << "\n";

		return out;
	}

	// Class for convenient container passage
	class Iterator
	{
	private:
		// Pointer to a container cell
		Node* ptr {nullptr};

	private:
		friend class ForwardList<T>;
		
		// Get a container cell in its raw form
		Node* get_node() { return ptr; }

	public:
		Iterator() = default;
		Iterator(Node* p) : ptr(p) {}

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

		// Operator for getting data
		T& operator * () { return ptr->data; }

		// Comparison operators
		bool operator == (const Iterator& it) { return ptr == it.ptr; }
		bool operator != (const Iterator& it) { return ptr != it.ptr; }
	};
};

template <typename T>
ForwardList<T>::ForwardList(const std::initializer_list<T>& list)
{
	for (auto& element : list)
		push_back(element);
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
		return push_front(value);

	Node* node = new Node(value);
	Node* it = head;

	while (it->next != nullptr)
		it = it->next;

	it->next = node;
	size++;
}

template <typename T>
void ForwardList<T>::insert(const Iterator& it, T value)
{
	throw_if(size == 0, "Attempt to insert item to empty list!");

	if (const_cast<Iterator&>(it) == end())
		return push_back(value);

	Node* current_node = const_cast<Iterator&>(it).get_node();
	Node* old_next_node = current_node->next;
	Node* new_node = new Node(value);

	current_node->next = new_node;
	new_node->next = old_next_node;

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
		return pop_front();

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
void ForwardList<T>::erase(const Iterator& it)
{
	throw_if(size == 0, "Attempt to erase item from empty list!");

	Node* current_node = const_cast<Iterator&>(it).get_node();
	Node* node_for_delete = current_node->next;
	Node* next_node = node_for_delete->next;

	delete node_for_delete;
	current_node->next = next_node;

	size--;
}

template <typename T>
void ForwardList<T>::clear()
{
	while (size != 0)
		pop_front();
}

template <typename T>
ForwardList<T> ForwardList<T>::merge_and_sort(const ForwardList<T>& list_1, const ForwardList<T>& list_2)
{
	ForwardList<T> list = list_1;

	for (auto it = list_2.begin(); it != list_2.end(); ++it)
		list.push_back(*it);

	for (auto it_i = list.begin(); it_i != list.end(); ++it_i)
		for (auto it_j = list.begin(); it_j != list.begin() + (list.count() - 1); ++it_j)
			if (*(it_j + 1) < *it_j)
				std::swap(*(it_j + 1), *it_j);

	return list;
}

template <typename T>
ForwardList<T> ForwardList<T>::merge_and_sort(const ForwardList<T>& list)
{
	return merge_and_sort(*this, list);
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

	for (auto it = list.begin(); it != list.end(); ++it)
		push_back(*it);

	return *this;
}

template <typename T>
ForwardList<T>& ForwardList<T>::operator = (ForwardList<T>&& list)
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
bool ForwardList<T>::operator == (const ForwardList<T>& list)
{
	if (&list == this)
		return true;

	if (size != list.size)
		return false;

	auto this_begin = begin();
	auto list_begin = list.begin();

	while (this_begin != end() && list_begin != list.end())
		if (*(this_begin++) != *(list_begin++))
			return false;

	return true;
}

template <typename T>
bool ForwardList<T>::operator != (const ForwardList<T>& list)
{
	return !(*this == list);
}

template <typename T>
bool ForwardList<T>::operator < (const ForwardList<T>& list)
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
bool ForwardList<T>::operator > (const ForwardList<T>& list)
{
	return !(*this < list) && *this != list;
}

template <typename T>
bool ForwardList<T>::operator <= (const ForwardList<T>& list)
{
	return *this < list || *this == list;
}

template <typename T>
bool ForwardList<T>::operator >= (const ForwardList<T>& list)
{
	return *this > list || *this == list;
}

template <typename T>
void ForwardList<T>::throw_if(bool condition, const char* message)
{
	if (condition)
		throw std::runtime_error(message);
}

#endif