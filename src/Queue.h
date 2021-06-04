#ifndef QUEUE_INCLUDED
#define QUEUE_INCLUDED
#include <ostream>

class Queue
{
private:
	// Array for storing queue elements
	int* data;

	// Number of elements in queue
	int size;

	// First index of queue
	int begin_id;

	// Number of cells to add when queue overflows
	static constexpr int supplement = 2048;

public:
	Queue();
	~Queue();

	// Add item to the top of queue
	void push(int number);

	// Remove item from the top of queue
	void pop();

	// Get a reference to the last element of queue
	int& peek();

	// Get number of items in queue
	int count();

	// Sum of all elements
	int get_sum();

	// Concat all elements
	long long concat();

	// Lexicographic comparison operators
	bool operator == (const Queue& queue);
	bool operator != (const Queue& queue);

	bool operator < (const Queue& queue);
	bool operator <= (const Queue& queue);

	bool operator > (const Queue& queue);
	bool operator >= (const Queue& queue);

	// Output operator
	friend std::ostream& operator << (std::ostream& stream, const Queue& queue);
};

#endif