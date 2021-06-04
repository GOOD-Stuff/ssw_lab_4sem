#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include "double_linked_list.h"

template <class T>
class circular_buffer
{
private:
	using cbuff = circular_buffer<T>;
	
	double_linked_list<T> stored_list;
	int capacity;

	circular_buffer(const double_linked_list<T>& list) : stored_list(list), capacity(list.size())
	{
		if (capacity == 0) {
			throw std::invalid_argument("capacity must not be zero!");
		}
	}

public:
	using iterator = typename double_linked_list<T>::iterator;
	explicit circular_buffer(int elements_count) : capacity(elements_count) { }

	circular_buffer(const std::initializer_list<T>& init_list)
	{
		for (auto it = init_list.begin(); it != init_list.end(); ++it) {
			push(*it);
		}
	}

	circular_buffer(const cbuff& buff)
	{
		*this = buff;
	}

	void clear()
	{
		stored_list.clear();
	}

	void push(T value)
	{
		stored_list.push_back(value);
	}

	void pop()
	{
		stored_list.pop_front();
	}

	void insert(iterator it, T value)
	{
		bool begin_insert = it == begin();
		stored_list.insert(it, value);

		if (stored_list.size() > capacity) {
			if (begin_insert) {
				stored_list.erase(begin() + 1);
			} else {
				stored_list.pop_front();
			}
		}
	}

	void erase(iterator it)
	{
		stored_list.erase(it);
	}

	iterator begin() const
	{
		return stored_list.begin();
	}

	iterator end() const
	{
		return stored_list.end();
	}

	int size() const
	{
		return stored_list.size();
	}

	int max_size() const
	{
		return capacity;
	}

	bool operator == (const cbuff& buff) const
	{
		return stored_list == buff.stored_list;
	}

	bool operator != (const cbuff& buff) const
	{
		return stored_list != buff.stored_list;
	}

	bool operator < (const cbuff& buff) const
	{
		return stored_list < buff.stored_list;
	}

	bool operator <= (const cbuff& buff) const
	{
		return stored_list <= buff.stored_list;
	}

	bool operator > (const cbuff& buff) const
	{
		return stored_list > buff.stored_list;
	}

	bool operator >= (const cbuff& buff) const
	{
		return stored_list >= buff.stored_list;
	}

	cbuff merge_sort(const cbuff& buff)
	{
		return stored_list.merge_sort(buff.stored_list);
	}

	std::pair<T, T> erase_min_max()
	{
		return stored_list.erase_min_max();
	}

	friend std::ostream& operator << (std::ostream& out, const cbuff& buff)
	{
		out << buff.stored_list;
		return out;
	}
};

#endif