#ifndef QUEUE_H
#define QUEUE_H
#include <stdexcept>
#include "ostream"
template <typename T>
class Queue {
private:
	T* arr;// Pointer to an array with queue elements
	int size; // Queue size
	int last; // Last element index
	static constexpr int DEF_SIZE{ 2 }; // Initial size
	void checkOverflow(); // Overflow Checking and Queue Growth
public:
	Queue(); // constructor
	~Queue(); // destructor

	void push(T elem); // Adding an item to the end of the queue

	T pop(); // Retrieving and Deleting the Head of the Queue Element

	T& peek(); // Get the last item in the queue

	int count() const; //Real size of queue

	bool isMount();//  Determination of the mountain sequence 
	void swap(Queue<T>& q); // Exchange between structures

	// Lexicographic comparison operators
	bool operator<(const Queue<T>& right) const;
	bool operator>(const Queue<T>& right) const;
	bool operator==(const Queue<T>& right) const;
	bool operator!=(const Queue<T>& right) const;
	bool operator<=(const Queue<T>& right) const;
	bool operator>=(const Queue<T>& right) const;

	friend std::ostream& operator<<(std::ostream& o, const Queue<T>& r) {
		for (int i = 0; i <= r.last; i++) {
			o << r.arr[i] << " ";
		}
		o << "\n";
		return o;
	}
};

template<typename T>
void Queue<T>::checkOverflow() {
	if (last + 1 == size) {
		T* tmp = arr;
		size *= DEF_SIZE;
		arr = new T[size];
		for (int i = 0; i <= last; i++) {
			arr[i] = tmp[i];
		}
		delete[] tmp;
	}
}

template<typename T>
Queue<T>::Queue() {
	size = DEF_SIZE;
	arr = new T[size];
	last = -1;
}

template<typename T>
Queue<T>::~Queue() {
	if (arr != nullptr)
		delete[] arr;
}
template<typename T>
void Queue<T>::push(T elem) {
	checkOverflow();
	last++;
	arr[last] = elem;
}

template<typename T>
T Queue<T>::pop() {
	if (last == -1) {
		throw std::runtime_error("Queue is empty! Pop failed");
	}
	T elem = arr[0];

	T* tmp = arr;
	arr = new T[size];
	for (int i = 1; i <= last; i++) {
		arr[i - 1] = tmp[i];
	}
	delete[] tmp;
	last--;
	return elem;
}
template<typename T>
T& Queue<T>::peek() {
	if (last == -1) {
		throw std::runtime_error("Queue is empty! Operation 'peek' failed.");
	}
	return arr[last];
}

template<typename T>
int Queue<T>::count() const {
	return size;
}

template<typename T>
bool Queue<T>::isMount() {
	if (last >= 3) {
		T max = arr[0];
		T max_i;
		for (int i = 0; i <= last; i++) {
			if (arr[i] > max) {
				max = arr[i];
				max_i = i;
			}
		}
		for (int i = 0; i < max_i; i++) {
			if (arr[i] > arr[i + 1])
				return false;
		}
		for (int i = last; i != max_i; i--) {
			if (arr[i] > arr[i - 1])
				return false;
		}
		return true;
	}
	return false;
}

template<typename T>
void Queue<T>::swap(Queue<T>& v) {
	if (v == *this)
		throw std::runtime_error("Can't swap the same object");
	T* tmp_arr = arr;
	int tmp_size = size;
	int tmp_last = last;

	arr = v.arr;
	size = v.size;
	last = v.last;

	v.arr = tmp_arr;
	v.size = tmp_size;
	v.last = tmp_last;
}


template <typename T>
bool Queue<T>::operator < (const Queue<T>& right) const {
	int thisSize = last;
	int rightSize = right.last;
	int size_b = (thisSize > rightSize) ? rightSize : thisSize;
	for (int i = 0; i < size_b; i++) {
		if (arr[i] != right.arr[i])
			return arr[i] < right.arr[i];
	}
	return thisSize < rightSize;
}

template <typename T>
bool Queue<T>::operator == (const Queue<T>& right) const {
	if (last != right.last)
		return false;
	for (int i = 0; i <= last; i++) {
		if (arr[i] != right.arr[i])
			return false;
	}
	return true;
}

template <typename T>
bool Queue<T>::operator != (const Queue<T>& right) const {
	return !(*this == right);
}

template <typename T>
bool Queue<T>::operator > (const Queue<T>& right) const {
	return !(*this < right) && *this != right;
}

template <typename T>
bool Queue<T>::operator >= (const Queue<T>& right) const {
	return (*this > right) || (*this == right);
}
template <typename T>
bool Queue<T>::operator <= (const Queue<T>& right) const {
	return (*this < right) || (*this == right);
}
#endif
