#include <ostream>

template <typename T>
class Queue
{
private:
	T* storage;	  // Pointer to array with queue data
	size_t count; // Count of elements in the queue

	size_t deleted_count; // Number that determines when to clear unused memory
	size_t real_size;     // Real queue size (capacity)
	static const size_t reserve = 100; // Reserve cells count

private:
	void delete_storage();                          // Clear memory allocated for the queue
	void replace_storage(T*& new_storage);		    // Replace queue storage 
	void throw_if_empty(const char* message) const; // For exceptions when working with empty queue

public:
	Queue();  // Constructor
	~Queue(); // Destructor

	void push(T value); // Add element
	void pop();         // Delete element

	T& begin(); // Get begin element

	size_t size() const;     // Get queue size
	size_t capacity() const; // Get queue capacity
	bool empty() const;	     // Queue is empty?

	// Lexicographic comparison operators begin

	bool operator==(const Queue<T>& queue) const;
	bool operator!=(const Queue<T>& queue) const;

	bool operator<(const Queue<T>& queue) const;
	bool operator>(const Queue<T>& queue) const;

	bool operator<=(const Queue<T>& queue) const;
	bool operator>=(const Queue<T>& queue) const;

	// Lexicographic comparison operators end

	// Operator for output all queue elements
	friend std::ostream& operator<<(std::ostream& out, const Queue<T>& queue)
	{
		queue.throw_if_empty("You are trying to display empty queue!");

		int real_size = static_cast<int>(queue.real_size);
		int count = static_cast<int>(queue.count);
		int deleted_count = static_cast<int>(queue.deleted_count);

		for (int i = real_size - deleted_count - 1; i > real_size - deleted_count - count - 1; i--)
			out << queue.storage[i] << "\n";

		return out;
	}

	// Noncopyable
	Queue(const Queue& queue) = delete;
	Queue& operator=(const Queue& queue) = delete;
};

template <typename T>
Queue<T>::Queue()
{
	storage = nullptr;
	count = 0;
	real_size = 0;
	deleted_count = 0;
}

template <typename T>
Queue<T>::~Queue()
{
	delete_storage();
}

template <typename T>
void Queue<T>::push(T value)
{
	if (count < real_size)
	{
		storage[real_size - 1 - count++] = value;
		return;
	}

	real_size += reserve;
	T* new_storage = new T[real_size];

	for (size_t i = real_size - 1; i > real_size - count - 1; i--)
		new_storage[i] = storage[i - reserve];

	new_storage[real_size - 1 - count++] = value;
	replace_storage(new_storage);
}

template <typename T>
void Queue<T>::pop()
{
	throw_if_empty("You are trying to extract item from empty queue!");

	--count;

	if (deleted_count != reserve - 1)
	{
		deleted_count++;
		return;
	}

	T* new_storage = new T[count];

	for (size_t i = 0; i < count; i++)
		new_storage[i] = storage[i];

	deleted_count = 0;
	real_size -= reserve;
	replace_storage(new_storage);
}

template <typename T>
T& Queue<T>::begin()
{
	throw_if_empty("You are trying to access begin of empty queue!");
	return storage[real_size - deleted_count - 1];
}

template <typename T>
size_t Queue<T>::size() const
{
	return count;
}

template <typename T>
size_t Queue<T>::capacity() const
{
	return real_size;
}

template <typename T>
bool Queue<T>::empty() const
{
	return count == 0;
}

template <typename T>
bool Queue<T>::operator==(const Queue<T>& queue) const
{
	if (count != queue.count)
		return false;

	T* this_begin = storage + real_size - deleted_count - 1;
	T* queue_begin = queue.storage + queue.real_size - queue.deleted_count - 1;

	for (size_t i = 0; i < count; i++)
		if (*(this_begin--) != *(queue_begin--))
			return false;

	return true;
}

template <typename T>
bool Queue<T>::operator!=(const Queue<T>& queue) const
{
	return !(*this == queue);
}

template <typename T>
bool Queue<T>::operator<(const Queue<T>& queue) const
{
	size_t min_count = count < queue.count ? count : queue.count;

	T* this_begin = storage + real_size - deleted_count - 1;
	T* queue_begin = queue.storage + queue.real_size - queue.deleted_count - 1;

	for (size_t i = 0; i < min_count; i++)
		if (*(this_begin--) >= *(queue_begin--))
			return false;

	return true;
}

template <typename T>
bool Queue<T>::operator>(const Queue<T>& queue) const
{
	return !(*this < queue) && *this != queue;
}

template <typename T>
bool Queue<T>::operator<=(const Queue<T>& queue) const
{
	return *this < queue || *this == queue;
}

template <typename T>
bool Queue<T>::operator>=(const Queue<T>& queue) const
{
	return *this > queue || *this == queue;
}

template <typename T>
void Queue<T>::delete_storage()
{
	if (storage == nullptr)
		return;

	delete[] storage;
	storage = nullptr;
}

template <typename T>
void Queue<T>::replace_storage(T*& new_storage)
{
	delete_storage();
	storage = new_storage;
}

template <typename T>
void Queue<T>::throw_if_empty(const char* message) const
{
	if (empty())
		throw std::runtime_error(message);
}