#ifndef STACK_INCLUDED
#define STACK_INCLUDED
#include <ostream>

class Stack
{
private:
	// Array for storing stack elements
	int* data;
	
	// Number of elements in stack
	int size;

	// Number of cells to add when stack overflows
	static constexpr int supplement = 2048;

public:
	Stack();
	~Stack();

	// Add item to the top of stack
	void push(int number);
	
	// Remove item from the top of stack
	void pop();

	// Get a reference to the top element of stack
	int& peek();

	// Get number of items in stack
	int count();

	// Sum of all elements
	int get_sum();

	// Concat all elements
	long long concat();

	// Lexicographic comparison operators
	bool operator == (const Stack& stack);
	bool operator != (const Stack& stack);

	bool operator < (const Stack& stack);
	bool operator <= (const Stack& stack);

	bool operator > (const Stack& stack);
	bool operator >= (const Stack& stack);

	// Output operator
	friend std::ostream& operator << (std::ostream& stream, const Stack& stack);
};

#endif

