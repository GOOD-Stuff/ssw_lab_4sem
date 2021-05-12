#ifndef STACK_H
#define STACK_H
#include <stdexcept>
#include "ostream"

template <typename T>
class Stack {
private:
	T* arr; // Pointer to an array with stack elements
	int top; // Top of stack number
	int size; // Real stack size
	static constexpr int DEF_SIZE{ 2 }; // Initial size
	void checkOverflow(); // Overflow Checking and Stack Growth
public:
	Stack(); // Create object with default size
	~Stack(); // destructor
	void push(T elem); // Adding an item to the stack

	T pop(); // Removing and returning the top of the stack

	T& peek(); // Returning the top of the stack

	int count() const; // Returning the real size

	bool isMount();//  Determination of the mountain sequence

	void swap(Stack<T> &s); // Exchange between structures


	// Lexicographic comparison operators
	bool operator<( const Stack<T>& right) const;
	bool operator>(const Stack<T>& right) const;
	bool operator==(const Stack<T>& right) const;
	bool operator!=(const Stack<T>& right) const ;
	bool operator<=(const Stack<T>& right) const;
	bool operator>=(const Stack<T>& right) const;

	friend std::ostream& operator<<(std::ostream& o, const Stack<T>& r) {
		for (int i = 0; i <= r.top; i++) {
			o << r.arr[i] << " ";
		}
		o << "\n";
		return o;
	}

};

template<typename T>
void Stack<T>::checkOverflow() {
	if (top + 1 == size) {
		T* tmp = arr;
		size *= DEF_SIZE;
		arr = new T[size];
		for (int i = 0; i <= top; i++) {
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
void Stack<T>::push(T elem) {
	checkOverflow();
	top++;
	arr[top] = elem;

}

template<typename T>
T Stack<T>::pop() {
	if (top == -1) {
		throw std::runtime_error("Stack is empty! Pop failed");
	}
	T last = arr[top];
	top--;
	return last;
}

template<typename T>
T& Stack<T>::peek() {
	if (top == -1) {
		throw std::runtime_error("Stack is empty! Peek failed");
		return 0;
	}
	return arr[top];
}

template<typename T>
int Stack<T>::count() const {
	return size;
}

template<typename T>
bool Stack<T>::isMount() {
	if (top >= 3) {
		for (int i = 0; i < top - 1; i++) {
			if (arr[i] > arr[i + 1])
				return false;
		}
		return true;
	}
	return false;
}

template<typename T>
void Stack<T>::swap(Stack<T>& v) {
	T* tmp_arr = arr;
	int tmp_size = size;
	int tmp_last = top;

	arr = v.arr;
	size = v.size;
	top = v.top;

	v.arr = tmp_arr;
	v.size = tmp_size;
	v.top = tmp_last;
}

template<typename T>
Stack<T>::~Stack() {
	delete[] arr;
}

template <typename T>
bool Stack<T>::operator < (const Stack<T>& right) const {
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
	for (int i = 0; i <= top; i++) {
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





#endif
