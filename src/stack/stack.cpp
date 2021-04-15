#include <iostream>
#include "stack.h"

template<typename T>
stack<T>::stack() {
    init(DEFAULT_SIZE);
}

template<typename T>
stack<T>::stack(int size) {
    init(size);
}

template<typename T>
void stack<T>::init(int size) {
    size = size;
    head = -1;
    arr = new T[size];
}

template<typename T>
void stack<T>::checkDimension() {
    if(size - count() == 0) {
        size += DEFAULT_SIZE;
        T* _arr = new T[size];

        for(int i = 0; i < size - DEFAULT_SIZE; i++)
            _arr[i] = arr[i];

        delete arr;
        arr = _arr;
    }
}

template<typename T>
void stack<T>::push(T item) {
    checkDimension();
    arr[++head] = item;
}

template<typename T>
T stack<T>::pop() {
    if(head == -1)
        throw "Stack is empty";

    return arr[head--];
}

template<typename T>
T stack<T>::peek() {
    if(head == -1)
        throw "Stack is empty";

    return arr[head];
}

template<typename T>
stack<T> stack<T>::concat(const stack<T>& st) {
    int thisCount = count();
    int contacStackCount = st.count();

    stack<T> newStack(thisCount + contacStackCount + DEFAULT_SIZE);

    for(int i = 0; i < count(); i++)
        newStack.push(arr[i]);

    for(int i = 0; i < contacStackCount; i++)
        newStack.push(st.arr[i]);

    for (int i = 0; i < newStack.count(); i++) {
		for (int j = 0; j < newStack.count() - 1; j++) {
			if (newStack.arr[j] > newStack.arr[j + 1]) {
				T temp = newStack.arr[j];
				newStack.arr[j] = newStack.arr[j + 1];
				newStack.arr[j + 1] = temp;
			}
		}
	}

    return newStack;
}

template<typename T>
T stack<T>::getAverage() {
    T sum = arr[0];

    for(int i = 1; i < count(); i++)
        sum += arr[i];

    return sum / count();
}

template<typename T>
bool stack<T>::operator<(const stack<T>& right) {
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
bool stack<T>::operator>(const stack<T>& right) {
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
bool stack<T>::operator==(const stack<T>& right) {
    if(count() != right.count())
        return false;

    for(int i = 0; i < count(); i++) {
        if(arr[i] != right.arr[i])
            return false;
    }

    return true;
}

template<typename T>
bool stack<T>::operator!=(const stack<T>& right) {
    return !(*this == right);
}

template<typename T>
bool stack<T>::operator<=(const stack<T>& right) {
    return (*this == right) || (*this < right);
}

template<typename T>
bool stack<T>::operator>=(const stack<T>& right) {
    return (*this == right) || (*this > right);
}

template<class T>
std::ostream& operator<<(std::ostream& stream, const stack<T>& stack) {
    stream << "Count: " << stack.count() << std::endl;

    for(int i = stack.head; i >= 0; i--)
		stream << stack.arr[i] << std::endl;

    return stream;
}
