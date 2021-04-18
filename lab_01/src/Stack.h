#ifndef CLASS_STACK_H
#define CLASS_STACK_H

#include <ostream>

template <typename T>
class Stack
{
private:
	T* storage;	  // Pointer to array with stack data
	size_t count; // Count of elements in the stack

	size_t real_size; // Real stack size (capacity)
	static const size_t reserve = 100; // Reserve cells count

private:
	void delete_storage();                          // Clear memory allocated for the stack
	void replace_storage(T*& new_storage);		    // Replace stack storage 
	void throw_if_empty(const char* message) const; // For exceptions when working with empty stack

public:
	Stack();  // Constructor
	~Stack(); // Destructor

	void push(T value); // Add element
	void pop();         // Delete element

	T& top(); // Get top element

	size_t size() const;     // Get stack size
	size_t capacity() const; // Get stack capacity
	bool empty() const;	     // Stack is empty?

	// Lexicographic comparison operators begin

	bool operator==(const Stack<T>& stack) const;
	bool operator!=(const Stack<T>& stack) const;

	bool operator<(const Stack<T>& stack) const;
	bool operator>(const Stack<T>& stack) const;

	bool operator<=(const Stack<T>& stack) const;
	bool operator>=(const Stack<T>& stack) const;

	// Lexicographic comparison operators end

	// Operator for output all stack elements
	friend std::ostream& operator<<(std::ostream& out, const Stack<T>& stack)
	{
		stack.throw_if_empty("You are trying to display empty stack!");

		for (int i = stack.size() - 1; i >= 0; i--)
			out << stack.storage[i] << "\n";

		return out;
	}

	// Noncopyable
	Stack(const Stack& stack) = delete;
	Stack& operator=(const Stack& stack) = delete;
};

template <typename T>
Stack<T>::Stack()
{
	storage = nullptr;
	count = 0;
	real_size = 0;
}

template <typename T>
Stack<T>::~Stack()
{
	delete_storage();
}

template <typename T>
void Stack<T>::push(T value)
{
	if (count < real_size)
	{
		storage[count++] = value;
		return;
	}

	real_size += reserve;
	T* new_storage = new T[real_size];

	for (size_t i = 0; i < count; i++)
		new_storage[i] = storage[i];

	new_storage[count++] = value;
	replace_storage(new_storage);
}

template <typename T>
void Stack<T>::pop()
{
	throw_if_empty("You are trying to extract item from empty stack!");

	if (--count > real_size - reserve)
		return;

	T* new_storage = new T[count];

	for (size_t i = 0; i < count; i++)
		new_storage[i] = storage[i];

	real_size -= reserve;
	replace_storage(new_storage);
}

template <typename T>
T& Stack<T>::top()
{
	throw_if_empty("You are trying to access top of empty stack!");
	return storage[count - 1];
}

template <typename T>
size_t Stack<T>::size() const
{
	return count;
}

template <typename T>
size_t Stack<T>::capacity() const
{
	return real_size;
}

template <typename T>
bool Stack<T>::empty() const
{
	return count == 0;
}

template <typename T>
bool Stack<T>::operator==(const Stack<T>& stack) const
{
	if (count != stack.count)
		return false;

	for (size_t i = 0; i < count; i++)
		if (storage[i] != stack.storage[i])
			return false;

	return true;
}

template <typename T>
bool Stack<T>::operator!=(const Stack<T>& stack) const
{
	return !(*this == stack);
}

template <typename T>
bool Stack<T>::operator<(const Stack<T>& stack) const
{
	size_t min_count = count < stack.count ? count : stack.count;
	size_t max_count = count > stack.count ? count : stack.count;
	size_t delta_size = max_count - min_count;

	bool first_is_greater = count > stack.count;

	for (size_t i = max_count - 1; i >= delta_size && i != 0; i--)
		if (first_is_greater)
		{
			if (storage[i] < stack.storage[i - delta_size])
				return true;
		}
		else
		{
			if (storage[i - delta_size] < stack.storage[i])
				return true;
		}

	return false;
}

template <typename T>
bool Stack<T>::operator>(const Stack<T>& stack) const
{
	return !(*this < stack) && *this != stack;
}

template <typename T>
bool Stack<T>::operator<=(const Stack<T>& stack) const
{
	return *this < stack || *this == stack;
}

template <typename T>
bool Stack<T>::operator>=(const Stack<T>& stack) const
{
	return *this > stack || *this == stack;
}

template <typename T>
void Stack<T>::delete_storage()
{
	if (storage == nullptr)
		return;

	delete[] storage;
	storage = nullptr;
}

template <typename T>
void Stack<T>::replace_storage(T*& new_storage)
{
	delete_storage();
	storage = new_storage;
}

template <typename T>
void Stack<T>::throw_if_empty(const char* message) const
{
	if (empty())
		throw std::runtime_error(message);
}

#endif