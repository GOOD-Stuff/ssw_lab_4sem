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
        int count();
        void print();
        bool operator<(stack<T> right);
};
