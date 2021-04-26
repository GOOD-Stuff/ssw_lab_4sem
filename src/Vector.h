#ifndef VECTOR_INCLUDED
#define VECTOR_INCLUDED

#include <ostream>

class Vector
{
private:
	// Array for store vector data
	int* arr_data;

	// Vector elements count
	int size;

public:
	Vector();
	~Vector();

	// Add element to back
	void push_back(int value);

	// Add element to front
	void push_front(int value);

	// Add element by index
	void insert(int value, int index);

	// Extract element from back
	void pop_back();

	// Extract element from front
	void pop_front();

	// Extract element by index
	void erase(int index);

	// Get vector elements count
	int count();
	
	// Get element by index
	int& at(int index);

	// Calculate sum of all elements
	int get_all_sum();

	// Concatenate all elements
	int concat();

	// Lexicographic comparison operators
	bool operator == (const Vector& right);
	bool operator != (const Vector& right);
	bool operator < (const Vector& right);
	bool operator > (const Vector& right);
	bool operator <= (const Vector& right);
	bool operator >= (const Vector& right);

	// Output operator
	friend std::ostream& operator<<(std::ostream& stream, const Vector& vector);
};

#endif