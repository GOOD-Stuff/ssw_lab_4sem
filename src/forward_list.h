#ifndef CLASS_FORWARD_LIST_INCLUDED_H
#define CLASS_FORWARD_LIST_INCLUDED_H

#include <ostream>
#include <stdexcept>
#include <initializer_list>
#include "merge_sort.h"

template <class T>
class forward_list
{
private:
	struct node
	{
		T value;
		node* next {nullptr};

		node(T value)
		{
			this->value = value;
		}
	};

	node* head {nullptr};
	int size {0};


	bool is_include(const forward_list<T>& list, int shift_step) const
	{
		if (size < list.size - shift_step)
		{
			return false;
		}

		auto it = begin();
		auto sub_it = list.begin();

		auto recalc_sub_it = [&]()
		{
			sub_it = list.begin();
			int cnt = 0;

			while (cnt++ < shift_step)
			{
				++sub_it;
			}
		};

		recalc_sub_it();
		int coincidence_count = 0;

		while (it != end() && sub_it != list.end())
		{
			if (*it == *sub_it)
			{
				coincidence_count++;
				++sub_it;

				if (coincidence_count == list.size - shift_step)
				{
					++it;
					break;
				}
			}
			else
			{
				coincidence_count = 0;
				recalc_sub_it();
			}

			++it;
		}

		if (coincidence_count == list.size - shift_step)
		{
			if (shift_step == 0)
			{
				return true;
			}

			sub_it = list.begin();
			coincidence_count = 0;

			while (it != end() && sub_it != list.end())
			{
				if (*it == *sub_it)
				{
					coincidence_count++;

					if (coincidence_count == shift_step)
					{
						return true;
					}
				}

				++it;
				++sub_it;
			}
		}

		return false;
	}

public:
	class iterator;
	friend class iterator;
	
	forward_list() = default;

	forward_list(const std::initializer_list<T>& list)
	{
		auto it = list.end() - 1;

		for (int i = 0; i < list.size(); i++)
		{
			push_front(*(it--));
		}
	}

	forward_list(const forward_list<T>& list)
	{
		*this = list;
	}

	forward_list(forward_list<T>&& list) noexcept
	{
		*this = std::move(list);
	}

	~forward_list()
	{
		clear();
	}

	void push_front(T value)
	{
		node* new_node = new node(value);

		new_node->next = head;
		head = new_node;

		size++;
	}
	
	void push_back(T value)
	{
		if (size == 0)
		{
			return push_front(value);
		}
		
		iterator it = begin();

		for (int i = 0; i < size - 1; i++)
			++it;
		
		node* new_node = new node(value);

		it.node_ptr->next = new_node;
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

		iterator it = begin();

		for (int i = 0; i < size - 2; i++)
			++it;
		
		delete it.node_ptr->next;
		it.node_ptr->next = nullptr;

		size--;
	}

	void insert(iterator it, T value)
	{
		if (it == begin())
		{
			push_front(value);
			return;
		}
		
		if (it == end())
		{
			push_back(value);
			return;
		}

		node* new_node = new node(value);
		it.prev()->next = new_node;
		new_node->next = it.node_ptr;

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
			pop_front();
			return;
		}
		
		it.prev()->next = it.node_ptr->next;
		delete it.node_ptr;

		size--;
	}

	iterator begin() const
	{
		return iterator(head, const_cast<forward_list<T>&>(*this));
	}

	iterator end() const
	{
		return iterator(nullptr, const_cast<forward_list<T>&>(*this));
	}

	int count() const
	{
		return size;
	}
	
	bool cyclic_include(const forward_list<T>& list) const
	{
		if (list.size == 0)
		{
			return true;
		}
		
		int shift_step = 0;

		while (shift_step < list.count())
		{
			if (is_include(list, shift_step++))
			{
				return true;
			}
		}

		return false;
	}
	
	forward_list<T> merge_sort(const forward_list<T>& list) const
	{
		int result_size = size + list.size;
		
		T* temp_array = new T[result_size];
		int write_position = 0;

		for (auto& value : *this)
		{
			temp_array[write_position++] = value;
		}

		for (auto& value : list)
		{
			temp_array[write_position++] = value;
		}

		merge_sort_array<T>(temp_array, result_size);

		forward_list<T> new_list;

		for (int i = result_size - 1; i >= 0; i--)
		{
			new_list.push_front(temp_array[i]);
		}

		delete[] temp_array;
		return new_list;
	}

	void clear()
	{
		while (size != 0)
		{
			pop_front();
		}
	}

	forward_list<T>& operator = (const forward_list<T>& list)
	{
		if (this == std::addressof(list))
		{
			return *this;
		}

		clear();

		for (auto value : list)
		{
			push_back(value);
		}
	}

	forward_list<T>& operator = (forward_list<T>&& list) noexcept
	{
		if (this == std::addressof(list))
		{
			return *this;
		}

		clear();

		head = list.head;
		size = list.size;

		list.head = nullptr;
		list.size = 0;
	}
	
	bool operator == (const forward_list<T>& list) const
	{
		if (this == std::addressof(list))
		{
			return true;
		}

		if (size != list.size)
		{
			return false;
		}

		for (iterator it_1 = begin(), it_2 = list.begin(); it_1 != end(); ++it_1, ++it_2)
		{
			if (*it_1 != *it_2)
			{
				return false;
			}
		}

		return true;
	}

	bool operator != (const forward_list<T>& list) const
	{
		return !(*this == list);
	}

	bool operator < (const forward_list<T>& list) const
	{
		if (this == std::addressof(list))
		{
			return false;
		}

		for (iterator it_1 = begin(), it_2 = list.begin(); it_1 != end(); ++it_1, ++it_2)
		{
			if (*it_1 != *it_2)
			{
				return *it_1 < *it_2;
			}
		}

		return size < list.size;
	}

	bool operator <= (const forward_list<T>& list) const
	{
		return *this < list || list == this;
	}

	bool operator > (const forward_list<T>& list) const
	{
		return !(*this < list) && list != this;
	}

	bool operator >= (const forward_list<T>& list) const
	{
		return *this > list || list == this;
	}

	class iterator
	{
	private:
		friend class forward_list<T>;
		
		forward_list<T>& list;
		node* node_ptr {nullptr};

		iterator(node* ptr, forward_list<T>& list_ref) : list(list_ref), node_ptr(ptr) {}

		node* prev() const
		{
			if (node_ptr == list.head)
			{
				return nullptr;
			}

			iterator it = list.begin();

			while (it.node_ptr->next != node_ptr)
			{
				++it;
			}

			return it.node_ptr;
		}
	
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
			return iterator(old_ptr, list);
		}

		T& operator * () const
		{
			if (node_ptr == nullptr)
			{
				throw std::runtime_error("Current node is empty!");
			}
			
			return node_ptr->value;
		}

		iterator& operator = (const iterator& it)
		{
			list = it.list;
			node_ptr = it.node_ptr;

			return *this;
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

	friend std::ostream& operator << (std::ostream& out, const forward_list<T>& list)
	{
		for (auto& value : list)
		{
			out << value << "\n";
		}

		return out;
	}
};

#endif