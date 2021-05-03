#ifndef VECTOR_H
#define VECTOR_H
#define DEF_SIZE 32768

template <typename T>
class Vector {
private:
	T* arr; // Pointer to an array with vector elements
	int last, size; //Vector size and last element
	void checkOverflow(); // Overflow Checking and Vector Growth
public:
	Vector(); // constructor
	~Vector(); // destructor

	void push(T elem);  // Adding an item to the vector
	 
	T pop(); // Removing and returning last element of vector

	T at(int i); // Getting a vector element with an index i

	T peek(); // Returning the last element of vector

	int count()const; // Returning the number of elements on a vecotr

	bool isMount(int start_i); //  Determination of the mountain sequence

	void swap(Vector<T>& v); // Exchange between structures


	// Lexicographic comparison operators
	bool operator<(const Vector<T>& right) const;
	bool operator>(const Vector<T>& right) const;
	bool operator==(const Vector<T>& right) const;
	bool operator!=(const Vector<T>& right) const;
	bool operator<=(const Vector<T>& right) const;
	bool operator>=(const Vector<T>& right) const;

};
#endif