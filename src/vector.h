#ifndef CLASS_VECTOR_INCLUDED_H
#define CLASS_VECTOR_INCLUDED_H

#include <ostream>
#include <stdexcept>

template <typename T>
class vector
{
protected:
	T* data {nullptr};

	int count {0};
	static constexpr int OVERFLOW_ADDITION {4096};

public:
	virtual ~vector()
	{
		clear();
	}

	void push(T element)
	{
		if (count % OVERFLOW_ADDITION == 0) {
			T* extended_data = new T[count + OVERFLOW_ADDITION];
			memcpy(extended_data, data, count * sizeof(T));

			if (data != nullptr) {
				delete[] data;
			}

			data = extended_data;
		}

		data[count++] = element;
	}

	void pop()
	{
		if (count == 0) {
			throw std::underflow_error("vector is empty!");
		}

		if (--count % OVERFLOW_ADDITION == 0) {
			T* extended_data = new T[count];
			memcpy(extended_data, data, count * sizeof(T));

			if (data != nullptr) {
				delete[] data;
			}

			data = extended_data;
		}
	}

	T& peek() const
	{
		if (count == 0) {
			throw std::underflow_error("vector is empty!");
		}

		return data[count - 1];
	}

	T& at(int index) const
	{
		if (count == 0) {
			throw std::underflow_error("vector is empty!");
		}

		if (index < 0 || index >= count) {
			throw std::out_of_range("index out of range!");
		}

		return data[index];
	}

	int size() const
	{
		return count;
	}

	void reverse()
	{
		for (int i = 0; i < count / 2; i++) {
			std::swap(data[i], data[count - i - 1]);
		}
	}

	void exclude_in_range(int min, int max)
	{
		if (count == 0) {
			throw std::runtime_error("vector is empty!");
		}

		if (min > max) {
			std::swap(min, max);
		}

		int marked_count = 0;

		for (int i = 0; i < count; i++) {
			if (data[i] >= min && data[i] <= max) {
				marked_count++;
			}
		}

		if (marked_count == 0) {
			return;
		}

		T* cleaned_data = new T[count - marked_count];
		int add_position = 0;

		for (int i = 0; i < count; i++) {
			if (data[i] < min || data[i] > max) {
				cleaned_data[add_position++] = data[i];
			}
		}

		if (data != nullptr) {
			delete[] data;
		}

		count -= marked_count;
		data = cleaned_data;
	}

	void clear()
	{
		if (data != nullptr) {
			delete[] data;
			count = 0;
		}
	}

	bool operator == (const vector<T>& vc) const
	{
		if (this == std::addressof(vc)) {
			return true;
		}

		if (count != vc.count) {
			return false;
		}

		return memcmp(data, vc.data, count * sizeof(T)) == 0;
	}

	bool operator != (const vector<T>& vc) const
	{
		return !(*this == vc);
	}

	bool operator < (const vector<T>& vc) const
	{
		if (this == std::addressof(vc)) {
			return false;
		}

		bool current_is_less = count < vc.count;
		int min_count = current_is_less ? count : vc.count;

		for (int i = 0; i < min_count; i++) {
			if (data[i] != vc.data[i]) {
				return data[i] < vc.data[i];
			}
		}

		return current_is_less;
	}

	bool operator <= (const vector<T>& vc) const
	{
		return *this < vc || *this == vc;
	}

	bool operator > (const vector<T>& vc) const
	{
		return !(*this < vc) && *this != vc;
	}

	bool operator >= (const vector<T>& vc) const
	{
		return *this > vc || *this == vc;
	}

	friend std::ostream& operator << (std::ostream& out, const vector<T>& vc)
	{
		for (int i = 0; i < vc.count; i++) {
			out << vc.data[i] << "\n";
		}
		
		return out;
	}
};

#endif