#ifndef CLASS_VECTOR_H
#define CLASS_VECTOR_H

#include <ostream>

template <typename T>
class Vector
{
private:
	T* storage {nullptr};   // Pointer to array with vector data
	size_t count {0};       // Count of elements in the vector;

	size_t start_index {0}; // Start vector index
	size_t end_index {0};   // End vector index
	size_t real_size {0};   // Real vector size (capacity)

	static constexpr size_t reserve {16384}; // Reserve cells count (half - left, half - right)


	void delete_storage();									   // Clear memory allocated for vector
	void replace_storage(T*& new_data);						   // Replace vector storage 
	void throw_if(bool expression, const char* message) const; // For exceptions

	void push_front(T value); // Insert element to front
	void pop_front();         // Remove first element

public:
	Vector() = default;
	~Vector();

	T& front();          // Get first element
	T& back();           // Get last element
	T& at(size_t index); // Get item by index

	void push_back(T value);            // Insert element to back
	void insert(size_t index, T value); // Insert element by index

	void pop_back();  // Remove last element

	void erase(size_t index);                     // Remove element by index
	void erase(size_t start_idx, size_t end_idx); // Remove elements in range
	void erase_in_vrange(T start_value, T end_value); // Remove elements in values range

	void reverse(); // Reverse order of elements

	size_t size() const;     // Get vector size
	size_t capacity() const; // Get vector capacity
	bool empty() const;      // Vector is empty? 

	void clear(); // Remove all elements from vector

	T& operator[](size_t index); // Access operator

	// Lexicographic comparison operators begin

	bool operator==(const Vector<T>& vector) const;
	bool operator!=(const Vector<T>& vector) const;

	bool operator<(const Vector<T>& vector) const;
	bool operator>(const Vector<T>& vector) const;

	bool operator<=(const Vector<T>& vector) const;
	bool operator>=(const Vector<T>& vector) const;

	// Lexicographic comparison operators end

	// Noncopyable
	Vector(const Vector& stack) = delete;
	Vector& operator=(const Vector& vector) = delete;

	// Operator for output all vector elements
	friend std::ostream& operator<<(std::ostream& out, const Vector<T>& vector)
	{
		vector.throw_if(vector.empty(), "You are trying to display empty vector!");

		for (size_t i = vector.start_index; i < vector.end_index; i++)
			out << vector.storage[i] << "\n";

		return out;
	}
};

template <typename T>
Vector<T>::~Vector()
{
	clear();
}

template <typename T>
T& Vector<T>::front()
{
	throw_if(empty(), "You are trying to access first element of empty vector!");
	return storage[start_index];
}

template <typename T>
T& Vector<T>::back()
{
	throw_if(empty(), "You are trying to access last element of empty vector!");
	return storage[end_index - 1];
}

template <typename T>
T& Vector<T>::at(size_t index)
{
	throw_if(index >= count, "Attempt to access the allocated memory boundary!");
	return storage[start_index + index];
}

template <typename T>
void Vector<T>::push_front(T value)
{
	if (start_index != 0)
	{
		storage[--start_index] = value;
		count++;
		return;
	}

	real_size = count + reserve;
	T* new_storage = new T[real_size];

	size_t new_start_index = (real_size - count) / 2;
	size_t new_end_index = new_start_index + count;

	for (size_t i = new_start_index; i < new_end_index; i++)
		new_storage[i] = storage[start_index++];

	new_storage[--new_start_index] = value;

	start_index = new_start_index;
	end_index = new_end_index;

	count++;
	replace_storage(new_storage);
}

template <typename T>
void Vector<T>::push_back(T value)
{
	if (end_index != real_size)
	{
		storage[end_index++] = value;
		count++;
		return;
	}

	real_size = count + reserve;
	T* new_storage = new T[real_size];

	size_t new_start_index = (real_size - count) / 2;
	size_t new_end_index = new_start_index + count;

	for (size_t i = new_start_index; i < new_end_index; i++)
		new_storage[i] = storage[start_index++];

	new_storage[new_end_index++] = value;

	start_index = new_start_index;
	end_index = new_end_index;

	count++;
	replace_storage(new_storage);
}

template <typename T>
void Vector<T>::insert(size_t index, T value)
{
	throw_if(index > count, "Attempt to go beyond the boundaries of vector!");

	if (start_index + index == 0)
	{
		push_front(value);
		return;
	}
	else if (start_index + index == end_index)
	{
		push_back(value);
		return;
	}

	count++;

	if (end_index < real_size)
	{
		for (size_t i = end_index - 1; i >= index + start_index; i--)
			storage[i + 1] = storage[i];

		storage[index + start_index] = value;
		end_index++;
	}
	else
	{
		real_size = count + reserve;
		T* new_storage = new T[real_size];

		size_t new_start_index = (real_size - count) / 2;
		size_t new_end_index = new_start_index + count;

		for (size_t i = new_start_index; i < new_start_index + index; i++)
			new_storage[i] = storage[start_index++];

		new_storage[new_start_index + index] = value;

		for (size_t i = new_start_index + index + 1; i < new_end_index; i++)
			new_storage[i] = storage[start_index++];

		start_index = new_start_index;
		end_index = new_end_index;

		replace_storage(new_storage);
	}
}

