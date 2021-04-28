#include <iostream>
#include "stack.h"

template<typename T>
Stack<T>::Stack() {
    init(DEFAULT_SIZE);
}

template<typename T>
Stack<T>::~Stack() {
    delete[] arr;
}

template<typename T>
Stack<T>::Stack(int size) {
    init(size);
}

template<typename T>
void Stack<T>::init(int size) {
    size = size;
    head = -1;
    arr = new T[size];
}

template<typename T>
void Stack<T>::checkDimension() {
    if(size - count() == 0) {
        size += DEFAULT_SIZE;
        T* _arr = new T[size];

        for(int i = 0; i < size - DEFAULT_SIZE; i++)
            _arr[i] = arr[i];

        delete[] arr;
        arr = _arr;
    }
}

template<typename T>
void Stack<T>::push(T item) {
    checkDimension();
    arr[++head] = item;
}

template<typename T>
T Stack<T>::pop() {
    if(head == -1)
        throw "Stack is empty";

    return arr[head--];
}

template<typename T>
T Stack<T>::peek() {
    if(head == -1)
        throw "Stack is empty";

    return arr[head];
}

template<typename T>
Stack<T> Stack<T>::concat(const Stack<T>& st) {
    int thisCount = count();
    int contacStackCount = st.count();

    Stack<T> newStack(thisCount + contacStackCount + DEFAULT_SIZE);

    for(int i = 0; i < count(); i++)
        newStack.push(arr[i]);

    for(int i = 0; i < contacStackCount; i++)
        newStack.push(st.arr[i]);

    for (int i = 0; i < newStack.count(); i++) {
		for (int j = 0; j < newStack.count() - 1; j++) {
			if (newStack.arr[j] < newStack.arr[j + 1]) {
				T temp = newStack.arr[j];
				newStack.arr[j] = newStack.arr[j + 1];
				newStack.arr[j + 1] = temp;
			}
		}
	}

    return newStack;
}

template<typename T>
T Stack<T>::getAverage() {
    T sum = arr[0];

    for(int i = 1; i < count(); i++)
        sum += arr[i];

    return sum / count();
}

template<typename T>
bool Stack<T>::operator<(const Stack<T>& right) {
    int thisCount = count();
    int rightCount = right.count();
    int cnt = (thisCount > rightCount) ? rightCount : thisCount;

    for(int i = 0; i < cnt; i++) {
        if(arr[i] == right.arr[i])
            continue;

        return arr[i] < right.arr[i];
    }

    return rightCount > thisCount ? true : false;
}

template<typename T>
bool Stack<T>::operator>(const Stack<T>& right) {
    int thisCount = count();
    int rightCount = right.count();
    int cnt = (thisCount > rightCount) ? rightCount : thisCount;

    for(int i = 0; i < cnt; i++) {
        if(arr[i] == right.arr[i])
            continue;

        return arr[i] > right.arr[i];
    }

    return thisCount > rightCount ? true : false;
}

template<typename T>
bool Stack<T>::operator==(const Stack<T>& right) {
    if(count() != right.count())
        return false;

    for(int i = 0; i < count(); i++) {
        if(arr[i] != right.arr[i])
            return false;
    }

    return true;
}

template<typename T>
bool Stack<T>::operator!=(const Stack<T>& right) {
    return !(*this == right);
}

template<typename T>
bool Stack<T>::operator<=(const Stack<T>& right) {
    return (*this == right) || (*this < right);
}

template<typename T>
bool Stack<T>::operator>=(const Stack<T>& right) {
    return (*this == right) || (*this > right);
}

template<class T>
std::ostream& operator<<(std::ostream& stream, const Stack<T>& stack) {
    for(int i = 0; i <= stack.head; i++)
		stream << stack.arr[i] << " ";

    return stream;
}
