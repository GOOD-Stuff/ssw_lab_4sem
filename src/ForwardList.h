#ifndef CLASS_FORWARD_LIST_H
#define CLASS_FORWARD_LIST_H

#include <ostream>

template <typename T>
class ForwardList
{
private:
	friend class Iterator;
	static void throw_if(bool condition, const char* message);

public:
	struct Node
	{
		Node() = delete;
		Node(T value) : data(value) {}

		T data;
		Node* next{};
	};

	size_t count{};
	Node* head{};

public:
	class Iterator;

	ForwardList() = default;
	ForwardList(const std::initializer_list<T>& list);
	ForwardList(const ForwardList<T>& list) { *this = list; }

	~ForwardList() { clear(); }

	void push_front(T value);
	void push_back(T value);
	void insert(const Iterator& it, T value);

	void pop_front();
	void pop_back();
	void erase(const Iterator& it);

	Iterator begin() const { return head; }
	Iterator end() const { return nullptr; }

	size_t size() const { return count; }
	bool empty() const { return count == 0; }

	void clear();

	static ForwardList<T> merge_and_sort(const ForwardList<T>& list_1, const ForwardList<T>& list_2);
	std::pair<T, T> clear_min_max();

	ForwardList<T>& operator = (const ForwardList<T>& list);

	bool operator == (const ForwardList<T>& list);
	bool operator != (const ForwardList<T>& list);

	bool operator < (const ForwardList<T>& list);
	bool operator > (const ForwardList<T>& list);

	bool operator <= (const ForwardList<T>& list);
	bool operator >= (const ForwardList<T>& list);

	friend std::ostream& operator << (std::ostream& out, const ForwardList<T>& list)
	{
		for (auto it = list.begin(); it != list.end(); ++it)
			out << *it << "\n";

		return out;
	}

	class Iterator
	{
	private:
		Node* ptr{};

	private:
		friend class ForwardList<T>;
		Node* get_node() { return ptr; }

	public:
		Iterator() = default;
		Iterator(Node * p) : ptr(p) {}

		Iterator operator ++ ()
		{
			throw_if(ptr == nullptr, "Trying to work with empty pointer!");

			ptr = ptr->next;
			return ptr;
		}

		Iterator operator ++ (int)
		{
			throw_if(ptr == nullptr, "Trying to work with empty pointer!");

			Node* old_ptr = ptr;
			ptr = ptr->next;
			return old_ptr;
		}

		Iterator operator + (size_t offset)
		{
			throw_if(ptr == nullptr, "Trying to work with empty pointer!");

			Iterator it(ptr);

			for (size_t i = 0; i < offset; i++)
				++it;
			
			return it;
		}

		T& operator * () { return ptr->data; }

		bool operator == (const Iterator& it) { return ptr == it.ptr; }
		bool operator != (const Iterator& it) { return ptr != it.ptr; }
	};
};

#endif

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

	count++;
}

template <typename T>
void ForwardList<T>::push_back(T value)
{
	if (count == 0)
		return push_front(value);

	Node* node = new Node(value);
	Node* it = head;

	while (it->next != nullptr)
		it = it->next;

	it->next = node;
	count++;
}

template <typename T>
void ForwardList<T>::insert(const Iterator& it, T value)
{
	throw_if(count == 0, "Attempt to insert item to empty list!");

	if (const_cast<Iterator&>(it) == end())
		return push_back(value);

	Node* current_node = const_cast<Iterator&>(it).get_node();
	Node* old_next_node = current_node->next;
	Node* new_node = new Node(value);

	current_node->next = new_node;
	new_node->next = old_next_node;

	count++;
}

template <typename T>
void ForwardList<T>::pop_front()
{
	throw_if(count == 0, "Attempt to delete item from empty list!");

	Node* old_head = head;
	head = head->next;
	delete old_head;

	count--;
}

template <typename T>
void ForwardList<T>::pop_back()
{
	throw_if(count == 0, "Attempt to delete item from empty list!");

	if (count == 1)
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

	count--;
}

template <typename T>
void ForwardList<T>::erase(const Iterator& it)
{
	throw_if(count == 0, "Attempt to erase item from empty list!");

	Node* current_node = const_cast<Iterator&>(it).get_node();
	Node* node_for_delete = current_node->next;
	Node* next_node = node_for_delete->next;

	delete node_for_delete;
	current_node->next = next_node;

	count--;
}

template <typename T>
void ForwardList<T>::clear()
{
	while (count != 0)
		pop_front();
}

template <typename T>
ForwardList<T> ForwardList<T>::merge_and_sort(const ForwardList<T>& list_1, const ForwardList<T>& list_2)
{
	ForwardList<T> list = list_1;

	for (auto it = list_2.begin(); it != list_2.end(); ++it)
		list.push_back(*it);

	for (auto it_i = list.begin(); it_i != list.end(); ++it_i)
		for (auto it_j = list.begin(); it_j != list.begin() + (list.size() - 1); ++it_j)
			if (*(it_j + 1) < *it_j)
				std::swap(*(it_j + 1), *it_j);

	return list;
}

template <typename T>
std::pair<T, T> ForwardList<T>::clear_min_max()
{
	throw_if(count < 2, "The number of items in list must be at least 2!");

	int current_index = 0;
	int del_index = 0;

	auto delete_found_element = [&]()
	{
		if (del_index == 0)
			pop_front();
		else if (del_index == count - 1)
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
bool ForwardList<T>::operator == (const ForwardList<T>& list)
{
	if (&list == this)
		return true;

	if (count != list.count)
		return false;

	auto this_begin = begin();
	auto list_begin = list.begin();

	for (size_t i = 0; i < count; i++)
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

	return count < list.count;
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