#ifndef QUEUE_INCLUDED
#define QUEUE_INCLUDED

#include <ostream>
class Queue
{
private:
	// Array for store queue data
	int* memory;

	// Queue elements count
	int size;

public:
	Queue();
	~Queue();

	// Add element
	void push(int value);
	
	// Extract element
	void pop();

	// Get first element
	int& peek();

	// Get queue elements count
	int count();

	// Lexicographic comparison operators
	bool operator == (const Queue& right);
	bool operator != (const Queue& right);
	bool operator < (const Queue& right);
	bool operator > (const Queue& right);
	bool operator <= (const Queue& right);
	bool operator >= (const Queue& right);

	// Output operator
	friend std::ostream& operator<<(std::ostream& stream, const Queue& queue);
};

#endif