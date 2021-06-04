#include "Vector.h"

Vector::Vector()
{
	data = nullptr;
	size = 0;
}

Vector::~Vector()
{
	if (data != nullptr) {
		delete[] data;
		size = 0;
	}
}

void Vector::push(int number)
{
	if (size % supplement == 0) {
		int* updated_data = new int[size + supplement];

		for (int i = 0; i < size; i++)
			updated_data[i] = data[i];

		if (data != nullptr)
			delete[] data;

		data = updated_data;
	}

	data[size++] = number;
}

void Vector::pop()
{
	if (size == 0)
		throw std::runtime_error("Vector is empty!");

	if (--size % supplement == 0) {
		int* updated_data = new int[size];

		for (int i = 0; i < size; i++)
			updated_data[i] = data[i];

		delete[] data;
		data = updated_data;
	}
}

int& Vector::at(int index)
{
	if (size == 0)
		throw std::runtime_error("Vector is empty!");

	if (index < 0 || index > size - 1)
		throw std::runtime_error("Going beyond vector boundary!");

	return data[index];
}

int Vector::count()
{
	return size;
}

int Vector::get_sum()
{
	if (size == 0)
		throw std::runtime_error("Vector is empty!");

	int sum = 0;

	for (int i = 0; i < size; i++)
		sum += data[i];

	return sum;
}

long long Vector::concat()
{
	if (size == 0)
		throw std::runtime_error("Vector is empty!");

	auto concat_numbers = [](long long a, long long b)
	{
		a = abs(a);
		b = abs(b);

		for (long long i = b; i != 0; i /= 10)
			a *= 10;

		return a + b;
	};

	long long result = data[0];

	for (int i = 1; i < size; i++)
		result = concat_numbers(result, data[i]);

	return result;
}

bool Vector::operator == (const Vector& vector)
{
	if (this == &vector)
		return true;

	if (size != vector.size)
		return false;

	for (int i = 0; i < size; i++)
		if (data[i] != vector.data[i])
			return false;

	return true;
}

bool Vector::operator != (const Vector& vector)
{
	return !(*this == vector);
}

bool Vector::operator < (const Vector& vector)
{
	if (this == &vector)
		return false;

	int iterations_count = (size < vector.size) ? size : vector.size;

	for (int i = 0; i < iterations_count; i++)
		if (data[i] != vector.data[i])
			return data[i] < vector.data[i];

	return size < vector.size;
}

bool Vector::operator <= (const Vector& vector)
{
	return (*this < vector) || (*this == vector);
}

bool Vector::operator > (const Vector& vector)
{
	return !(*this < vector) && (*this != vector);
}

bool Vector::operator >= (const Vector& vector)
{
	return (*this > vector) || (*this == vector);
}

std::ostream& operator << (std::ostream& stream, const Vector& vector)
{
	if (vector.size == 0) {
		stream << "Vector is empty!\n";
		return stream;
	}

	for (int i = 0; i < vector.size; i++)
		stream << vector.data[i] << "\n";

	return stream;
}