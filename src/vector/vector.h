#ifndef CLASS_VECTOR_H
#define CLASS_VECTOR_H

#include <ostream>

class Vector
{
private:
	int* arr;		// Pointer to an array with vector data
	int size;       // Number of elements in a vector
    int head;

public:
    /**
    * @brief Vector constructor
    */
	Vector();

	/**
    * @brief Vector copy constructor
    */
	Vector(const Vector& vector);

	/**
    * @brief Vector destructor
    */
	~Vector();


	/**
    * @brief Add element to end
	*
	* @param int Element to write
    */
	void push_back(int value);

	/**
    * @brief Delete last element
    */
	void pop_back();

	/**
    * @brief Get number of items on vector
    *
    * @return Number of items in vector
    */
	int count();

	/**
    * @brief Get reference to an element with a specified index
    *
	* @param int Position index
    * @return int& Reference to an element with a specified index
    */
	int& at(int index);

	/**
    * @brief Getting the arithmetic average
    *
    * @return float Arithmetic average
    */
	float get_arithmetic_mean();

	/**
    * @brief Outputs a new collection, linked to another, in a sorted form
    *
	* @param Vector& Vector for concatenation
    * @return Vector New converted vector
    */
	Vector concat_sort(const Vector& vector);


	/**
    * @brief Assignment operator
    *
	* @param Vector& Vector from which we will copy
    * @return Vector& Current vector
    */
	Vector& operator = (const Vector& right);

    /**
     * @brief Comparison operators
     *
     * @param Vector& Vector to compare it withV
     * @return bool Comparison result
     */
	bool operator == (const Vector& right);
	bool operator != (const Vector& right);
	bool operator < (const Vector& right);
	bool operator > (const Vector& right);
	bool operator <= (const Vector& right);
	bool operator >= (const Vector& right);

    /**
     * @brief Output vector operator
     *
     * @param ostream& Output object
     * @param Vector& Vector to display
     */
	friend std::ostream& operator<<(std::ostream& stream, const Vector& vector);
};

#endif
