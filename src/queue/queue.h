#ifndef CLASS_QUEUE_INCLUDED
#define CLASS_QUEUE_INCLUDED

#include <ostream>
using std::ostream;

class Queue
{
private:
	int* data;
	int size;
	int start_index;

public:
	Queue();
	Queue(const Queue& queue);
	~Queue();

	void push(int value);
	void pop();

	int& peek();
	int count();

	float get_arithmetic_mean();
	Queue concat_sort(const Queue& queue);

	Queue& operator = (const Queue& queue);

	bool operator == (const Queue& queue);
	bool operator != (const Queue& queue);

	bool operator < (const Queue& queue);
	bool operator > (const Queue& queue);

	bool operator <= (const Queue& queue);
	bool operator >= (const Queue& queue);

	friend ostream& operator << (ostream& stream, const Queue& queue);
};

#endif
