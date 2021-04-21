#ifndef CLASS_STACK_H
#define CLASS_STACK_H

#define DEFAULT_SIZE 20

template<typename T>
class stack {
    private:
        int head;
        int size;
        T* arr;
        void init(int);
        void checkDimension();
    public:
        ~stack();

        /**
         * @brief Stack constructor
         */
        stack();

        /**
         * @brief Creates an object with a specified initial stack size
         *
         * @param size Initial stack size
         */
        stack(int);

        /**
         * @brief Adds an item to the stack
         *
         * @param item The element that is added to the stack
         */
        void push(T);

        /**
         * @brief Pops an item from the top of the stack
         *
         * @return Item from the top of the stack
         */
        T pop();

        /**
         * @brief Pops an item off the top of the stack, without moving the head of the stack
         *
         * @return Item from the top of the stack
         */
        T peek();

        /**
         * @brief Returns the number of items on the stack
         *
         * @return Number of items in the stack
         */
        int count() const {
            return head + 1;
        };

        /**
         * @brief Calculates the arithmetic mean of a stack
         *
         * @return Arithmetic mean of the stack
         */
        T getAverage();

        /**
         * @brief Merges two stacks and sorts the resulting stack
         *
         * @param stack Second stack for concatenation
         * @return A new stack containing two stacks (current and transferred)
         */
        stack<T> concat(const stack<T>& stack);

        bool operator<(const stack<T>& right);
        bool operator>(const stack<T>& right);
        bool operator==(const stack<T>& right);
        bool operator!=(const stack<T>& right);
        bool operator<=(const stack<T>& right);
        bool operator>=(const stack<T>& right);

        template<class U>
        friend std::ostream& operator<<(std::ostream& stream, const stack<U>& stack);
};

#endif
