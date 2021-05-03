#include "Stack.h"
#include "iostream"

using namespace std;


template<typename T>
void Stack<T>::checkOverflow() {
	if (top+1 == size) {
		T* tmp = arr;
		size += DEF_SIZE;
		arr = new T[size];
		for (int i = 0; i < top-1; i++) {
			arr[i] = tmp[i];
		}
		delete[] tmp;
	}
}

template<typename T>
Stack<T>::Stack() { 
	size = DEF_SIZE;
	arr = new T[size];
	top = -1;
}

template<typename T>
Stack<T>::Stack(int size) {
	this->size = size;
	arr = new T[size];
	top = -1;
}

template<typename T>
void Stack<T>::push(T elem) {
	checkOverflow();
	top++;
	arr[top] = elem;

}

template<typename T>
T Stack<T>::pop() {
	if (top == -1) {
		cout << "Stack is empty! Operation 'pop' failed.";
		return 0;
	}
	T last = arr[top];
	arr[top] = NULL;
	top--;
	return last;
}

template<typename T>
T Stack<T>::peek() {
	if (top == -1) {
		cout << "Stack is empty! Operation 'peek' failed.";
		return 0;
	}
	return arr[top];
}

template<typename T>
int Stack<T>::count() const {
	return top;
}

template<typename T>
bool Stack<T>::isMount(int start_i) {
	if (size >= 3) {
		for (int i = start_i; i < top; i++) {
			if (arr[i] > arr[i + 1])
				return false;
		}
		return true;
	}
	return false;
}

template<typename T>
void Stack<T>::swap(Stack<T> &s) {
	if (size == s.size) {
		int thisSize = top;
		int rightSize = s.top;
		int size_b = (thisSize < rightSize) ? rightSize : thisSize;
		int tmp;
		for (int i = 0; i < size_b; i++) {
			tmp = arr[i];
			arr[i] = s.arr[i];
			s.arr[i] = tmp;
		}
	}
}
template<typename T>
void Stack<T>::print() {
	for (int i = 0; i <= top; i++)
		cout << arr[i]; 
	cout << endl;
}

template<typename T>
Stack<T>::~Stack() {
	delete[] arr;
}

template <typename T>
bool Stack<T>::operator < (const Stack<T>& right) const{
	int thisSize = top;
	int rightSize = right.count();
	int size_b = (thisSize > rightSize) ? rightSize : thisSize;
	for (int i = 0; i < size_b; i++) {
		if (arr[i] < right.arr[i])
			return true;
	}
	return false;
}

template <typename T>
bool Stack<T>::operator == (const Stack<T>& right) const {
	if (top != right.top)
		return false;
	for (int i = 0; i < size; i++) {
		if (arr[i] != right.arr[i])
			return false;
	}
	return true;
}

template <typename T>
bool Stack<T>::operator != (const Stack<T>& right) const {
	return !(*this == right);
}

template <typename T>
bool Stack<T>::operator > (const Stack<T>& right) const {
	return !(*this < right) && *this != right;
}

template <typename T>
bool Stack<T>::operator >= (const Stack<T>& right) const {
	return (*this > right) || (*this == right);
}
template <typename T>
bool Stack<T>::operator <= (const Stack<T>& right) const {
	return (*this < right) || (*this == right);
}



