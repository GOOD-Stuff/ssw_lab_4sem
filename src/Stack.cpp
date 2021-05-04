#include "Stack.h"

Stack::Stack()
{
	data_arr = nullptr;
	size = 0;
}

Stack::~Stack()
{
	if (data_arr)
		delete[] data_arr;
}

void Stack::push(int value)
{
	int* new_data_arr = new int[++size];
	for (int i = 0; i < size - 1; i++)
	{
		new_data_arr[i] = data_arr[i];
	}
	new_data_arr[size - 1] = value;
	delete[] data_arr;
	data_arr = new_data_arr;
}

void Stack::pop()
{
	int* new_data_arr = new int[--size];
	for (int i = 0; i < size; i++)
	{
		new_data_arr[i] = data_arr[i];
	}
	delete[] data_arr;
	data_arr = new_data_arr;
}

int& Stack::peek()
{
	return data_arr[size - 1];
}

int Stack::count()
{
	return size;
}

std::ostream& operator<<(std::ostream& stream, const Stack& stack)
{
	for (int i = stack.size - 1; i >= 0; i--)
	{
		stream << stack.data_arr[i] << "\n";
	}

	return stream;
}

bool Stack::operator == (const Stack& right)
{
	if (size != right.size)
		return false;

	for (int i = 0; i < size; i++)
	{
		if (data_arr[i] != right.data_arr[i])
			return false;
	}

	return true;
}

bool Stack::operator != (const Stack& right)
{
	return !(*this == right);
}

bool Stack::operator < (const Stack& right)
{
	int result_size = (size < right.size) ? size : right.size;

	for (int i = 0; i < result_size; i++)
		if (data_arr[i] != right.data_arr[i])
			return data_arr[i] < right.data_arr[i];

	return size < right.size;
}

bool Stack::operator > (const Stack& right)
{
	return !(*this < right) && (*this != right);
}

bool Stack::operator <= (const Stack& right)
{
	return (*this < right) || (*this == right);
}

bool Stack::operator >= (const Stack& right)
{
	return (*this > right) || (*this == right);
}
