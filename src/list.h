#ifndef CLASS_LIST_INCLUDED_H
#define CLASS_LIST_INCLUDED_H

#include <ostream>
#include <stdexcept>
#include <initializer_list>
#include "merge_sort.h"

template <class T>
class list
{
private:
	struct node
	{
		T value;

		node* prev {nullptr};
		node* next {nullptr};

		node(T value)
		{
			this->value = value;
		}
	};

	node* head {nullptr};
	node* tail {nullptr};
	
	int size {0};


	bool is_include(const list<T>& lst, int shift_step) const
	{
		if (size < lst.size - shift_step)
		{
			return false;
		}

		auto it = begin();
		auto sub_it = lst.begin() + shift_step;
		
		int coincidence_count = 0;

		while (it != end() && sub_it != lst.end())
		{
			if (*it == *sub_it)
			{
				coincidence_count++;
				++sub_it;

				if (coincidence_count == lst.size - shift_step)
				{
					++it;
					break;
				}
			}
			else
			{
				coincidence_count = 0;
				sub_it = lst.begin() + shift_step;
			}

			++it;
		}

		if (coincidence_count == lst.size - shift_step)
		{
			if (shift_step == 0)
			{
				return true;
			}

			sub_it = lst.begin();
			coincidence_count = 0;

			while (it != end() && sub_it != lst.end())
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
	
	list() = default;

	list(const std::initializer_list<T>& lst)
	{
		for (auto& value : lst)
		{
			push_back(value);
		}
	}

	list(const list<T>& lst)
	{
		*this = lst;
	}

	list(list<T>&& lst) noexcept
	{
		*this = std::move(lst);
	}

	~list()
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
		return iterator(head, const_cast<list<T>&>(*this));
	}

	iterator end() const
	{
		return iterator(nullptr, const_cast<list<T>&>(*this));
	}

	int count() const
	{
		return size;
	}

	bool cyclic_include(const list<T>& lst) const
	{
		if (lst.size == 0)
		{
			return true;
		}

		int shift_step = 0;

		while (shift_step < lst.count())
		{
			if (is_include(lst, shift_step++))
			{
				return true;
			}
		}

		return false;
	}

	list<T> merge_sort(const list<T>& lst) const
	{
		int result_size = size + lst.size;

		T* temp_array = new T[result_size];
		int write_position = 0;

		for (auto& value : *this)
		{
			temp_array[write_position++] = value;
		}

		for (auto& value : lst)
		{
			temp_array[write_position++] = value;
		}

		merge_sort_array<T>(temp_array, result_size);

		list<T> new_list;

		for (int i = 0; i < result_size; i++)
		{
			new_list.push_back(temp_array[i]);
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

	list<T>& operator = (const list<T>& lst)
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

	list<T>& operator = (list<T>&& lst) noexcept
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

	bool operator == (const list<T>& lst) const
	{
		if (this == std::addressof(lst))
		{
			return true;
		}

		if (size != lst.size)
		{
			return false;
		}

		for (iterator it_1 = begin(), it_2 = lst.begin(); it_1 != end(); ++it_1, ++it_2)
		{
			if (*it_1 != *it_2)
			{
				return false;
			}
		}

		return true;
	}

	bool operator != (const list<T>& lst) const
	{
		return !(*this == lst);
	}

	bool operator < (const list<T>& lst) const
	{
		if (this == std::addressof(lst))
		{
			return false;
		}

		for (iterator it_1 = begin(), it_2 = lst.begin(); it_1 != end(); ++it_1, ++it_2)
		{
			if (*it_1 != *it_2)
			{
				return *it_1 < *it_2;
			}
		}

		return size < lst.size;
	}

	bool operator <= (const list<T>& lst) const
	{
		return *this < lst || lst == this;
	}

	bool operator > (const list<T>& lst) const
	{
		return !(*this < lst) && lst != this;
	}

	bool operator >= (const list<T>& lst) const
	{
		return *this > lst || lst == this;
	}

	class iterator
	{
	private:
		friend class list<T>;

		list<T>& lst;
		node* node_ptr {nullptr};

		iterator(node* p_node, list<T>& list_ref) : lst(list_ref), node_ptr(p_node) {}

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

	friend std::ostream& operator << (std::ostream& out, const list<T>& lst)
	{
		for (auto& value : lst)
		{
			out << value << "\n";
		}

		return out;
	}
};

#endif