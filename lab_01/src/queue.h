#ifndef CLASS_QUEUE_INCLUDED_H
#define CLASS_QUEUE_INCLUDED_H

#include <ostream>
#include <stdexcept>

template <typename T>
class queue
{
private:
	T* data {nullptr};

	int count {0};
	
	int begin_idx {0};
	int capacity {0};
	
	static constexpr int OVERFLOW_ADDITION {4096};

public:
	~queue()
	{
		clear();
	}

	void push(T element)
	{
		if (count % OVERFLOW_ADDITION == 0) {
			capacity += OVERFLOW_ADDITION;
			
			T* extended_data = new T[capacity];
			memcpy(extended_data, data + begin_idx, count * sizeof(T));

			extended_data[count++] = element;

			if (data != nullptr) {
				delete[] data;
			}

			begin_idx = 0;
			data = extended_data;
		} else {
			data[begin_idx + count++] = element;
		}
	}

	void pop()
	{
		if (count == 0) {
			throw std::runtime_error("queue is empty!");
		}

		count--;
		begin_idx++;

		if (begin_idx >= OVERFLOW_ADDITION || count % OVERFLOW_ADDITION == 0) {
			capacity -= OVERFLOW_ADDITION;

			T* extended_data = new T[capacity];
			memcpy(extended_data, data + begin_idx, count * sizeof(T));

			if (data != nullptr) {
				delete[] data;
			}

			begin_idx = 0;
			data = extended_data;
		}
	}

	T& peek() const
	{
		if (count == 0) {
			throw std::runtime_error("queue is empty!");
		}

		return data[begin_idx + count - 1];
	}

	int size() const
	{
		return count;
	}

	void reverse()
	{
		for (int i = 0; i < count / 2; i++) {
			std::swap(data[begin_idx + i], data[begin_idx + count - i - 1]);
		}
	}

	void exclude_in_range(int min, int max)
	{
		if (count == 0) {
			throw std::runtime_error("queue is empty!");
		}

		if (min > max) {
			std::swap(min, max);
		}

		int marked_count = 0;

		for (int i = begin_idx; i < begin_idx + count; i++) {
			if (data[i] >= min && data[i] <= max) {
				marked_count++;
			}
		}

		if (marked_count == 0) {
			return;
		}

		T* cleaned_data = new T[count - marked_count];
		int add_position = 0;

		for (int i = begin_idx; i < begin_idx + count; i++) {
			if (data[i] < min || data[i] > max) {
				cleaned_data[add_position++] = data[i];
			}
		}

		if (data != nullptr) {
			delete[] data;
		}

		count -= marked_count;
		data = cleaned_data;
		begin_idx = 0;
	}

	void clear()
	{
		if (data != nullptr) {
			delete[] data;
			count = 0;
		}
	}

	bool operator == (const queue<T>& q) const
	{
		if (this == std::addressof(q)) {
			return true;
		}

		if (count != q.count) {
			return false;
		}

		return memcmp(data + begin_idx, q.data + q.begin_idx, count * sizeof(T)) == 0;
	}

	bool operator != (const queue<T>& q) const
	{
		return !(*this == q);
	}

	bool operator < (const queue<T>& q) const
	{
		if (this == std::addressof(q)) {
			return false;
		}

		bool current_is_less = count < q.count;
		int min_count = current_is_less ? count : q.count;

		int first_begin = begin_idx;
		int second_begin = q.begin_idx;
		
		for (int i = 0; i < min_count; i++) {
			T& first_element = data[first_begin++];
			T& second_element = q.data[second_begin++];
			
			if (first_element != second_element) {
				return first_element < second_element;
			}
		}

		return current_is_less;
	}

	bool operator <= (const queue<T>& q) const
	{
		return *this < q || *this == q;
	}

	bool operator > (const queue<T>& q) const
	{
		return !(*this < q) && *this != q;
	}

	bool operator >= (const queue<T>& q) const
	{
		return *this > q || *this == q;
	}

	friend std::ostream& operator << (std::ostream& out, const queue<T>& q)
	{
		for (int i = q.begin_idx; i < q.begin_idx + q.count; i++) {
			out << q.data[i] << "\n";
		}

		return out;
	}
};

#endif