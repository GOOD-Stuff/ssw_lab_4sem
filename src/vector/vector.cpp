#include "Vector.h"

Vector::Vector() {
	arr = nullptr;
	size = 0;
}

Vector::Vector(const Vector& vector)
{
	*this = vector;
}

Vector::~Vector() {
	if (arr)
		delete[] arr;
}
void Vector::push_back(int value)
{
	insert(value, size);
}
void Vector::push_front(int value)
{
	insert(value, 0);
}

void Vector::insert(int value, int index )
{
	int* arr_new = new int[++size];
	
	for (int i = 0; i < index ; i++)
	{
		arr_new[i] = arr[i];
	}
	
	arr_new[index] = value;

	for (int i = index + 1; i < size; i++)
	{
		arr_new[i] = arr[i - 1];

	}

	delete[] arr;
	arr = arr_new;
}

std::ostream& operator<<(std::ostream& stream, const Vector& vector)
{
	for (int i = 0; i < vector.size; i++) 
	{
		stream << vector.arr[i] << "\n";
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
	int* arr_new = new int[size - 1];
	int t = 0;

	for (int i = 0; i < size; i++)
	{
		if (i != index)
			arr_new[t++] = arr[i];

	}
	delete[] arr;
	arr = arr_new;
	size--;
}

int Vector::count()
{
	return size;
}

int& Vector::at(int index)
{
	return arr[index];
}

float Vector::get_arithmetic_mean()
{
	float sum = 0.0f;

	for (int i = 0; i < size; i++)
	{
		sum += arr[i];
	}

	return sum / size;
}

Vector Vector::concat_sort(const Vector& vector)
{
	Vector new_vector;
	
	new_vector.size = size + vector.size;
	new_vector.arr = new int[new_vector.size];

	int j = 0;

	for (int i = 0; i < size; i++)
	{
		new_vector.arr[j++] = arr[i];
	}

	for (int i = 0; i < vector.size; i++)
	{
		new_vector.arr[j++] = vector.arr[i];
	}

	for (int i = 0; i < new_vector.size; i++) {
		for (int j = 0; j < new_vector.size - 1; j++) {
			if (new_vector.arr[j] > new_vector.arr[j + 1]) {
				int temp = new_vector.arr[j];
				new_vector.arr[j] = new_vector.arr[j + 1];
				new_vector.arr[j + 1] = temp;
			}
		}
	}

	return new_vector;
}

Vector& Vector::operator = (const Vector& vector)
{
	if (arr)
		delete[] arr;

	size = vector.size;
	arr = new int[size];

	for (int i = 0; i < size; i++)
	{
		arr[i] = vector.arr[i];
	}

	return *this;
}

bool Vector::operator ==  (const Vector& right)
{
	if (size != right.size)
		return false;
	
	for (int i = 0; i < size; i++)
	{
		if (arr[i] != right.arr[i])
			return false;
	}

	return true;
}
bool Vector::operator != ( const Vector& right)
{
	return !(*this == right);
}
bool Vector::operator < ( const Vector& right) 
{
	
	int res_size = (size < right.size) ? size : right.size;
	for (int i = 0; i < res_size; i++)
	{
		if (arr[i] >= right.arr[i])
			return false;
	}
	return true;
}
bool Vector::operator > ( const Vector& right)
{
	return !(*this < right) && *this != right;
}
bool Vector::operator <= ( const Vector& right) 
{
	return (*this == right) || (*this < right);
}
bool Vector::operator >= ( const Vector& right)
{
	return (*this > right) || (*this == right);
}