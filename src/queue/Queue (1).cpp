#include "Queue.h"
#define ADDITION 256

Queue::Queue()
{
    data = new int[ADDITION];
    size = 0;
    start_index = 0;
}

Queue::Queue(const Queue& queue)
{
    *this = queue;
}

Queue::~Queue()
{
    if (data)
        delete[] data;
}

void Queue::push(int value)
{
    if (size != 0 && size % ADDITION == 0) {
        int* new_data = new int[size + ADDITION];

        for (int i = 0; i < size; i++) {
            new_data[i] = data[i];
        }

        new_data[size++] = value;
        delete[] data;

        data = new_data;
        start_index = 0;
    }
    else {
        data[start_index + size++] = value;
    }
}

void Queue::pop()
{
    if (size == 0) {
        return;
    }

    size--;
    start_index++;

    if (start_index >= ADDITION) {
        int* new_data = new int[size];
        int j = 0;

        for (int i = start_index; i < size + start_index; i++) {
            new_data[j++] = data[i];
        }

        delete[] data;
        data = new_data;

        start_index = 0;
    }
}

int& Queue::peek()
{
    return data[start_index];
}

int Queue::count()
{
    return size;
}

float Queue::get_arithmetic_mean()
{
    float sum = 0.0f;

    for (int i = 0; i < size; i++)
        sum += data[i];

    return sum / size;
}

Queue Queue::concat_sort(const Queue& queue)
{
    Queue new_queue;

    new_queue.size = size + queue.size;
    new_queue.data = new int[new_queue.size];

    int k = 0;

    for (int i = start_index; i < start_index + size; i++) {
        new_queue.data[k++] = data[i];
    }

    for (int i = queue.start_index; i < queue.start_index + queue.size; i++) {
        new_queue.data[k++] = queue.data[i];
    }

    for (int i = 0; i < new_queue.size; i++) {
        for (int j = 0; j < new_queue.size - 1; j++) {
            if (new_queue.data[j] > new_queue.data[j + 1]) {
                int temp = new_queue.data[j];
                new_queue.data[j] = new_queue.data[j + 1];
                new_queue.data[j + 1] = temp;
            }
        }
    }

    return new_queue;
}

Queue& Queue::operator = (const Queue& queue)
{
    if (data != nullptr) {
        delete[] data;
    }

    size = queue.size;
    data = new int[size];

    int k = 0;

    for (int i = queue.start_index; i < queue.start_index + size; i++) {
        data[k++] = queue.data[i];
    }

    return *this;
}

bool Queue::operator == (const Queue& queue)
{
    if (size != queue.size) {
        return false;
    }

    int min_size = size < queue.size ? size : queue.size;

    for (int i = 0; i < min_size; i++) {
        if (data[start_index + i] != queue.data[queue.start_index + i]) {
            return false;
        }
    }

    return true;
}

bool Queue::operator != (const Queue& queue)
{
    return !(*this == queue);
}

bool Queue::operator < (const Queue& queue)
{
    int min_size = size < queue.size ? size : queue.size;

    for (int i = 0; i < min_size; i++) {
        if (data[start_index + i] < queue.data[queue.start_index + i]) {
            return true;
        }
    }

    return false;
}

bool Queue::operator > (const Queue& queue)
{
    return !(*this < queue) && (*this != queue);
}

bool Queue::operator <= (const Queue& queue)
{
    return (*this < queue) || (*this == queue);
}

bool Queue::operator >= (const Queue& queue)
{
    return (*this > queue) || (*this == queue);
}

ostream& operator << (ostream& stream, Queue& queue)
{
    for (int i = queue.start_index; i < queue.start_index + queue.size; i++) {
        stream << queue.data[i] << "\n";
    }

    return stream;
}