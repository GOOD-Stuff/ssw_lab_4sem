#include "vector.h"

Vector::Vector() {
	size = 1024;
	head = -1;
	arr = new int[size];
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
	if(++head == size) {
		size += 1024;
		int* arr_new = new int[size];

		for (int i = 0; i <= head ; i++)
		{
			arr_new[i] = arr[i];
		}

		delete[] arr;
		arr = arr_new;
	}

	arr[head] = value;
}

std::ostream& operator<<(std::ostream& stream, const Vector& vector)
{
	for (int i = 0; i <= vector.head; i++)
		stream << vector.arr[i] << " ";

	return stream;
}

void Vector::pop_back()
{
	if(head == -1)
        throw "Vector is empty";

    head--;
}

int Vector::count()
{
	return head + 1;
}

int& Vector::at(int index)
{
	if(index > head)
		throw "Element not found";

	return arr[index];
}

float Vector::get_arithmetic_mean()
{
	float sum = 0.0f;

	for (int i = 0; i <= head; i++)
	{
		sum += arr[i];
	}

	return sum / (head + 1);
}

Vector Vector::concat_sort(const Vector& vector)
{
	Vector new_vector;

	new_vector.size = head + 1 + vector.head + 1;
	new_vector.arr = new int[new_vector.size];

	for (int i = 0; i <= head; i++)
	{
		new_vector.push_back(arr[i]);
	}

	for (int i = 0; i <= vector.head; i++)
	{
		new_vector.push_back(arr[i]);
	}

	for (int i = 0; i <= new_vector.head; i++) {
		for (int j = 0; j <= new_vector.head - 1; j++) {
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

	for (int i = 0; i <= head; i++)
	{
		arr[i] = vector.arr[i];
	}

	return *this;
}

bool Vector::operator ==  (const Vector& right)
{
	if (head != right.head)
		return false;

	for (int i = 0; i <= head; i++)
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

bool Vector::operator<(const Vector& right) {
    int thisCount = head + 1;
    int rightCount = right.head + 1;
    int cnt = (thisCount > rightCount) ? rightCount : thisCount;

    for(int i = 0; i < cnt; i++) {
        if(arr[i] == right.arr[i])
            continue;

        return arr[i] < right.arr[i];
    }

    return rightCount > thisCount ? true : false;
}

bool Vector::operator>(const Vector& right) {
    int thisCount = head + 1;
    int rightCount = right.head + 1;
    int cnt = (thisCount > rightCount) ? rightCount : thisCount;

    for(int i = 0; i < cnt; i++) {
        if(arr[i] == right.arr[i])
            continue;

        return arr[i] > right.arr[i];
    }

    return thisCount > rightCount ? true : false;
}

bool Vector::operator <= ( const Vector& right)
{
	return (*this == right) || (*this < right);
}
bool Vector::operator >= ( const Vector& right)
{
	return (*this > right) || (*this == right);
}
