#include "Stack.h"

Stack::Stack()
{
	data = nullptr;
	size = 0;
}

Stack::~Stack()
{
	if (data != nullptr) {
		delete[] data;
		size = 0;
	}
}

void Stack::push(int number)
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

void Stack::pop()
{
	if (size == 0)
		throw std::runtime_error("Stack is empty!");

	if (--size % supplement == 0) {
		int* updated_data = new int[size];

		for (int i = 0; i < size; i++)
			updated_data[i] = data[i];

		delete[] data;
		data = updated_data;
	}
}

int& Stack::peek()
{
	if (size == 0)
		throw std::runtime_error("Stack is empty!");

	return data[size - 1];
}

int Stack::count()
{
	return size;
}

int Stack::get_sum()
{
	if (size == 0)
		throw std::runtime_error("Stack is empty!");

	int sum = 0;

	for (int i = 0; i < size; i++)
		sum += data[i];

	return sum;
}

long long Stack::concat()
{
	if (size == 0)
		throw std::runtime_error("Stack is empty!");

	auto concat_numbers = [](long long a, long long b)
	{
		a = abs(a);
		b = abs(b);

		for (long long i = b; i != 0; i /= 10)
			a *= 10;

		return a + b;
	};

	long long result = data[size - 1];

	for (int i = size - 2; i >= 0; i--)
		result = concat_numbers(result, data[i]);

	return result;
}

bool Stack::operator == (const Stack& stack)
{
	if (this == &stack)
		return true;

	if (size != stack.size)
		return false;

	for (int i = 0; i < size; i++)
		if (data[i] != stack.data[i])
			return false;

	return true;
}

bool Stack::operator != (const Stack& stack)
{
	return !(*this == stack);
}

bool Stack::operator < (const Stack& stack)
{
	if (this == &stack)
		return false;

	int iterations_count = (size < stack.size) ? size : stack.size;

	for (int i = 0; i < iterations_count; i++)
		if (data[i] != stack.data[i])
			return data[i] < stack.data[i];

	return size < stack.size;
}

bool Stack::operator <= (const Stack& stack)
{
	return (*this < stack) || (*this == stack);
}

bool Stack::operator > (const Stack& stack)
{
	return !(*this < stack) && (*this != stack);
}

bool Stack::operator >= (const Stack& stack)
{
	return (*this > stack) || (*this == stack);
}

std::ostream& operator << (std::ostream& stream, const Stack& stack)
{
	if (stack.size == 0) {
		stream << "Stack is empty!\n";
		return stream;
	}

	for (int i = stack.size - 1; i >= 0; i--)
		stream << stack.data[i] << "\n";

	return stream;
}