#ifndef CLASS_CIRCULAR_BUFFER_INCLUDED_H
#define CLASS_CIRCULAR_BUFFER_INCLUDED_H

#include "list.h"

template <class T>
class circular_buffer
{
private:
	list<T> buffer;
	int capacity {0};

	circular_buffer(list<T>&& lst)
	{
		buffer = lst;
	}

public:
	using iterator = typename list<T>::iterator;

	circular_buffer(const std::initializer_list<T>& list)
	{
		for (auto& value : list)
		{
			buffer.push_back(value);
		}
	}

	void push(T value)
	{
		if (buffer.count() == capacity)
		{
			buffer.pop_front();
		}
		
		buffer.push_back(value);
	}

	void pop()
	{
		buffer.pop_front();
	}

	void insert(iterator it, T value)
	{
		bool check_is_start = it == begin();

		buffer.insert(it, value);

		if (buffer.count() > capacity)
		{
			if (check_is_start)
			{
				buffer.erase(begin() + 1);
			}
			else
			{
				buffer.pop_front();
			}
		}
	}

	void erase(iterator it)
	{
		buffer.erase(it);
	}

	iterator begin() const
	{
		return buffer.begin();
	}

	iterator end() const
	{
		return buffer.end();
	}

	int count() const
	{
		return buffer.size();
	}

	int max_count() const
	{
		return capacity;
	}

	bool cyclic_include(const circular_buffer<T>& cbuffer) const
	{
		return buffer.cyclic_include(cbuffer.buffer);
	}

	circular_buffer<T> merge_sort(const circular_buffer<T>& cbuffer) const
	{
		return buffer.merge_sort(cbuffer.buffer);
	}

	bool operator == (const circular_buffer<T>& cbuffer) const
	{
		return buffer == cbuffer.buffer;
	}

	bool operator != (const circular_buffer<T>& cbuffer) const
	{
		return buffer != cbuffer.buffer;
	}

	bool operator < (const circular_buffer<T>& cbuffer) const
	{
		return buffer < cbuffer.buffer;
	}

	bool operator > (const circular_buffer<T>& cbuffer) const
	{
		return buffer > cbuffer.buffer;
	}

	bool operator <= (const circular_buffer<T>& cbuffer) const
	{
		return buffer <= cbuffer.buffer;
	}

	bool operator >= (const circular_buffer<T>& cbuffer) const
	{
		return buffer >= cbuffer.buffer;
	}

	friend std::ostream& operator << (std::ostream& out, const circular_buffer<T>& cbuffer)
	{
		out << cbuffer.buffer;
		return out;
	}
};

#endif