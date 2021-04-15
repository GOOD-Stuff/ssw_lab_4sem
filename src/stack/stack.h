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
        stack();
        stack(int);
        void push(T);
        T pop();
        T peek();
        int count() const {
            return head + 1;
        };
        T getAverage();
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
