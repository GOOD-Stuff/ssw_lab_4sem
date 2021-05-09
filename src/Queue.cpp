#include "Queue.h"

Queue::Queue()
{
	begin_id = 0;
	data = nullptr;
	size = 0;
}

Queue::~Queue()
{
	if (data == nullptr) {
		delete[] data;
		size = 0;
	}
}

void Queue::push(int number)
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

void Queue::pop()
{
	if (size == 0)
		throw std::runtime_error("Queue is empty!");

	begin_id++;
	size--;

	if (size % supplement == 0 || begin_id % supplement == 0) {
		int* updated_data = new int[size];

		for (int i = begin_id; i < begin_id + size; i++)
			updated_data[i - begin_id] = data[i];

		delete[] data;
		data = updated_data;
		begin_id = 0;
	}
}

int& Queue::peek()
{
	if (size == 0)
		throw std::runtime_error("Queue is empty!");

	return data[size - 1];
}

int Queue::count()
{
	return size;
}

int Queue::get_sum()
{
	if (size == 0)
		throw std::runtime_error("Queue is empty!");

	int sum = 0;

	for (int i = begin_id; i < begin_id + size; i++)
		sum += data[i];

	return sum;
}

long long Queue::concat()
{
	if (size == 0)
		throw std::runtime_error("Queue is empty!");

	auto concat_numbers = [](long long a, long long b)
	{
		a = abs(a);
		b = abs(b);

		for (long long i = b; i != 0; i /= 10)
			a *= 10;

		return a + b;
	};

	long long result = data[begin_id];

	for (int i = begin_id + 1; i < begin_id + size; i++)
		result = concat_numbers(result, data[i]);

	return result;
}

bool Queue::operator == (const Queue& queue)
{
	if (this == &queue)
		return true;

	if (size != queue.size)
		return false;

	for (int i = 0; i < size; i++)
		if (data[i] != queue.data[i])
			return false;

	return true;
}

bool Queue::operator != (const Queue& queue)
{
	return !(*this == queue);
}

bool Queue::operator < (const Queue& queue)
{
	if (this == &queue)
		return false;

	int iterations_count = (size < queue.size) ? size : queue.size;

	for (int i = 0; i < iterations_count; i++)
		if (data[i] != queue.data[i])
			return data[i] < queue.data[i];

	return size < queue.size;
}

bool Queue::operator <= (const Queue& queue)
{
	return (*this < queue) || (*this == queue);
}

bool Queue::operator > (const Queue& queue)
{
	return !(*this < queue) && (*this != queue);
}

bool Queue::operator >= (const Queue& queue)
{
	return (*this > queue) || (*this == queue);
}

std::ostream& operator << (std::ostream& stream, const Queue& queue)
{
	if (queue.size == 0) {
		stream << "Queue is empty!\n";
		return stream;
	}

	for (int i = queue.begin_id; i < queue.begin_id + queue.size; i++)
		stream << queue.data[i] << "\n";

	return stream;
}