template <typename T>
void Vector<T>::pop_front()
{
	throw_if(empty(), "You are trying to remove first element of empty vector!");
	
	count--;
	start_index++;

	if (start_index > reserve)
	{
		real_size = count + reserve;
		T* new_storage = new T[real_size];

		size_t new_start_index = (real_size - count) / 2;
		size_t new_end_index = new_start_index + count;

		for (size_t i = new_start_index; i < new_end_index; i++)
			new_storage[i] = storage[start_index++];

		start_index = new_start_index;
		end_index = new_end_index;

		replace_storage(new_storage);
	}
}

template <typename T>
void Vector<T>::pop_back()
{
	throw_if(empty(), "You are trying to remove first element of empty vector!");

	count--;
	end_index--;

	if (real_size - end_index > reserve)
	{
		real_size = count + reserve;
		T* new_storage = new T[real_size];

		size_t new_start_index = (real_size - count) / 2;
		size_t new_end_index = new_start_index + count;

		for (size_t i = new_start_index; i < new_end_index; i++)
			new_storage[i] = storage[start_index++];

		start_index = new_start_index;
		end_index = new_end_index;

		replace_storage(new_storage);
	}
}

template <typename T>
void Vector<T>::erase(size_t index)
{
	if (index == 0)
	{
		pop_front();
		return;
	}
	else if (index == count - 1)
	{
		pop_back();
		return;
	}

	erase(index, index);
}

template <typename T>
void Vector<T>::erase(size_t start_idx, size_t end_idx)
{
	throw_if(empty(), "You are trying to remove element of empty vector!");
	throw_if(start_idx >= count || end_idx >= count, "Attempt to access the allocated memory boundary!");
	throw_if(start_idx > end_idx, "Incorrect arguments!");

	if ((start_idx == 0 && end_idx == 0) || (start_idx == count - 1 && end_idx == count - 1))
	{
		erase(start_idx);
		return;
	}

	size_t delta_count = end_idx - start_idx + 1;
	count -= delta_count;

	real_size = count + reserve;
	T* new_storage = new T[real_size];

	size_t new_start_index = (real_size - count) / 2;
	size_t new_end_index = new_start_index + count;

	size_t j = new_start_index;
	size_t end = start_index + start_idx;

	for (size_t i = start_index; i < end; i++)
		new_storage[j++] = storage[start_index++];

	start_index += delta_count;

	for (size_t i = start_index; i < end_index; i++)
		new_storage[j++] = storage[start_index++];

	start_index = new_start_index;
	end_index = new_end_index;

	replace_storage(new_storage);
}

template <typename T>
void Vector<T>::erase_in_vrange(T start_value, T end_value)
{
	bool completed = false;
	
	while (!completed)
	{
		for (size_t i = start_index; i < end_index; i++)
		{
			if (storage[i] >= start_value && storage[i] <= end_value)
			{
				erase(i - start_index);
				break;
			}

			completed = true;
		}
	}
}

template <typename T>
void Vector<T>::reverse()
{
	throw_if(empty(), "You are trying to reverse empty vector!");

	size_t start = start_index;
	size_t end = end_index - 1;

	for (size_t i = 0; i < count / 2; i++)
		std::swap(storage[start++], storage[end--]);
}

template <typename T>
size_t Vector<T>::size() const
{
	return count;
}

template <typename T>
size_t Vector<T>::capacity() const
{
	return real_size;
}

template <typename T>
bool Vector<T>::empty() const
{
	return count == 0;
}

template <typename T>
void Vector<T>::clear()
{
	delete_storage();

	count = 0;
	real_size = 0;
	start_index = 0;
	end_index = 0;
}

template <typename T>
T& Vector<T>::operator[](size_t index)
{
	return at(index);
}

template <typename T>
bool Vector<T>::operator==(const Vector<T>& vector) const
{
	if (count != vector.count)
		return false;

	size_t this_begin = start_index;
	size_t vector_begin = vector.start_index;

	for (size_t i = 0; i < count; i++)
		if (storage[this_begin++] != vector.storage[vector_begin++])
			return false;

	return true;
}

template <typename T>
bool Vector<T>::operator!=(const Vector<T>& vector) const
{
	return !(*this == vector);
}

template <typename T>
bool Vector<T>::operator<(const Vector<T>& vector) const
{
	size_t min_count = count < vector.count ? count : vector.count;

	size_t this_begin = start_index;
	size_t vector_begin = vector.start_index;

	for (size_t i = 0; i < min_count; i++)
	{
		T& this_value = storage[this_begin++];
		T& vector_value = vector.storage[vector_begin++];

		if (this_value == vector_value)
			continue;

		return this_value < vector_value;
	}

	return count < vector.count;
}

template <typename T>
bool Vector<T>::operator>(const Vector<T>& vector) const
{
	return !(*this < vector) && *this != vector;
}

template <typename T>
bool Vector<T>::operator<=(const Vector<T>& vector) const
{
	return *this < vector || *this == vector;
}

template <typename T>
bool Vector<T>::operator>=(const Vector<T>& vector) const
{
	return *this > vector || *this == vector;
}

template <typename T>
void Vector<T>::delete_storage()
{
	if (storage == nullptr)
		return;

	delete[] storage;
	storage = nullptr;
}

template <typename T>
void Vector<T>::replace_storage(T*& new_data)
{
	delete_storage();
	storage = new_data;
}

template <typename T>
void Vector<T>::throw_if(bool expression, const char* message) const
{
	if (expression)
		throw std::runtime_error(message);
}

#endif