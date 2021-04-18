#include "Vector.h"
#include <cmath>

Vector::Vector()
{
	arr_data = nullptr;
	size = 0;
}

Vector::~Vector()
{
	if (arr_data)
		delete[] arr_data;
}

void Vector::push_back(int value)
{
	insert(value, size);
}

void Vector::push_front(int value)
{
	insert(value, 0);
}

void Vector::insert(int value, int index)
{
	int* new_arr_data = new int[++size];
	
	for (int i = 0; i < index; i++)
	{
		new_arr_data[i] = arr_data[i];
	}
	
	new_arr_data[index] = value;

	for (int i = index + 1; i < size; i++)
	{
		new_arr_data[i] = arr_data[i - 1];
	}

	delete[] arr_data;
	arr_data = new_arr_data;	
}

std::ostream& operator << (std::ostream& stream, const Vector& vector)
{
	for (int i = 0; i < vector.size; i++)
	{
		stream << vector.arr_data[i] << "\n";
	}

	return stream;
}

void Vector::pop_back()
{
	erase(size - 1);
}

void Vector::pop_front()
{
	erase(0);
}

void Vector::erase(int index)
{
	int* new_array_data = new int[size - 1];
	int j = 0;

	for (int i = 0; i < size; i++)
	{
		if (i != index)
			new_array_data[j++] = arr_data[i];
	}

	delete[] arr_data;
	arr_data = new_array_data;
	size--;
}

int Vector::count()
{
	return size;
}

int& Vector::at(int index)
{
	return arr_data[index];
}

int Vector::get_all_sum()
{
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += arr_data[i];
	}

	return sum;
}

int Vector::concat()
{

	auto concut_numbers = [](int a, int b)
	{
		a = abs(a);
		b = abs(b);

		for (int i = b; i != 0; i /= 10)
			a *= 10;
		a += b;
		return a;
	};

	int result_conc = arr_data[0];
	for (int i = 1; i < size; i++)
	{
		result_conc = concut_numbers(result_conc, arr_data[i]);
	}

	return result_conc;
}

bool Vector::operator == (const Vector& right)
{
	if (size != right.size)
		return false;

	for (int i = 0; i < size; i++)
	{
		if (arr_data[i] != right.arr_data[i])
			return false;
	}

	return true;
}

bool Vector::operator != (const Vector& right)
{
	return !(*this == right);
}

bool Vector::operator < (const Vector& right)
{
	int result_size = (size < right.size) ? size : right.size;

	for (int i = 0; i < result_size; i++)
		if (arr_data[i] < right.arr_data[i])
			return true;
		
	return false;
}

bool Vector::operator > (const Vector& right)
{
	return !(*this < right) && (*this != right);
}

bool Vector::operator <= (const Vector& right)
{
	return (*this < right) || (*this == right);
}

bool Vector::operator >= (const Vector& right)
{
	return (*this > right) || (*this == right);
}

