#ifndef CLASS_VECTOR_H
#define CLASS_VECTOR_H

#include <ostream>

class Vector
{
private:
	int* arr;		// Pointer to an array with vector data
	int size;       // Number of elements in a vector

public:
	Vector();
	Vector(const Vector& vector);
	~Vector();

	void push_back(int value);					// Add element to end
	void push_front(int value);					// Add element to front
	void insert(int value, int index);			// Insert element by index

	void pop_back();							// Delete first element
	void pop_front();							// Delete last element
	void erase(int index);						// Delete an element by index

	int count();								// Returns the number of elements

	int& at(int index);							// Returns a reference to an element with a specified index
	float get_arithmetic_mean();				// Getting the arithmetic average

	Vector concat_sort(const Vector& vector);	// Outputs a new collection, linked to another, in a sorted form
	Vector& operator = (const Vector& right);

	// The lexicographic comparison operators

	bool operator == (const Vector& right);
	bool operator != (const Vector& right);
	bool operator < (const Vector& right);
	bool operator > (const Vector& right);
	bool operator <= (const Vector& right);
	bool operator >= (const Vector& right);
	friend std::ostream& operator<<(std::ostream& stream, const Vector& vector);	// Operator outputs all elements of a vector

};

#endif


