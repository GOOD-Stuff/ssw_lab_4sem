#include "Vector.h"
#include "iostream"
using namespace std;

template<typename T>
void Vector<T>::checkOverflow() {
	if (last+1 == size) {
		T* tmp = arr;
		size += DEF_SIZE;
		arr = new T[size];
		for (int i = 0; i < last-1; i++) {
			arr[i] = tmp[i];
		}
		delete[] tmp;
	}
}


template<typename T>
Vector<T>::Vector() { // Create object with default size
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
		cout << "Vector is empty! Operation 'pop' failed.";
		return 0;
	}

	T last_el = arr[last];
	arr[last] = NULL;
	last--;
	return last_el;
}

template<typename T>
T Vector<T>::at(int i) {
	if (i > last) {
		cout << i << " is empty! Operation 'at' failed.";
		return 0;
	}

	return arr[i];
}

template<typename T>
T Vector<T>::peek() {
	if (last == -1) {
		cout << "Vector is empty! Operation 'peek' failed.";
		return 0;
	}

	return arr[last];
}
template<typename T>
int Vector<T>::count() const {
	return last;
}

template<typename T>
bool Vector<T>::isMount(int start_i) {
	if (size >= 3) {
		for (int i = start_i; i < last; i++) {
			if (arr[i] > arr[i + 1])
				return false;
		}
		return true;
	}
	return false;
}

template<typename T>
void Vector<T>::swap(Vector<T> &v) {
	if (size == v.size) {
		int thisSize = last;
		int rightSize = v.last;
		int size_b = (thisSize < rightSize) ? rightSize : thisSize;
		int tmp;
		for (int i = 0; i < size_b; i++) {
			tmp = arr[i];
			arr[i] = v.arr[i];
			v.arr[i] = tmp;
		}
	}
}

template<typename T>
Vector<T>::~Vector() {
	//delete arr;
}
template <typename T>
bool Vector<T>::operator < (const Vector<T>& right) const {
	int thisSize = last;
	int rightSize = right.last;
	int size_b = (thisSize > rightSize) ? rightSize : thisSize;
	for (int i = 0; i < size_b; i++) {
		if (arr[i] < right.arr[i])
			return true;
	}
	return false;
}

template <typename T>
bool Vector<T>::operator == (const Vector<T>& right) const {
	if (last != right.last)
		return false;
	for (int i = 0; i < size; i++) {
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
