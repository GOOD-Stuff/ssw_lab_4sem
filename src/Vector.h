#ifndef VECTOR_INCLUDED
#define VECTOR_INCLUDED
#include <ostream>

class Vector
{
private:
	// Array for storing vector elements
	int* data;

	// Number of elements in vector
	int size;

	// Number of cells to add when vector overflows
	static constexpr int supplement = 2048;

public:
	Vector();
	~Vector();

	// Add item to the top of vector
	void push(int number);

	// Remove item from the top of vector
	void pop();

	// Get a reference to the top element of vector
	int& at(int index);

	// Get number of items in vector
	int count();

	// Sum of all elements
	int get_sum();

	// Concat all elements
	long long concat();

	// Lexicographic comparison operators
	bool operator == (const Vector& vector);
	bool operator != (const Vector& vector);

	bool operator < (const Vector& vector);
	bool operator <= (const Vector& vector);

	bool operator > (const Vector& vector);
	bool operator >= (const Vector& vector);

	// Output operator
	friend std::ostream& operator << (std::ostream& stream, const Vector& vector);
};

#endif