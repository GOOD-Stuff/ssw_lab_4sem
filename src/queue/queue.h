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
	~Queue();

	void push(int value);
	void pop();

	int& peek();
	int count();
	
	bool operator == (const Queue& queue);
	bool operator != (const Queue& queue);

	bool operator < (const Queue& queue);
	bool operator > (const Queue& queue);

	bool operator <= (const Queue& queue);
	bool operator >= (const Queue& queue);

	friend ostream& operator << (ostream& stream, Queue& queue);
};

#endif
