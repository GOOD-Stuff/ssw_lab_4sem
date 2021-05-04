#include "Queue.h"

Queue::Queue()
{
	memory = nullptr;
	size = 0;
}

Queue::~Queue()
{
	if (memory)
		delete[] memory;
}


void Queue::push(int value)
{
	int* new_memory = new int[++size];
	for (int i = 0; i < size - 1; i++)
	{
		new_memory[i] = memory[i];
	}
	new_memory[size - 1] = value;
	delete[] memory;
	memory = new_memory;
}

void Queue::pop()
{
	int* new_memory = new int[--size];
	int j = 0;
	for (int i = 1; i <= size; i++)
	{
		new_memory[j] = memory[i];
		j++;
	}
	delete[] memory;
	memory = new_memory;
}

int& Queue::peek()
{
	return memory[0];
}

int Queue::count()
{
	return size;
}

std::ostream& operator<<(std::ostream& stream, const Queue& queue)
{
	for (int i = 0; i < queue.size; i++)
	{
		stream << queue.memory[i] << "\n";
	}

	return stream;
}

bool Queue::operator == (const Queue& right)
{
	if (size != right.size)
		return false;

	for (int i = 0; i < size; i++)
	{
		if (memory[i] != right.memory[i])
			return false;
	}

	return true;
}

bool Queue::operator != (const Queue& right)
{
	return !(*this == right);
}

bool Queue::operator < (const Queue& right)
{
	int min_size = size < right.size ? size : right.size;
	int max_size = size > right.size ? size : right.size;
	int delta_size = max_size - min_size;

	for (int i = max_size - 1; i >= max_size - min_size; i--)
	{
		if (size > right.size)
		{
			if (memory[i] != right.memory[i - delta_size])
				return memory[i] < right.memory[i - delta_size];
		}
		else
		{
			if (memory[i - delta_size] != right.memory[i])
				return memory[i - delta_size] < right.memory[i];
		}
	}

	return false;
}

bool Queue::operator > (const Queue& right)
{
	return !(*this < right) && (*this != right);
}

bool Queue::operator <= (const Queue& right)
{
	return (*this < right) || (*this == right);
}

bool Queue::operator >= (const Queue& right)
{
	return (*this > right) || (*this == right);
}