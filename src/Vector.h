#ifndef VECTOR_H
#define VECTOR_H
#include <stdexcept>
#include "ostream"

template <typename T>
class Vector {
private:
	T* arr; // Pointer to an array with vector elements
	int last; // Index last element
	int size; //Vector size
	void checkOverflow(); // Overflow Checking and Vector Growth
	static constexpr int DEF_SIZE{ 2 };// Initial size
public:
	Vector(); // constructor
	~Vector(); // destructor

	void push(T elem);  // Adding an item to the vector
	 
	T pop(); // Removing and returning last element of vector

	T& at(int i); // Getting a vector element with an index i

	T& peek(); // Returning the last element of vector

	int count()const; // Returning the real size 

	bool isMount(); //  Determination of the mountain sequence

	void swap(Vector<T>& v); // Exchange between structures


	// Lexicographic comparison operators
	bool operator<(const Vector<T>& right) const;
	bool operator>(const Vector<T>& right) const;
	bool operator==(const Vector<T>& right) const;
	bool operator!=(const Vector<T>& right) const;
	bool operator<=(const Vector<T>& right) const;
	bool operator>=(const Vector<T>& right) const;

	friend std::ostream& operator<<(std::ostream& o, const Vector<T>& r) {
		for (int i = 0; i <= r.last; i++) {
			o << r.arr[i] << " ";
		}
		o << "\n";
		return o;
	}

};

template<typename T>
void Vector<T>::checkOverflow() {
	if (last + 1 == size) {
		T* tmp = arr;
		size *= DEF_SIZE;
		arr = new T[size];
		for (int i = 0; i <= last; i++) {
			arr[i] = tmp[i];
		}
		delete[] tmp;
	}
}


template<typename T>
Vector<T>::Vector() {
	size = DEF_SIZE;
	arr = new T[size];
	last = -1;
}



template<typename T>
void Vector<T>::push(T elem) {
	checkOverflow();
	last++;
	arr[last] = elem;
}

template<typename T>
T Vector<T>::pop() {
	if (last == -1) {
		throw std::runtime_error("Vector is empty! Pop failed");
	}

	T last_el = arr[last];
	last--;
	return last_el;
}

template<typename T>
T& Vector<T>::at(int i) {
	if (i > last || i < 0) {
		throw std::runtime_error("Index i is empty! At failed");
	}

	return arr[i];
}

template<typename T>
T& Vector<T>::peek() {
	if (last == -1) {
		throw std::runtime_error("Vector is empty! Peek failed");
	}

	return arr[last];
}
template<typename T>
int Vector<T>::count() const {
	return size;
}

template<typename T>
bool Vector<T>::isMount() {
	if (last >= 3) {
		T max = arr[0];
		T max_i;
		for (int i = 0; i <= last; i++) {
			if (arr[i] > max) {
				max = arr[i];
				max_i = i;
			}
		}
		for (int i = 0; i < max_i; i++) {
			if (arr[i] > arr[i + 1])
				return false;
		}
		for (int i = last; i != max_i; i--) {
			if (arr[i] > arr[i - 1])
				return false;
		}
		return true;
	}
	return false;
}

template<typename T>
void Vector<T>::swap(Vector<T>& v) {
	if (v == *this)
		throw std::runtime_error("Can't swap the same object");
	T* tmp_arr = arr;
	int tmp_size = size;
	int tmp_last = last;

	arr = v.arr;
	size = v.size;
	last = v.last;

	v.arr = tmp_arr;
	v.size = tmp_size;
	v.last = tmp_last;
	
}

template<typename T>
Vector<T>::~Vector() {
	if (arr != nullptr)
		delete[] arr;
}
template <typename T>
bool Vector<T>::operator < (const Vector<T>& right) const {
	int thisSize = last;
	int rightSize = right.last;
	int size_b = (thisSize > rightSize) ? rightSize : thisSize;
	for (int i = 0; i < size_b; i++) {
		if (arr[i] != right.arr[i])
			return arr[i] < right.arr[i];
	}
	return thisSize < rightSize;
}

template <typename T>
bool Vector<T>::operator == (const Vector<T>& right) const {
	if (last != right.last)
		return false;
	for (int i = 0; i <= last; i++) {
		if (arr[i] != right.arr[i])
			return false;
	}
	return true;
}

template <typename T>
bool Vector<T>::operator != (const Vector<T>& right) const {
	return !(*this == right);
}

template <typename T>
bool Vector<T>::operator > (const Vector<T>& right) const {
	return !(*this < right) && *this != right;
}

template <typename T>
bool Vector<T>::operator >= (const Vector<T>& right) const {
	return (*this > right) || (*this == right);
}
template <typename T>
bool Vector<T>::operator <= (const Vector<T>& right) const {
	return (*this < right) || (*this == right);
}
#endif
