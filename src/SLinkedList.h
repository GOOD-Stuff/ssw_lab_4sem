#ifndef CLASS_SLINKED_LIST_H
#define CLASS_SLINKED_LIST_H

#include <ostream>
#include <stdexcept>

template <class T>
class SLinkedList
{
private:
	// Structure describing a list cell
	struct Cell
	{
		// Stored value
		T value {};

		// Pointer to the next cell
		Cell* next {};

		Cell() {}

		Cell(T value)
		{
			this->value = value;
		}
	};

	// Pointer to the first cell in the list
	Cell* head {};

	// Number of elements in the list
	int size {};

	// Method that does quick array sorting (for a single linked list, this is a quick variant)
	void quick_sort_array_handler(T* arr, int size)
	{
		int i = 0;
		int j = size - 1;

		T mid = arr[size / 2];

		do
		{
			while (arr[i] < mid)
			{
				i++;
			}

			while (arr[j] > mid)
			{
				j--;
			}

			if (i <= j)
			{
				std::swap(arr[i++], arr[j--]);
			}
		}
		while (i <= j);

		if (j > 0)
		{
			quick_sort_array_handler(arr, j + 1);
		}

		if (i < size)
		{
			quick_sort_array_handler(arr + i, size - i);
		}
	}

public:
	class iterator;

	SLinkedList() {}

	// Constructor with initialization list support
	SLinkedList(const std::initializer_list<T>& lst)
	{
		for (auto& value : lst)
		{
			push_back(value);
		}
	}

	// Copy constructor
	SLinkedList(const SLinkedList<T>& lst)
	{
		*this = lst;
	}

	~SLinkedList()
	{
		clear();
	}

	// Add element to the top of the list
	void push_front(T value)
	{
		Cell* cell = new Cell;
		cell->value = value;

		Cell* prev_head = head;
		head = cell;

		head->next = prev_head;
		size++;
	}

	// Add element to the end of the list
	void push_back(T value)
	{
		if (size != 0)
		{
			Cell* cell = new Cell;
			cell->value = value;

			Cell* current = head;

			while (current->next)
			{
				current = current->next;
			}

			current->next = cell;
			size++;
		}
		else
		{
			push_front(value);
		}
	}

	// Delete the first element of the list
	void pop_front()
	{
		if (size == 0)
		{
			throw std::runtime_error("List is empty!");
		}

		Cell* prev_head = head;
		head = head->next;

		delete prev_head;
		size--;
	}

	// Delete the last element of the list
	void pop_back()
	{
		if (size == 0)
		{
			throw std::runtime_error("List is empty!");
		}

		if (size != 1)
		{
			Cell* current = head;
			Cell* prev_current = nullptr;

			while (current->next)
			{
				prev_current = current;
				current = current->next;
			}

			delete current;
			prev_current->next = nullptr;
			size--;
		}
		else
		{
			pop_front();
		}
	}

	// Insert element after the specified position
	void insert(iterator it, T value)
	{
		Cell* cell = new Cell;
		cell->value = value;

		Cell* cell_it = it.native_pointer();
		Cell* cell_next_old = cell_it->next;

		cell_it->next = cell;
		cell->next = cell_next_old;

		size++;
	}

	// Delete element after the specified position
	void erase(iterator it)
	{
		if (size == 0)
		{
			throw std::runtime_error("List is empty!");
		}

		Cell* cell_it = it.native_pointer();
		Cell* cell_erase = cell_it->next;
		Cell* cell_next = cell_erase->next;
		
		cell_it->next = cell_next;
		delete cell_erase;

		size--;
	}

	// Get iterator to the start of the list
	iterator begin() const
	{
		return iterator(head);
	}

	// Get iterator to the end of the list
	iterator end() const
	{
		return iterator(nullptr);
	}

	// Get the number of elements in the list
	int count() const
	{
		return size;
	}


	// Remove all items from the list
	void clear()
	{
		while (size != 0)
		{
			pop_front();
		}
	}

