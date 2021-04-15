#ifndef CLASS_VECTOR_H
#define CLASS_VECTOR_H

#include <ostream>

class Vector
{
private:
	int* arr;
	int size;
public:
	Vector();
	Vector(const Vector& vector);
	~Vector();

	void push_back(int value);
	void push_front(int value);
	void insert(int value, int index);

	void pop_back();
	void pop_front();
	void erase(int index);

	int count();

	int& at(int index);
	float get_arithmetic_mean();

	Vector concat_sort(const Vector& vector);
	Vector& operator = (const Vector& right);

	bool operator == (const Vector& right);
	bool operator != (const Vector& right);
	bool operator < (const Vector& right);
	bool operator > (const Vector& right);
	bool operator <= (const Vector& right);
	bool operator >= (const Vector& right);
	friend std::ostream& operator<<(std::ostream& stream, const Vector& vector);
};

#endif


