#pragma once
#include <ostream>

template <typename T>
class Stack
{
private:
	// Stack element
	struct Node
	{
		T data;     // Stack element data
		Node* next; // Pointer to next stack element
	};

	Node* head;     // Top of the stack
	size_t count;   // Elements count in stack

private:
	void throw_if_empty(const char* message) const;

public:
	Stack();             // Constructor
	~Stack();            // Destructor

	void push(T data);   // Add item to stack
	void pop();          // Remove item from stack

	T& top();            // Get stack top element

	size_t size() const; // Get stack size
	bool empty() const;  // Stack is empty?

	// Lexicographic comparison operators begin

	template <typename _T>
	friend bool operator==(const Stack<_T>& left, const Stack<_T>& right);

	template <typename _T>
	friend bool operator!=(const Stack<_T>& left, const Stack<_T>& right);

	template <typename _T>
	friend bool operator<(const Stack<_T>& left, const Stack<_T>& right);

	template <typename _T>
	friend bool operator>(const Stack<_T>& left, const Stack<_T>& right);

	template <typename _T>
	friend bool operator<=(const Stack<_T>& left, const Stack<_T>& right);

	template <typename _T>
	friend bool operator>=(const Stack<_T>& left, const Stack<_T>& right);

	// Lexicographic comparison operators end

	// Operator for output all stack elements
	template <typename _T>
	friend std::ostream& operator<<(std::ostream& out, const Stack<_T>& stack);

	// Noncopyable
	Stack(const Stack& stack) = delete;
	Stack& operator=(const Stack& stack) = delete;
};

template <typename T>
Stack<T>::Stack()
{
	head = nullptr;
	count = 0;
}

template <typename T>
Stack<T>::~Stack()
{
	while (!empty())
		pop();
}

template <typename T>
void Stack<T>::push(T data)
{
	Node* node = new Node;
	node->data = data;
	node->next = nullptr;

	Node* prev_top = head;
	head = node;
	head->next = prev_top;

	count++;
}

template <typename T>
void Stack<T>::pop()
{
	throw_if_empty("You are trying to extract item from empty stack!");

	Node* new_head = head->next;

	delete head;
	head = new_head;

	count--;
}

template <typename T>
T& Stack<T>::top()
{
	throw_if_empty("You are trying to access top of empty stack!");
	return head->data;
}

template <typename T>
size_t Stack<T>::size() const
{
	return count;
}

template <typename T>
bool Stack<T>::empty() const
{
	return count == 0;
}

template <typename _T>
bool operator==(const Stack<_T>& left, const Stack<_T>& right)
{
	if (left.size() != right.size())
		return false;

	auto left_it = left.head;
	auto right_it = right.head;

	for (size_t i = 0; i < left.size(); i++)
	{
		if (left_it->data != right_it->data)
			return false;

		left_it = left_it->next;
		right_it = right_it->next;
	}

	return true;
}

template <typename _T>
bool operator!=(const Stack<_T>& left, const Stack<_T>& right)
{
	return !(left == right);
}

template <typename _T>
bool operator<(const Stack<_T>& left, const Stack<_T>& right)
{
	size_t left_size = left.size();
	size_t right_size = right.size();
	size_t min_size = (left_size < right_size) ? left_size : right_size;

	auto left_it = left.head;
	auto right_it = right.head;

	for (size_t i = 0; i < min_size; i++)
	{
		if (left_it->data >= right_it->data)
			return false;

		left_it = left_it->next;
		right_it = right_it->next;
	}

	return true;
}

template <typename _T>
bool operator>(const Stack<_T>& left, const Stack<_T>& right)
{
	return !(left < right) && left != right;
}

template <typename _T>
bool operator<=(const Stack<_T>& left, const Stack<_T>& right)
{
	return left < right || left == right;
}

template <typename _T>
bool operator>=(const Stack<_T>& left, const Stack<_T>& right)
{
	return left > right || left == right;
}

template <typename _T>
std::ostream& operator<<(std::ostream& out, const Stack<_T>& stack)
{
	stack.throw_if_empty("You are trying to display empty stack!");

	auto node = stack.head;

	while (node != nullptr)
	{
		out << node->data << "\n";
		node = node->next;
	}

	return out;
}

template <typename T>
void Stack<T>::throw_if_empty(const char* message) const
{
	if (empty())
		throw std::runtime_error(message);
}