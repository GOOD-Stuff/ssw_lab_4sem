#ifndef QUEUE_H
#define QUEUE_H
#define DEF_SIZE 32768 // Initial size
#include <iostream>
using namespace std;


template <typename T>
class Queue {
private:
	T* arr;// Pointer to an array with queue elements
	int size, last; // Queue size and last element index
	void checkOverflow(); // Overflow Checking and Queue Growth
public:
	Queue(); // constructor
	~Queue(); // destructor

	void push(T elem); // Adding an item to the end of the queue

	T pop(); // Retrieving and Deleting the Head of the Queue Element

	T peek(); // Get the last item in the queue

	int count() const; //Number of items in the queue

	bool isMount(int start_i);//  Determination of the mountain sequence 
	void swap(Queue<T>& q); // Exchange between structures


	// Lexicographic comparison operators
	bool operator<(const Queue<T>& right) const;
	bool operator>(const Queue<T>& right) const;
	bool operator==(const Queue<T>& right) const;
	bool operator!=(const Queue<T>& right) const;
	bool operator<=(const Queue<T>& right) const;
	bool operator>=(const Queue<T>& right) const;
};
#endif
