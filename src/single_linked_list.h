#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKER_LIST_H

#include <ostream>
#include <stdexcept>
#include <initializer_list>
#include <utility>
#include "array_quick_sort.h"

template <class T>
class single_linked_list
{
private:
	using slist = single_linked_list<T>;

	struct element
	{
		T value;
		element* next {nullptr};

		element(T val) : value(val) { }
	};

	element* start {nullptr};
	int count {0};

public:
	class iterator
	{
	private:
		friend class slist;
		element* current_element;
		
		iterator(element* el) : current_element(el) { }
	
	public:
		iterator() = delete;
		
		iterator operator ++ (int)
		{
			if (current_element == nullptr) {
				throw std::out_of_range("iterator out of range!");
			}
			
			element* prev_element = current_element;
			current_element = current_element->next;

			return iterator(prev_element);
		}

		iterator& operator ++ ()
		{
			if (current_element == nullptr) {
				throw std::out_of_range("iterator out of range!");
			}
			
			current_element = current_element->next;
			return *this;
		}

		bool operator == (const iterator& it) const
		{
			return current_element == it.current_element;
		}

		bool operator != (const iterator& it) const
		{
			return !(*this == it);
		}

		T& operator * () const
		{
			if (current_element == nullptr) {
				throw std::out_of_range("iterator out of range!");
			}
			
			return current_element->value;
		}
	};
	
	single_linked_list() = default;

	single_linked_list(const std::initializer_list<T>& init_list)
	{
		for (auto it = init_list.begin(); it != init_list.end(); ++it) {
			push_back(*it);
		}
	}

	single_linked_list(const slist& list)
	{
		*this = list;
	}

	~single_linked_list()
	{
		clear();
	}

	void clear()
	{
		while (count != 0) {
			pop_front();
		}
	}
	
	void push_front(T value)
	{
		element* new_element = new element(value);
		element* prev_start = start;

		start = new_element;
		new_element->next = prev_start;
		count++;
	}

	void pop_front()
	{
		if (count == 0) {
			throw std::runtime_error("list is empty!");
		}
		
		element* prev_start = start;
		start = start->next;
		
		delete prev_start;
		count--;
	}

	void push_back(T value)
	{
		if (count == 0) {
			push_front(value);
			return;
		}

		element* last = start;
		
		while (last->next != nullptr) {
			last = last->next;
		}

		last->next = new element(value);
		count++;
	}

	void pop_back()
	{
		if (count == 0) {
			throw std::runtime_error("list is empty!");
		}
		
		if (count == 1) {
			pop_front();
			return;
		}
		
		element* last = start;
		element* prev_last = nullptr;
		
		while (last->next != nullptr) {
			prev_last = last;
			last = last->next;
		}
		
		delete last;
		prev_last->next = nullptr;
		
		count--;
	}

	void insert(iterator it, T value)
	{
		if (it == begin()) {
			push_front(value);
			return;
		}

		if (it == end()) {
			push_back(value);
			return;
		}

		iterator prev_it = begin();

		while (prev_it.current_element->next != it.current_element) {
			++prev_it;
		}

		element* new_element = new element(value);

		prev_it.current_element->next = new_element;
		new_element->next = it.current_element;

		count++;
	}

	void erase(iterator it)
	{
		if (count == 0) {
			throw std::runtime_error("list is empty!");
		}
		
		if (it == begin()) {
			pop_front();
			return;
		}

		iterator prev_it = begin();

		while (prev_it.current_element->next != it.current_element) {
			++prev_it;
		}

		prev_it.current_element->next = it.current_element->next;
		delete it.current_element;
		
		count--;
	}

	iterator begin() const
	{
		return iterator(start);
	}

	iterator end() const
	{
		return iterator(nullptr);
	}

	int size() const
	{
		return count;
	}

	slist& operator = (const slist& list)
	{
		if (this == std::addressof(list)) {
			return *this;
		}

		clear();

		for (iterator it = list.begin(); it != list.end(); ++it) {
			push_back(*it);
		}

		return *this;
	}
	
	bool operator == (const slist& list) const
	{
		if (this == std::addressof(list)) {
			return true;
		}

		if (count != list.count) {
			return false;
		}

		for (iterator it_1 = begin(), it_2 = list.begin(); it_1 != end(); ++it_1, ++it_2) {
			if (*it_1 != *it_2) {
				return false;
			}
		}

		return true;
	}

	bool operator != (const slist& list) const
	{
		return !(*this == list);
	}

	bool operator < (const slist& list) const
	{
		if (this == std::addressof(list)) {
			return false;
		}

		for (iterator it_1 = begin(), it_2 = list.begin(); it_1 != end(); ++it_1, ++it_2) {
			if (*it_1 != *it_2) {
				return *it_1 < *it_2;
			}
		}

		return count < list.count;
	}

	bool operator <= (const slist& list) const
	{
		return *this < list || *this == list;
	}

	bool operator > (const slist& list) const
	{
		return !(*this < list) && *this != list;
	}

	bool operator >= (const slist& list) const
	{
		return *this > list || *this == list;
	}

	slist merge_sort(const slist& list)
	{
		slist merged_list;
		int full_count = count + list.count;

		if (full_count == 0) {
			return merged_list;
		}
		
		T* temp_array = new T[full_count];
		int write_pos = 0;

		for (iterator it = begin(); it != end(); ++it, ++write_pos) {
			temp_array[write_pos] = *it;
		}

		for (iterator it = list.begin(); it != list.end(); ++it, ++write_pos) {
			temp_array[write_pos] = *it;
		}

		array_quick_sort<T>(temp_array, full_count);

		for (int i = full_count - 1; i >= 0; i--) {
			merged_list.push_front(temp_array[i]);
		}

		delete[] temp_array;
		return merged_list;
	}
	
	std::pair<T, T> erase_min_max()
	{
		if (count == 0) {
			throw std::runtime_error("list is empty!");
		}

		if (count == 1) {
			T value = *begin();
			pop_front();
			
			return { value, value };
		}

		int index = 0;
		
		int min_index = 0;
		int max_index = 0;

		iterator min_it = begin();
		iterator max_it = begin();
		
		for (iterator it = begin(); it != end(); ++it) {
			if (*it < *min_it) {
				min_it = it;
				min_index = index;
			}

			if (*it > *max_it) {
				max_it = it;
				max_index = index;
			}

			++index;
		}

		T min_value = *min_it;
		T max_value = *max_it;

		if (min_index > max_index) {
			erase(min_it);
			erase(max_it);
		} else {
			erase(max_it);
			erase(min_it);
		}
		
		return { min_value, max_value };
	}

	friend std::ostream& operator << (std::ostream& out, const slist& list)
	{
		for (iterator it = list.begin(); it != list.end(); ++it) {
			out << *it << "\n";
		}

		return out;
	}
};

#endif