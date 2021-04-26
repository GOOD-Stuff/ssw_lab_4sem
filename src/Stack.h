#ifndef STACK_INCLUDED
#define STACK_INCLUDED

#include <ostream>

class Stack
{
private:
	// Array for store stack data
	int* data_arr;

	// Stack elements count
	int size;

public:
	Stack();
	~Stack();

	// Add element
	void push(int value);

	// Extract element
	void pop();

	// Get top element
	int& peek();

	// Get stack elements count
	int count();

	// Lexicographic comparison operators
	bool operator == (const Stack& right);
    bool operator != (const Stack& right);
	bool operator < (const Stack& right);
	bool operator > (const Stack& right);
	bool operator <= (const Stack& right);
	bool operator >= (const Stack& right);

	// Output operator
	friend std::ostream& operator<<(std::ostream& stream, const Stack& stack);
};

#endif