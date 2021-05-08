#ifndef CLASS_VECTOR_H
#define CLASS_VECTOR_H

#include <ostream>

template <typename T>
class Vector
{
private:
	/**
	* @brief Array for storing stack elements
	*/
	T* arr;

	/**
	* @brief Stack size
	*/
	int size;

	/**
	* @brief Cell reserve that is added on overflow
	*/
	static constexpr int ADDITION = 4096;

public:

	/**
	* @brief Vector constructor
	*/
	Vector();

	/**
	* @brief Copy constructor
	*/
	Vector(const Vector<T>& vector);

	/**
	* @brief Deconstructor
	*/
	~Vector();

	/**
	* @brief Add item to the end
	*/
	void push_back(T data);

	/**
	* @brief Delete the last item
	*/
	void pop_back();

	/**
	* @brief Get a reference to an element by its index
	*/
	T& at(int index);

	/**
	* @brief To find out the number of elements in a vector
	*/
	int count() const;

	/**
	* @brief Clear vector
	*/
	void clear();

	/**
	* @brief Arithmetic mean of all elements
	*/
	float get_arithmetic_mean();

	/**
	* @brief Sorted concatenation with another vector
	*/
	Vector concat_sort(const Vector& vector);

	/**
	* @brief Assignment operator
	*/
	Vector& operator = (const Vector& vector);

	/**
	* @brief  Comparison operators
	*/
	bool operator == (const Vector<T>& vector) const;
	bool operator != (const Vector<T>& vector) const;
	bool operator < (const Vector<T>& vector) const;
	bool operator > (const Vector<T>& vector) const;
	bool operator <= (const Vector<T>& vector) const;
	bool operator >= (const Vector<T>& vector) const;

	/**
	* @brief Output operator
	*/
	friend std::ostream& operator << (std::ostream& stream, const Vector& vector)
	{
		for (int i = 0; i < vector.size; i++)
		{
			stream << vector.arr[i] << "\n";
		}

		return stream;
	}
};

template <typename T>
Vector<T>::Vector()
{
	arr = nullptr;
	size = 0;
}

template <typename T>
Vector<T>::Vector(const Vector<T>& vector)
{
	*this = vector;
}

template <typename T>
Vector<T>::~Vector()
{
	clear();
}

template <typename T>
void Vector<T>::push_back(T data)
{
	if (size % ADDITION == 0)
	{
		T* new_arr = new T[size + ADDITION];

		for (int i = 0; i < size; i++)
		{
			new_arr[i] = arr[i];
		}

		new_arr[size] = data;

		if (arr != nullptr)
		{
			delete[] arr;
		}

		arr = new_arr;
	}
	else
	{
		arr[size] = data;
	}

	size++;
}

template <typename T>
void Vector<T>::pop_back()
{
	if (size == 0)
	{
		throw std::runtime_error("Vector is empty!");
	}

	size--;

	if (size % ADDITION)
	{
		T* new_arr = new T[size];

		for (int i = 0; i < size; i++)
		{
			new_arr[i] = arr[i];
		}

		if (arr != nullptr)
		{
			delete[] arr;
		}

		arr = new_arr;
	}
}

template <typename T>
T& Vector<T>::at(int index)
{
	if (size == 0)
	{
		throw std::runtime_error("Vector is empty!");
	}

	if (index < 0 || index > size)
	{
		throw std::runtime_error("You have gone beyond boundary of vector!");
	}

	return arr[index];
}

template <typename T>
int Vector<T>::count() const
{
	return size;
}

template <typename T>
void Vector<T>::clear()
{
	if (arr != nullptr)
	{
		delete[] arr;
		arr = nullptr;
		size = 0;
	}
}

template <typename T>
float Vector<T>::get_arithmetic_mean()
{
	if (size == 0)
	{
		throw std::runtime_error("Vector is empty!");
	}

	float result = 0.0f;

	for (int i = 0; i < size; i++)
	{
		result += arr[i];
	}

	return result / size;
}

template <typename T>
Vector<T> Vector<T>::concat_sort(const Vector<T>& vector)
{
	if (size == 0 || vector.size == 0)
	{
		throw std::runtime_error("One or both vectors are empty!");
	}

	Vector<T> new_vector;

	new_vector.size = size + vector.size;
	new_vector.arr = new T[new_vector.size];

	for (int i = 0; i < new_vector.size; i++)
	{
		new_vector.arr[i] = (i < size) ? arr[i] : vector.arr[i - size];
	}

	for (int i = 0; i < new_vector.size; i++)
	{
		for (int j = 0; j < new_vector.size - 1; j++)
		{
			if (new_vector.arr[j] > new_vector.arr[j + 1])
			{
				std::swap(new_vector.arr[j], new_vector.arr[j + 1]);
			}
		}
	}

	return new_vector;
}

template <typename T>
Vector<T>& Vector<T>::operator = (const Vector<T>& vector)
{
	if (&vector == this)
	{
		return *this;
	}

	clear();

	size = vector.size;
	arr = new T[size];

	for (int i = 0; i < size; i++)
	{
		arr[i] = vector.arr[i];
	}
}

template <typename T>
bool Vector<T>::operator == (const Vector<T>& vector) const
{
	if (&vector == this)
	{
		return true;
	}

	if (size != vector.size)
	{
		return false;
	}

	for (int i = 0; i < size; i++)
	{
		if (arr[i] != vector.arr[i])
		{
			return false;
		}
	}

	return true;
}

template <typename T>
bool Vector<T>::operator != (const Vector<T>& vector) const
{
	return !(*this == vector);
}

template <typename T>
bool Vector<T>::operator < (const Vector<T>& vector) const
{
	if (&vector == this)
	{
		return false;
	}

	int min_size = (size < vector.size) ? size : vector.size;

	for (int i = 0; i < min_size; i++)
	{
		if (arr[i] != vector.arr[i])
		{
			return arr[i] < vector.arr[i];
		}
	}

	return size < vector.size;
}

template <typename T>
bool Vector<T>::operator > (const Vector<T>& vector) const
{
	return !(*this < vector) && (*this != vector);
}

template <typename T>
bool Vector<T>::operator <= (const Vector<T>& vector) const
{
	return (*this < vector) || (*this == vector);
}

template <typename T>
bool Vector<T>::operator >= (const Vector<T>& vector) const
{
	return (*this > vector) || (*this == vector);
}

#endif