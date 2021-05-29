#include "CircularBuffer.h"

template<class T>
typename CircularBuffer<T>::iterator search(CircularBuffer<T>& buffer, T data)
{
	if (buffer.count() == 0)
	{
		throw std::runtime_error("Circular buffer is empty!");
	}

	typename CircularBuffer<T>::iterator it = buffer.begin();

	while (it != buffer.end() && *it != data)
	{
		it++;
	}

	return it;
}
