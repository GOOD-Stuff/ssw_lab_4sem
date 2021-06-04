#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include <ostream>
#include <stdexcept>
#include <initializer_list>
#include <utility>
#include "array_quick_sort.h"

template <class T>
class double_linked_list
{
private:
	using dlist = double_linked_list<T>;

	struct element
	{
		T value;
		
		element* prev {nullptr};
		element* next {nullptr};

		element(T val) : value(val) { }
	};

	element* start {nullptr};
	element* last {nullptr};
	
	int count {0};

public:
	class iterator
	{
	private:
		friend class dlist;

		const dlist* attached_list;
		element* current_element;
		
		iterator(const dlist* list, element* el) : attached_list(list), current_element(el) { }

	public:
		iterator() = delete;

		iterator operator ++ (int)
		{
			if (current_element == nullptr) {
				throw std::out_of_range("iterator out of range!");
			}

			element* prev_element = current_element;
			current_element = current_element->next;

			return iterator(attached_list, prev_element);
		}

		iterator& operator ++ ()
		{
			if (current_element == nullptr) {
				throw std::out_of_range("iterator out of range!");
			}

			current_element = current_element->next;
			return *this;
		}

		iterator operator -- (int)
		{
			if (current_element == attached_list->start) {
				throw std::out_of_range("iterator out of range!");
			}

			if (current_element == nullptr) {
				return iterator(attached_list, attached_list->last);
			}

			element* prev_element = current_element;
			current_element = current_element->prev;

			return iterator(attached_list, prev_element);
		}

		iterator& operator -- ()
		{
			if (current_element == attached_list->start) {
				throw std::out_of_range("iterator out of range!");
			}

			if (current_element == nullptr) {
				current_element = attached_list->last;
				return *this;
			}

			current_element = current_element->prev;
			return *this;
		}

		iterator operator + (int step)
		{
			iterator it = *this;

			for (int i = 0; i < step; i++) {
				++it;
			}
						
			return *this;
		}

		iterator operator - (int step)
		{
			iterator it = *this;

			for (int i = 0; i < step; i++) {
				--it;
			}

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

	double_linked_list() = default;

	double_linked_list(const std::initializer_list<T>& init_list)
	{
		for (auto it = init_list.begin(); it != init_list.end(); ++it) {
			push_back(*it);
		}
	}

	double_linked_list(const dlist& list)
	{
		*this = list;
	}

	~double_linked_list()
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

		if (prev_start != nullptr) {
			prev_start->prev = new_element;
		}

		if (++count == 1) {
			last = start;
		}
	}

	void pop_front()
	{
		if (count == 0) {
			throw std::runtime_error("list is empty!");
		}

		element* prev_start = start;
		start = start->next;

		if (start != nullptr) {
			start->prev = nullptr;
		}

		delete prev_start;
		count--;
	}

	void push_back(T value)
	{
		if (count == 0) {
			push_front(value);
			return;
		}

		element* new_element = new element(value);
		element* prev_last = last;

		last = new_element;
		last->prev = prev_last;
		prev_last->next = last;

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

		element* prev_last = last;

		last = last->prev;
		last->next = nullptr;

		delete prev_last;
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

		element* new_element = new element(value);
		element* prev_element = it.current_element->prev;

		prev_element->next = new_element;
		new_element->prev = prev_element;

		new_element->next = it.current_element;
		it.current_element->prev = new_element;

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

		if (it == --end()) {
			pop_back();
			return;
		}

		element* prev_element = it.current_element->prev;
		element* next_element = it.current_element->next;

		prev_element->next = next_element;
		next_element->prev = prev_element;

		delete it.current_element;
		count--;
	}

	iterator begin() const
	{
		return iterator(this, start);
	}

	iterator end() const
	{
		return iterator(this, nullptr);
	}

	int size() const
	{
		return count;
	}

	dlist& operator = (const dlist& list)
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

	bool operator == (const dlist& list) const
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

	bool operator != (const dlist& list) const
	{
		return !(*this == list);
	}

	bool operator < (const dlist& list) const
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

	bool operator <= (const dlist& list) const
	{
		return *this < list || *this == list;
	}

	bool operator > (const dlist& list) const
	{
		return !(*this < list) && *this != list;
	}

	bool operator >= (const dlist& list) const
	{
		return *this > list || *this == list;
	}

	dlist merge_sort(const dlist& list)
	{
		dlist merged_list;
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

	friend std::ostream& operator << (std::ostream& out, const dlist& list)
	{
		for (iterator it = list.begin(); it != list.end(); ++it) {
			out << *it << "\n";
		}

		return out;
	}
};

#endif