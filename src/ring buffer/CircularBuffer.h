#ifndef CIRCULAR_BUFFER_INCLUDED_H
#define CIRCULAR_BUFFER_INCLUDED_H

#include <ostream>
#include <stdexcept>
#include <initializer_list>

template <class T>
class CircularBuffer
{
private:
	class iterator;
	friend class iterator;
	
	struct Node
	{
		T data;

		Node* prev {nullptr};
		Node* next {nullptr};

		Node() = default;
		Node(T value) : data(value) {}
	};

	using PNode = Node*;
	using PBuffer = CircularBuffer<T>*;
	
	int current_size {0};
	int max_size {0};

	Node* head {nullptr};
	Node* tail {nullptr};

public:
	explicit CircularBuffer(int size)
	{
		if (size == 0)
		{
			throw std::invalid_argument("The size must be greater than zero!");
		}

		max_size = size;
	}

	CircularBuffer(const std::initializer_list<T> list) : CircularBuffer(list.size())
	{
		for (auto el : list)
		{
			push(el);
		}
	}

	void push(T data)
	{
		PNode node = new Node(data);

		if (current_size++ == 0)
		{
			head = tail = node;
			return;
		}
		
		tail->next = node;
		node->prev = tail;
		tail = node;

		if (current_size > max_size)
		{
			pop();
		}
	}

	void pop()
	{
		if (current_size == 0)
		{
			throw std::runtime_error("Circular buffer is empty!");
		}

		PNode old_head = head;

		head = head->next;
		delete old_head;
		
		current_size--;
	}

	void insert(iterator it, T data)
	{
		if (it == end())
		{
			return push(data);
		}

		bool is_begin = it == begin();
		
		if (is_begin && current_size == max_size)
		{
			it++;
			erase(begin());
		}
		
		PNode prev_node = it.current_node->prev;
		PNode new_node = new Node(data);

		if (prev_node != nullptr)
		{
			prev_node->next = new_node;
		}
		
		new_node->prev = prev_node;
		new_node->next = it.current_node;

		if (is_begin)
		{
			head = new_node;
		}

		if (++current_size > max_size)
		{
			pop();
		}
	}

	void erase(iterator it)
	{
		if (current_size == 0)
		{
			throw std::runtime_error("Circular buffer is empty!");
		}
		
		if (it == begin())
		{
			return pop();
		}

		it.iterator_overflow_control();
		
		bool is_end = it == --end();

		PNode prev_node = it.current_node->prev;
		PNode next_node = it.current_node->next;

		delete it.current_node;

		if (prev_node != nullptr)
		{
			prev_node->next = next_node;
		}

		if (next_node != nullptr)
		{
			next_node->prev = prev_node;
		}

		if (is_end)
		{
			tail = prev_node;
		}

		current_size--;
	}

	int count() const
	{
		return current_size;
	}

	int max_count() const
	{
		return max_size;
	}

	iterator begin() const
	{
		return iterator(const_cast<PBuffer>(this), head);
	}

	iterator end() const
	{
		return iterator(const_cast<PBuffer>(this), nullptr);
	}

	iterator find(T data) const
	{
		if (current_size == 0)
		{
			throw std::runtime_error("Circular buffer is empty!");
		}
		
		iterator it = begin();

		while (it != end() && *it != data)
		{
			it++;
		}

		return it;
	}

	bool operator == (const CircularBuffer<T>& buffer) const
	{
		if (this == std::addressof(buffer))
		{
			return true;
		}

		if (current_size != buffer.current_size)
		{
			return false;
		}

		iterator it_first = begin();
		iterator it_second = buffer.begin();

		while (it_first != end())
		{
			if (*it_first++ != *it_second++)
			{
				return false;
			}
		}
		
		return true;
	}

	bool operator != (const CircularBuffer<T>& buffer) const
	{
		return !(*this == buffer);
	}

	bool operator < (const CircularBuffer<T>& buffer) const
	{
		if (this == std::addressof(buffer))
		{
			return false;
		}

		iterator it_first = begin();
		iterator it_second = buffer.begin();

		while (it_first != end() && it_second != buffer.end())
		{
			T& first_data = *it_first++;
			T& second_data = *it_second++;
			
			if (first_data != second_data)
			{
				return first_data < second_data;
			}
		}

		return current_size < buffer.current_size;
	}

	bool operator > (const CircularBuffer<T>& buffer) const
	{
		return !(*this < buffer) && *this != buffer;
	}

	bool operator <= (const CircularBuffer<T>& buffer) const
	{
		return *this < buffer || *this == buffer;
	}

	bool operator >= (const CircularBuffer<T>& buffer) const
	{
		return *this > buffer || *this == buffer;
	}


	class iterator
	{
	private:
		friend class CircularBuffer<T>;
		
		PBuffer buffer {nullptr};
		PNode current_node {nullptr};
		
		iterator(const PBuffer target_buffer, const PNode node): buffer(target_buffer), current_node(node) {}

		void iterator_empty_control() const
		{
			if (buffer == nullptr)
			{
				throw std::runtime_error("Trying to work with empty iterator!");
			}
		}

		void iterator_overflow_control() const
		{
			if (current_node == nullptr)
			{
				throw std::out_of_range("Going beyond the right buffer boundary!");
			}
		}

		void iterator_underflow_control() const
		{
			if (current_node == buffer->head)
			{
				throw std::out_of_range("Going beyond the left buffer boundary!");
			}
		}
		
	public:
		iterator() = default;

		iterator& operator ++ ()
		{
			iterator_empty_control();
			iterator_overflow_control();
			
			current_node = current_node->next;
			return *this;
		}

		iterator operator ++ (int)
		{
			iterator_empty_control();
			iterator_overflow_control();
			
			PNode old_node = current_node;
			current_node = current_node->next;
			return iterator(buffer, old_node);
		}

		iterator operator + (int offset)
		{
			iterator it = *this;

			for (int i = 0; i < offset; i++)
			{
				++it;
			}

			return it;
		}

		iterator& operator -- ()
		{
			iterator_empty_control();
			iterator_underflow_control();

			if (current_node == nullptr)
			{
				*this = iterator(buffer, buffer->tail);
				return *this;
			}
			
			current_node = current_node->prev;
			return *this;
		}

		iterator operator -- (int)
		{
			iterator_empty_control();
			iterator_underflow_control();

			if (current_node == nullptr)
			{
				return iterator(buffer, buffer->tail);
			}
			
			PNode old_node = current_node;
			current_node = current_node->prev;
			return iterator(buffer, old_node);
		}

		iterator operator - (int offset)
		{
			iterator it = *this;

			for (int i = 0; i < offset; i++)
			{
				--it;
			}

			return it;
		}

		T& operator * () const
		{
			iterator_empty_control();
			return current_node->data;
		}

		bool operator == (const iterator& it) const
		{
			return current_node == it.current_node;
		}

		bool operator != (const iterator& it) const
		{
			return !(*this == it);
		}
	};
};

template <class T>
std::ostream& operator << (std::ostream& stream, const CircularBuffer<T>& buffer)
{
	for (auto& el : buffer)
	{
		stream << el << "\n";
	}

	return stream;
}

#endif