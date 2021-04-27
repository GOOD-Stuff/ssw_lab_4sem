#include <iostream>
#include <ctime>
using std::cout;

#include "ContainersTests.h"
#include "Stack.h"
#include "Queue.h"
#include "Vector.h"

int Random(int min, int max) {
	return min + rand() % (max - min);
}

const char* BoolToString(bool expression)
{
	return expression ? "true" : "false";
}

void TestStack()
{
	srand(time(0));

	Stack<int> stack_1;
	Stack<int> stack_2;

	int repeats_count_1 = Random(2, 10);
	int repeats_count_2 = Random(2, 10);

	for (size_t i = 0; i <= repeats_count_1; i++)
		stack_1.push(Random(10, 50));

	for (size_t i = 0; i <= repeats_count_2; i++)
		stack_2.push(Random(10, 50));

	cout << "Stack 1:\n\n" << stack_1 << '\n';
	cout << "Stack 2:\n\n" << stack_2 << '\n';

	cout << "Top elements after called pop():\n\n";

	stack_1.pop();
	stack_2.pop();

	cout << "Stack 1 top: " << stack_1.top() << '\n';
	cout << "Stack 2 top: " << stack_2.top() << "\n\n";

	cout << "Stack 1 == Stack 2: " << BoolToString(stack_1 == stack_2) << '\n';
	cout << "Stack 1 != Stack 2: " << BoolToString(stack_1 != stack_2) << "\n\n";

	cout << "Stack 1 < Stack 2: " << BoolToString(stack_1 < stack_2) << '\n';
	cout << "Stack 1 > Stack 2: " << BoolToString(stack_1 > stack_2) << "\n\n";

	cout << "Stack 1 <= Stack 2: " << BoolToString(stack_1 <= stack_2) << '\n';
	cout << "Stack 1 >= Stack 2: " << BoolToString(stack_1 >= stack_2) << "\n\n";
}

void TestQueue()
{
	srand(time(0));

	Queue<int> queue_1;
	Queue<int> queue_2;

	int repeats_count_1 = Random(2, 10);
	int repeats_count_2 = Random(2, 10);

	for (size_t i = 0; i <= repeats_count_1; i++)
		queue_1.push(Random(10, 50));

	for (size_t i = 0; i <= repeats_count_2; i++)
		queue_2.push(Random(10, 50));

	cout << "Queue 1:\n\n" << queue_1 << '\n';
	cout << "Queue 2:\n\n" << queue_2 << '\n';

	cout << "Top elements after called pop():\n\n";

	queue_1.pop();
	queue_2.pop();

	cout << "Queue 1 top: " << queue_1.begin() << '\n';
	cout << "Queue 2 top: " << queue_2.begin() << "\n\n";

	cout << "Queue 1 == Queue 2: " << BoolToString(queue_1 == queue_2) << '\n';
	cout << "Queue 1 != Queue 2: " << BoolToString(queue_1 != queue_2) << "\n\n";

	cout << "Queue 1 < Queue 2: " << BoolToString(queue_1 < queue_2) << '\n';
	cout << "Queue 1 > Queue 2: " << BoolToString(queue_1 > queue_2) << "\n\n";

	cout << "Queue 1 <= Queue 2: " << BoolToString(queue_1 <= queue_2) << '\n';
	cout << "Queue 1 >= Queue 2: " << BoolToString(queue_1 >= queue_2) << "\n\n";
}

void TestVector()
{
	srand(time(0));

	Vector<int> vector_1;
	Vector<int> vector_2;

	int repeats_count_1 = Random(2, 10);
	int repeats_count_2 = Random(2, 10);

	for (size_t i = 0; i <= repeats_count_1; i++)
		vector_1.push_back(Random(10, 50));

	for (size_t i = 0; i <= repeats_count_2; i++)
		vector_2.push_front(Random(10, 50));

	cout << "Vector 1:\n\n" << vector_1 << '\n';
	cout << "Vector 2:\n\n" << vector_2 << '\n';

	cout << "Vector 1 == Vector 2: " << BoolToString(vector_1 == vector_2) << '\n';
	cout << "Vector 1 != Vector 2: " << BoolToString(vector_1 != vector_2) << "\n\n";

	cout << "Vector 1 < Vector 2: " << BoolToString(vector_1 < vector_2) << '\n';
	cout << "Vector 1 > Vector 2: " << BoolToString(vector_1 > vector_2) << "\n\n";

	cout << "Vector 1 <= Vector 2: " << BoolToString(vector_1 <= vector_2) << '\n';
	cout << "Vector 1 >= Vector 2: " << BoolToString(vector_1 >= vector_2) << "\n\n";

	vector_1.pop_front();
	vector_2.pop_front();

	cout << "Vector 1 front after called pop_front(): " << vector_1.front() << '\n';
	cout << "Vector 2 front after called pop_front(): " << vector_2.front() << "\n\n";

	vector_1.pop_back();
	vector_2.pop_back();

	cout << "Vector 1 back after called pop_back(): " << vector_1.back() << '\n';
	cout << "Vector 2 back after called pop_back(): " << vector_2.back() << "\n\n";

}

#define LINE "*******************************************\n\n"

void TestAllContainers()
{
	TestStack();
	cout << LINE;

	TestQueue();
	cout << LINE;

	TestVector();
	cout << LINE;
}
