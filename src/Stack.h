#ifndef STACK_H
#define STACK_H
#define DEF_SIZE 32768
template <typename T>
class Stack {
private:
	T* arr; // Pointer to an array with stack elements
	int top, size; // Top of stack number and stack size
	void checkOverflow(); // Overflow Checking and Stack Growth
public:
	Stack(); // Create object with default size
	
	Stack(int size); // Creating an object with arbitrary size
	~Stack(); //
	void push(T elem); // Adding an item to the stack

	T pop(); // Removing and returning the top of the stack

	T peek(); // Returning the top of the stack

	int count() const; // Returning the number of elements on a stack

	bool isMount(int start_i);//  Determination of the mountain sequence

	void swap(Stack<T> &s);

	void print();

	// Lexicographic comparison operators
	bool operator<( const Stack<T>& right) const;
	bool operator>(const Stack<T>& right) const;
	bool operator==(const Stack<T>& right) const;
	bool operator!=(const Stack<T>& right) const ;
	bool operator<=(const Stack<T>& right) const;
	bool operator>=(const Stack<T>& right) const;

};

#endif
