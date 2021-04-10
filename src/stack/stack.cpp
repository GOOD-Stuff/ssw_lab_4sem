#include <iostream>
#include "stack.h"

template<typename T>
stack<T>::stack() {
    this->init(DEFAULT_SIZE);
}

template<typename T>
stack<T>::stack(int size) {
    this->init(size);
}

template<typename T>
void stack<T>::init(int size) {
    this->size = size;
    this->head = -1;
    arr = new T[this->size];
}

template<typename T>
int stack<T>::count() {
    return this->head + 1;
}

template<typename T>
void stack<T>::checkDimension() {
    if(this->size - this->count() == 0) {
        this->size += DEFAULT_SIZE;
        T* _arr = new T[this->size];

        for(int i = 0; i < this->size - DEFAULT_SIZE; i++)
            _arr[i] = arr[i];

        delete this->arr;
        this->arr = _arr;
    }
}

template<typename T>
void stack<T>::push(T item) {
    this->checkDimension();
    this->arr[++this->head] = item;
}

template<typename T>
T stack<T>::pop() {
    if(this->head == -1)
        throw "Stack is empty";

    return this->arr[this->head--];
}

template<typename T>
T stack<T>::peek() {
    if(this->head == -1)
        throw "Stack is empty";

    return this->arr[this->head];
}

template<typename T>
void stack<T>::print() {
    std::cout << "Count: " << this->count() << std::endl;

    for(int i = this->head; i >= 0; i--)
		std::cout << i << ": " << this->arr[i] << std::endl;
}

template<typename T>
bool stack<T>::operator<(stack<T> right) {
    int count = this->count() > right.count() ? right->count() : this->count();

    for(i = 0; i < count; i++) {
        if(this->arr[i] == right->arr[i])
            continue;

        return this->arr[i] < right->arr[i];
    }

    return this->count() > right.count() ? true : false;
}
