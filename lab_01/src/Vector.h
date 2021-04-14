#ifndef CLASS_VECTOR_H
#define CLASS_VECTOR_H

#include <ostream>

template <typename T>
class Vector
{
private:
	T* storage;   // Pointer to array with vector data
	size_t count; // Count of elements in the vector;

private:
	void delete_storage();
	void replace_storage(T*& new_data);

public:
	Vector();
	~Vector();

	T& front();          // Get first element
	T& back();           // Get last element
	T& at(size_t index); // Get item by index

	void push_front(T value);           // Insert element to front
	void push_back(T value);            // Insert element to back
	void insert(size_t index, T value); // Insert element by index

	void pop_front(); // Remove first element
	void pop_back();  // Remove last element

	void erase(size_t index);                         // Remove element by index
	void erase(size_t start_index, size_t end_index); // Remove elements in range

	void reverse(); // Reverse order of elements

	size_t size() const; // Get stack size
	bool empty() const;  // Vector is empty? 

	void clear(); // Remove all elements from vector
	
	T& operator[](size_t index); // Access operator

	// Operator for output all vector elements
	friend std::ostream& operator<<(std::ostream& out, const Vector<T>& vector)
	{
		for (size_t i = 0; i < vector.size(); i++)
			out << vector.storage[i] << "\n";

		return out;
	}
};

template <typename T>
Vector<T>::Vector()
{
	storage = nullptr;
	count = 0;
}

template <typename T>
Vector<T>::~Vector()
{
	clear();
}

template <typename T>
T& Vector<T>::front()
{
	return storage[0];
}

template <typename T>
T& Vector<T>::back()
{
	return storage[count - 1];
}

template <typename T>
T& Vector<T>::at(size_t index)
{
	return storage[index];
}

template <typename T>
void Vector<T>::push_front(T value)
{
	insert(0, value);
}

template <typename T>
void Vector<T>::push_back(T value)
{
	insert(count, value);
}

template <typename T>
void Vector<T>::insert(size_t index, T value)
{
	T* new_data = new T[++count];

	for (size_t i = 0; i < index; i++)
		new_data[i] = storage[i];

	new_data[index] = value;

	for (size_t i = index + 1; i < count; i++)
		new_data[i] = storage[i - 1];

	replace_storage(new_data);
}

template <typename T>
void Vector<T>::pop_front()
{
	erase(0);
}

template <typename T>
void Vector<T>::pop_back()
{
	erase(count - 1);
}

template <typename T>
void Vector<T>::erase(size_t index)
{
	erase(index, index);
}

template <typename T>
void Vector<T>::erase(size_t start_index, size_t end_index)
{
	size_t exclude_count = end_index - start_index + 1;
	T* new_data = new T[count - exclude_count];

	size_t current_idx = 0;
	for (size_t i = 0; i < count; i++)
	{
		if (i >= start_index && i <= end_index)
			continue;

		new_data[current_idx++] = storage[i];
	}

	replace_storage(new_data);
	count -= exclude_count;
}

template <typename T>
void Vector<T>::reverse()
{
	for (int i = 0; i < count / 2; i++)
		std::swap(storage[i], storage[count - i - 1]);
}

template <typename T>
size_t Vector<T>::size() const
{
	return count;
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

#endif