	// Sort the list in ascending order
	void quick_sort()
	{
		T* arr = new T[size];
		int i = 0;

		for (auto& value : *this)
		{
			arr[i++] = value;
		}

		quick_sort_array_handler(arr, size);

		int old_size = size;
		clear();

		for (int i = old_size - 1; i >= 0; i--)
		{
			push_front(arr[i]);
		}

		delete[] arr;
	}

	// Splitting the current list into two new ones by threshold value
	void devide(SLinkedList<T>& lst1, SLinkedList<T>& lst2, T divider)
	{
		if (this == &lst1 || this == &lst2)
		{
			throw std::runtime_error("Trying to use yourself!");
		}

		lst1.clear();
		lst2.clear();

		for (auto& value : *this)
		{
			if (value < divider)
			{
				lst1.push_back(value);
			}
			else
			{
				lst2.push_back(value);
			}
		}
	}

	// Copy operator
	SLinkedList<T>& operator = (const SLinkedList<T>& lst)
	{
		if (this != &lst)
		{
			clear();

			for (auto& value : lst)
			{
				push_back(value);
			}
		}

		return *this;
	}

	// Comparison operators start
	bool operator == (const SLinkedList<T>& lst) const
	{
		if (this == &lst)
		{
			return true;
		}

		if (size != lst.size)
		{
			return false;
		}

		iterator it_first = begin();
		iterator it_second = lst.begin();

		while (it_first != end())
		{
			if (*it_first++ != *it_second++)
			{
				return false;
			}
		}

		return true;
	}

	bool operator != (const SLinkedList<T>& lst) const
	{
		return !(*this == lst);
	}

	bool operator < (const SLinkedList<T>& lst) const
	{
		if (this == &lst)
		{
			return false;
		}

		iterator it_first = begin();
		iterator it_second = lst.begin();

		while (it_first != end() && it_second != lst.end())
		{
			T& first_value = *it_first++;
			T& second_value = *it_second++;

			if (first_value != second_value)
			{
				return first_value < second_value;
			}
		}

		return size < lst.size;
	}

	bool operator <= (const SLinkedList<T>& lst) const
	{
		return *this < lst || *this == lst;
	}

	bool operator > (const SLinkedList<T>& lst) const
	{
		return !(*this < lst) && *this != lst;
	}

	bool operator >= (const SLinkedList<T>& lst) const
	{
		return *this > lst || *this == lst;
	}
	// Comparison operators end

	// Iterator class for easy navigation through list cells
	class iterator
	{
	private:
		friend class SLinkedList<T>;

		// Pointer to a certain cell
		Cell* cell {};

		// Get a pointer to a cell in its primary form
		Cell* native_pointer()
		{
			return cell;
		}

	public:
		iterator() {}

		iterator(Cell* cell)
		{
			this->cell = cell;
		}

		// Prefix increment
		iterator& operator++()
		{
			if (!cell)
			{
				throw std::runtime_error("Pointer is empty!");
			}

			cell = cell->next;
			return *this;
		}

		// Postfix increment
		iterator operator++(int)
		{
			if (!cell)
			{
				throw std::runtime_error("Pointer is empty!");
			}

			Cell* prev_cell = cell;
			cell = cell->next;

			return iterator(prev_cell);
		}

		// Operator for getting a value
		T& operator*()
		{
			if (!cell)
			{
				throw std::runtime_error("Pointer is empty!");
			}

			return cell->value;
		}

		// Comparison operator equal
		bool operator == (const iterator& it)
		{
			return cell == it.cell;
		}

		// Comparison operator not equal
		bool operator != (const iterator& it)
		{
			return !(*this == it);
		}
	};
};

// List output statement to a stream
template <class T>
std::ostream& operator << (std::ostream& stream, const SLinkedList<T>& lst)
{
	if (lst.count() == 0)
	{
		throw std::runtime_error("List is empty!");
	}

	for (auto& value : lst)
	{
		stream << value << "\n";
	}

	return stream;
}

#endif