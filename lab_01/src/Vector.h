#pragma once
#include <ostream>

template <typename T>
class Vector
{
private:
	T* data;
	int count;

private:
	void delete_storage();
	void replace_storage(T*& new_data);

public:
	Vector();
	~Vector();

	T& front();
	T& back();
	T& at(int index);

	void push_front(T value);
	void push_back(T value);
	void insert(int index, T value);

	void pop_front();
	void pop_back();
	void erase(int index);
	void erase(int start_index, int end_index);

	void reverse();

	int size() const;
	bool empty() const;

	void clear();

	friend std::ostream& operator<<(std::ostream& out, const Vector<T>& vector)
	{
		for (int i = 0; i < vector.size(); i++)
			out << vector.data[i] << "\n";

		return out;
	}
};

template <typename T>
Vector<T>::Vector()
{
	data = nullptr;
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
	return data[0];
}

template <typename T>
T& Vector<T>::back()
{
	return data[count - 1];
}

template <typename T>
T& Vector<T>::at(int index)
{
	return data[index];
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
void Vector<T>::insert(int index, T value)
{
	T* new_data = new T[++count];

	for (int i = 0; i < index; i++)
		new_data[i] = data[i];

	new_data[index] = value;

	for (int i = index + 1; i < count; i++)
		new_data[i] = data[i - 1];

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
void Vector<T>::erase(int index)
{
	erase(index, index);
}

template <typename T>
void Vector<T>::erase(int start_index, int end_index)
{
	int exclude_count = end_index - start_index + 1;
	T* new_data = new T[count - exclude_count];

	int current_idx = 0;
	for (int i = 0; i < count; i++)
	{
		if (i >= start_index && i <= end_index)
			continue;

		new_data[current_idx++] = data[i];
	}

	replace_storage(new_data);
	count -= exclude_count;
}

template <typename T>
void Vector<T>::reverse()
{
	for (int i = 0; i < count / 2; i++)
		std::swap(data[i], data[count - i - 1]);
}

template <typename T>
int Vector<T>::size() const
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

template <typename _T>
std::ostream& operator<<(std::ostream& out, const Vector<_T>& vector)
{
	for (int i = 0; i < vector.size(); i++)
		out << vector.data[i] << "\n";

	return out;
}

template <typename T>
void Vector<T>::delete_storage()
{
	if (data == nullptr)
		return;

	delete[] data;
	data = nullptr;
}

template <typename T>
void Vector<T>::replace_storage(T*& new_data)
{
	delete_storage();
	data = new_data;
}