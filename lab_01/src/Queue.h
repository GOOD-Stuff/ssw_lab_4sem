#include <ostream>

template <typename T>
class Queue
{
private:
	T* storage;	  // Pointer to array with queue data
	size_t count; // Count of elements in the queue

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

	size_t size() const; // Get queue size
	bool empty() const;	 // Queue is empty?

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

		for (size_t i = 0; i < queue.size(); i++)
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
}

template <typename T>
Queue<T>::~Queue()
{
	delete_storage();
	count = 0;
}

template <typename T>
void Queue<T>::push(T value)
{
	T* new_storage = new T[count + 1];

	for (size_t i = 0; i < count; i++)
		new_storage[i] = storage[i];

	new_storage[count++] = value;
	replace_storage(new_storage);
}

template <typename T>
void Queue<T>::pop()
{
	throw_if_empty("You are trying to extract item from empty queue!");

	T* new_storage = new T[--count];

	for (size_t i = 0; i < count; i++)
		new_storage[i] = storage[i + 1];

	replace_storage(new_storage);
}

template <typename T>
T& Queue<T>::begin()
{
	throw_if_empty("You are trying to access begin of empty queue!");
	return storage[0];
}

template <typename T>
size_t Queue<T>::size() const
{
	return count;
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

	for (size_t i = 0; i < count; i++)
		if (storage[i] != queue.storage[i])
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

	for (size_t i = 0; i < min_count; i++)
		if (storage[i] >= queue.storage[i])
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