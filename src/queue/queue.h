#include <iostream>

#ifndef CLASS_QUEUE_INCLUDED
#define CLASS_QUEUE_INCLUDED

template<typename T>
class Queue
{
private:
	static constexpr int ADDITION {4096};
	T* data {nullptr};
	int size {ADDITION};
	int start_index {0};
	int end_index = {0};
	T& at(int index) const;

public:
	Queue();
	Queue(int size);
	~Queue();

	void push(T value);
	void pop();
	T& peek();

	float get_arithmetic_mean();
	Queue concat_sort(const Queue& queue);

	Queue& operator = (const Queue& queue);

	bool isEmpty() const;
	bool operator == (const Queue& queue);
	bool operator != (const Queue& queue);
	bool operator < (const Queue& queue);
	bool operator > (const Queue& queue);
	bool operator <= (const Queue& queue);
	bool operator >= (const Queue& queue);

	/**
    * @brief Returns the number of items on the queue
    *
    * @return Number of items in the queue
    */
	int count() const
	{
	    return end_index >= start_index ? end_index - start_index : size - start_index + end_index;
	};

    template<class U>
	friend std::ostream& operator << (std::ostream& stream, const Queue<U>& queue);
};

template<typename T>
Queue<T>::Queue()
{
    data = new int[ADDITION];
}

/**
* @brief Creates an object with a specified initial queue size
*
* @param size Initial queue size
*/
template<typename T>
Queue<T>::Queue(int size)
{
    this->size = size;
    data = new int[size];
}

template<typename T>
Queue<T>::~Queue()
{
    if (data)
        delete[] data;
}

/**
* @brief Is the queue empty
*
* @return empty - true, not empty - false
*/
template<typename T>
bool Queue<T>::isEmpty() const
{
	return start_index == end_index;
}

/**
* @brief Adds an item to the queue
*
* @param item The element that is added to the queue
*/
template<typename T>
void Queue<T>::push(T value)
{
	data[end_index++] = value;

	if(end_index == size)
		end_index = 0;

    if(start_index == end_index) {
        int old_size = size;
        size += ADDITION;
        T* _arr = new T[size];

        int k = 0;

        for(int i = start_index; i < old_size; i++)
            _arr[k++] = data[i];

        for(int i = 0; i < end_index; i++)
            _arr[k++] = data[i];

        delete[] data;
        data = _arr;
        start_index = 0;
        end_index = k;
    }
}

template<typename T>
T& Queue<T>::at(int index) const {
    if(isEmpty())
        throw new std::runtime_error("Queue is empty");

    return data[(start_index + index) % size];
}

/**
* @brief Pops an item from the head of the queue
*
* @return Item from the head of the queue
*/
template<typename T>
void Queue<T>::pop()
{
    if(isEmpty())
        throw new std::runtime_error("Queue is empty");

    if(++start_index == size)
        start_index = 0;
}

/**
* @brief Pops an item off the head of the queue, without moving the head of the queue
*
* @return Item from the head of the queue
*/
template<typename T>
T& Queue<T>::peek()
{
    if(isEmpty())
        throw new std::runtime_error("Queue is empty");

    return data[start_index];
}


/**
* @brief Calculates the arithmetic mean of a queue
*
* @return Arithmetic mean of the queue
*/
template<typename T>
float Queue<T>::get_arithmetic_mean()
{
    float sum = 0.0f;

    for (int i = 0; i < count(); i++)
        sum += data[i];

    return sum / count();
}
/**
* @brief Merges two queue and sorts the resulting queue
*
* @param queue Second queue for concatenation
* @return A new queue containing two queues (current and transferred)
*/
template<typename T>
Queue<T> Queue<T>::concat_sort(const Queue<T>& queue)
{
    Queue<T> new_queue(size + queue.size);

    for (int i = 0; i < count(); i++)
        new_queue.push(data[i]);

    for (int i = 0; i < count(); i++)
        new_queue.push(queue.data[i]);

    for (int i = 0; i < new_queue.count(); i++) {
		for (int j = 0; j < new_queue.count() - 1; j++) {
			if (new_queue.data[j] < new_queue.data[j + 1]) {
				T temp = new_queue.data[j];
				new_queue.data[j] = new_queue.data[j + 1];
				new_queue.data[j + 1] = temp;
			}
		}
	}

    return new_queue;
}

template<typename T>
Queue<T>& Queue<T>::operator = (const Queue<T>& queue)
{
    if (data != nullptr)
        delete[] data;

    size = queue.size;
    data = new int[size];
    start_index = queue.start_index;
    end_index = queue.end_index;

    for (int i = 0; i < queue.count(); i++)
        data[i] = queue.data[i];

    return *this;
}

template<typename T>
bool Queue<T>::operator == (const Queue<T>& queue)
{
    if (count() != queue.count())
        return false;

    for(int i = 0; i < count(); i++) {
        if(at(i) != queue.at(i))
            return false;
    }

    return true;
}

template<typename T>
bool Queue<T>::operator != (const Queue<T>& queue)
{
    return !(*this == queue);
}

template<typename T>
bool Queue<T>::operator<(const Queue<T>& queue) {
    int thisCount = count();
    int rightCount = queue.count();
    int cnt = (thisCount > rightCount) ? rightCount : thisCount;

    for(int i = 0; i < cnt; i++) {
        int q1 = at(i);
        int q2 = queue.at(i);

        if(q1 == q2)
            continue;

        return q1 < q2;
    }

    return rightCount > thisCount ? true : false;
}

template<typename T>
bool Queue<T>::operator>(const Queue<T>& queue) {
    int thisCount = count();
    int rightCount = queue.count();
    int cnt = (thisCount > rightCount) ? rightCount : thisCount;

    for(int i = 0; i < cnt; i++) {
        int q1 = at(i);
        int q2 = queue.at(i);

        if(q1 == q2)
            continue;

        return q1 > q2;
    }

    return thisCount > rightCount ? true : false;
}

template<typename T>
bool Queue<T>::operator <= (const Queue<T>& queue)
{
    return (*this < queue) || (*this == queue);
}

template<typename T>
bool Queue<T>::operator >= (const Queue<T>& queue)
{
    return (*this > queue) || (*this == queue);
}

template<class T>
std::ostream& operator << (std::ostream& stream, const Queue<T>& queue)
{
    for (int i = 0; i < queue.count(); i++)
        stream << queue.at(i) << " ";

    return stream;
}

#endif
