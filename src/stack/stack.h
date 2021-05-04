#include <iostream>

#ifndef CLASS_STACK_H
#define CLASS_STACK_H

template<typename T>
class Stack {
    private:
        static constexpr int DEFAULT_SIZE {1024};
        int head = -1;
        int size = DEFAULT_SIZE;
        T* arr = nullptr;
        void init(int);
        void checkDimension();
    public:
        Stack();
        explicit Stack(int);
        ~Stack();
        void push(T);
        T pop();
        T& peek();
        float getAverage();
        Stack<T> concat(const Stack<T>& stack);

        bool operator<(const Stack<T>& right);
        bool operator>(const Stack<T>& right);
        bool operator==(const Stack<T>& right);
        bool operator!=(const Stack<T>& right);
        bool operator<=(const Stack<T>& right);
        bool operator>=(const Stack<T>& right);

        /**
         * @brief Returns the number of items on the stack
         *
         * @return Number of items in the stack
         */
        int count() const {
            return head + 1;
        };

        template<class U>
        friend std::ostream& operator<<(std::ostream& stream, const Stack<U>& stack);
};

template<typename T>
Stack<T>::Stack() {
    arr = new T[DEFAULT_SIZE];
}

/**
* @brief Creates an object with a specified initial stack size
*
* @param size Initial stack size
*/
template<typename T>
Stack<T>::Stack(int size) {
    this->size = size;
    arr = new T[size];
}

template<typename T>
void Stack<T>::checkDimension() {
    if(size - head == 1) {
        size += DEFAULT_SIZE;
        T* _arr = new T[size];

        for(int i = 0; i < size - DEFAULT_SIZE; i++)
            _arr[i] = arr[i];

        delete[] arr;
        arr = _arr;
    }
}

/**
* @brief Adds an item to the stack
*
* @param item The element that is added to the stack
*/
template<typename T>
void Stack<T>::push(T item) {
    checkDimension();
    arr[++head] = item;
}

/**
* @brief Pops an item from the top of the stack
*
* @return Item from the top of the stack
*/
template<typename T>
T Stack<T>::pop() {
    if(head == -1)
        throw new std::runtime_error("Stack is empty");

    return arr[head--];
}

/**
* @brief Pops an item off the top of the stack, without moving the head of the stack
*
* @return Item from the top of the stack
*/
template<typename T>
T& Stack<T>::peek() {
    if(head == -1)
        throw new std::runtime_error("Stack is empty");

    return arr[head];
}


/**
* @brief Merges two stacks and sorts the resulting stack
*
* @param stack Second stack for concatenation
* @return A new stack containing two stacks (current and transferred)
*/
template<typename T>
Stack<T> Stack<T>::concat(const Stack<T>& st) {
    Stack<T> newStack(head + st.head + 2 + DEFAULT_SIZE);

    for(int i = 0; i <= head; i++)
        newStack.push(arr[i]);

    for(int i = 0; i <= st.head; i++)
        newStack.push(st.arr[i]);

    for (int i = 0; i <= newStack.head; i++) {
		for (int j = 0; j < newStack.head; j++) {
			if (newStack.arr[j] < newStack.arr[j + 1]) {
				T temp = newStack.arr[j];
				newStack.arr[j] = newStack.arr[j + 1];
				newStack.arr[j + 1] = temp;
			}
		}
	}

    return newStack;
}


/**
* @brief Calculates the arithmetic mean of a stack
*
* @return Arithmetic mean of the stack
*/
template<typename T>
float Stack<T>::getAverage() {
    float sum = (float)arr[0];

    for(int i = 1; i <= head; i++)
        sum += (float)arr[i];

    return sum / count();
}

template<typename T>
bool Stack<T>::operator<(const Stack<T>& right) {
    int cnt = (head > right.head) ? right.head : head;

    for(int i = 0; i <= cnt; i++) {
        if(arr[i] == right.arr[i])
            continue;

        return arr[i] < right.arr[i];
    }

    return right.head > head;
}

template<typename T>
bool Stack<T>::operator>(const Stack<T>& right) {
    int cnt = (head > right.head) ? right.head : head;

    for(int i = 0; i <= cnt; i++) {
        if(arr[i] == right.arr[i])
            continue;

        return arr[i] > right.arr[i];
    }

    return head > right.head;
}

template<typename T>
bool Stack<T>::operator==(const Stack<T>& right) {
    if(head != right.head)
        return false;

    for(int i = 0; i <= head; i++) {
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

template<typename T>
Stack<T>::~Stack() {
    if(arr)
        delete[] arr;
}

#endif
