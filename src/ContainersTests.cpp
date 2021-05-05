#include <iostream>
#include <ctime>
#include <stack>
#include <queue>
#include <vector>

#include "ContainersTests.h"
#include "Stack.h"
#include "Queue.h"
#include "Vector.h"
#include "Timer.h"

using std::cout;

#define REPEATS 5000000
#define LINE "*********************************************************************\n\n"

int Random(int min, int max)
{
	return min + rand() % (max - min);
}

const char* BoolToString(bool expression)
{
	return expression ? "true" : "false";
}

void TestStack()
{
	cout << "Compare STL stack and NEW stack.\nNumber of loop repeats for each method: " << REPEATS << "\nPlease, wait...\n\n";

	std::stack<int> stl_stack;
	Stack<int> new_stack;

	Timer timer;

	for (size_t i = 0; i < REPEATS; i++)
		stl_stack.push(i);

	cout << "STL stack push time: " << timer.GetElapsed_ms() << " ms\n";

	timer.Restart();

	for (size_t i = 0; i < REPEATS; i++)
		new_stack.push(i);

	cout << "NEW stack push time: " << timer.GetElapsed_ms() << " ms\n\n";

	timer.Restart();

	for (size_t i = 0; i < REPEATS; i++)
		int top = stl_stack.top();

	cout << "STL stack top time: " << timer.GetElapsed_ms() << " ms\n";

	timer.Restart();

	for (size_t i = 0; i < REPEATS; i++)
		int top = new_stack.top();

	cout << "NEW stack top time: " << timer.GetElapsed_ms() << " ms\n\n";

	timer.Restart();

	for (size_t i = 0; i < REPEATS; i++)
		stl_stack.pop();

	cout << "STL stack pop time: " << timer.GetElapsed_ms() << " ms\n";

	timer.Restart();

	for (size_t i = 0; i < REPEATS; i++)
		new_stack.pop();

	cout << "NEW stack pop time: " << timer.GetElapsed_ms() << " ms\n\n";

	std::stack<int> stl_stack_cmp_1;
	std::stack<int> stl_stack_cmp_2;

	Stack<int> new_stack_cmp_1;
	Stack<int> new_stack_cmp_2;

	int repeats_count_1 = Random(2, 10);
	int repeats_count_2 = Random(2, 10);

	for (size_t i = 0; i <= repeats_count_1; i++)
	{
		int number = Random(10, 50);
		stl_stack_cmp_1.push(number);
		new_stack_cmp_1.push(number);
	}

	for (size_t i = 0; i <= repeats_count_2; i++)
	{
		int number = Random(10, 50);
		stl_stack_cmp_2.push(number);
		new_stack_cmp_2.push(number);
	}

	cout << "Checking comparison operators.\n\n";

	cout << "Stack 1:\n\n" << new_stack_cmp_1 << "\n";
	cout << "Stack 2:\n\n" << new_stack_cmp_2 << "\n";

	cout << "First bool - STL stack result, second bool - NEW stack result.\n\n";

	cout << "Stack 1 == Stack 2:\t" << BoolToString(stl_stack_cmp_1 == stl_stack_cmp_2) << "\t" << BoolToString(new_stack_cmp_1 == new_stack_cmp_2) << "\n";
	cout << "Stack 1 != Stack 2:\t" << BoolToString(stl_stack_cmp_1 != stl_stack_cmp_2) << "\t" << BoolToString(new_stack_cmp_1 != new_stack_cmp_2) << "\n\n";

	cout << "Stack 1 < Stack 2:\t" << BoolToString(stl_stack_cmp_1 < stl_stack_cmp_2) << "\t" << BoolToString(new_stack_cmp_1 < new_stack_cmp_2) << "\n";
	cout << "Stack 1 > Stack 2:\t" << BoolToString(stl_stack_cmp_1 > stl_stack_cmp_2) << "\t" << BoolToString(new_stack_cmp_1 > new_stack_cmp_2) << "\n\n";

	cout << "Stack 1 <= Stack 2:\t" << BoolToString(stl_stack_cmp_1 <= stl_stack_cmp_2) << "\t" << BoolToString(new_stack_cmp_1 <= new_stack_cmp_2) << "\n";
	cout << "Stack 1 >= Stack 2:\t" << BoolToString(stl_stack_cmp_1 >= stl_stack_cmp_2) << "\t" << BoolToString(new_stack_cmp_1 >= new_stack_cmp_2) << "\n\n";
	cout << LINE;
}

void TestQueue()
{
	cout << "Compare STL queue and NEW queue.\nNumber of loop repeats for each method: " << REPEATS << "\nPlease, wait...\n\n";

	std::queue<int> stl_queue;
	Queue<int> new_queue;

	Timer timer;

	for (size_t i = 0; i < REPEATS; i++)
		stl_queue.push(i);

	cout << "STL queue push time: " << timer.GetElapsed_ms() << " ms\n";

	timer.Restart();

	for (size_t i = 0; i < REPEATS; i++)
		new_queue.push(i);

	cout << "NEW queue push time: " << timer.GetElapsed_ms() << " ms\n\n";

	timer.Restart();

	for (size_t i = 0; i < REPEATS; i++)
		int top = stl_queue.back();

	cout << "STL queue back time: " << timer.GetElapsed_ms() << " ms\n";

	timer.Restart();

	for (size_t i = 0; i < REPEATS; i++)
		int top = new_queue.back();

	cout << "NEW queue back time: " << timer.GetElapsed_ms() << " ms\n\n";

	timer.Restart();

	for (size_t i = 0; i < REPEATS; i++)
		stl_queue.pop();

	cout << "STL queue pop time: " << timer.GetElapsed_ms() << " ms\n";

	timer.Restart();

	for (size_t i = 0; i < REPEATS; i++)
		new_queue.pop();

	cout << "NEW queue pop time: " << timer.GetElapsed_ms() << " ms\n\n";

	std::queue<int> stl_queue_cmp_1;
	std::queue<int> stl_queue_cmp_2;

	Queue<int> new_queue_cmp_1;
	Queue<int> new_queue_cmp_2;

	int repeats_count_1 = Random(2, 10);
	int repeats_count_2 = Random(2, 10);

	for (size_t i = 0; i <= repeats_count_1; i++)
	{
		int number = Random(10, 50);
		stl_queue_cmp_1.push(number);
		new_queue_cmp_1.push(number);
	}

	for (size_t i = 0; i <= repeats_count_2; i++)
	{
		int number = Random(10, 50);
		stl_queue_cmp_2.push(number);
		new_queue_cmp_2.push(number);
	}

	cout << "Checking comparison operators.\n\n";

	cout << "Queue 1:\n\n" << new_queue_cmp_1 << "\n";
	cout << "Queue 2:\n\n" << new_queue_cmp_2 << "\n";

	cout << "First bool - STL queue result, second bool - NEW queue result.\n\n";

	cout << "Queue 1 == Queue 2:\t" << BoolToString(stl_queue_cmp_1 == stl_queue_cmp_2) << "\t" << BoolToString(new_queue_cmp_1 == new_queue_cmp_2) << "\n";
	cout << "Queue 1 != Queue 2:\t" << BoolToString(stl_queue_cmp_1 != stl_queue_cmp_2) << "\t" << BoolToString(new_queue_cmp_1 != new_queue_cmp_2) << "\n\n";

	cout << "Queue 1 < Queue 2:\t" << BoolToString(stl_queue_cmp_1 < stl_queue_cmp_2) << "\t" << BoolToString(new_queue_cmp_1 < new_queue_cmp_2) << "\n";
	cout << "Queue 1 > Queue 2:\t" << BoolToString(stl_queue_cmp_1 > stl_queue_cmp_2) << "\t" << BoolToString(new_queue_cmp_1 > new_queue_cmp_2) << "\n\n";

	cout << "Queue 1 <= Queue 2:\t" << BoolToString(stl_queue_cmp_1 <= stl_queue_cmp_2) << "\t" << BoolToString(new_queue_cmp_1 <= new_queue_cmp_2) << "\n";
	cout << "Queue 1 >= Queue 2:\t" << BoolToString(stl_queue_cmp_1 >= stl_queue_cmp_2) << "\t" << BoolToString(new_queue_cmp_1 >= new_queue_cmp_2) << "\n\n";
	cout << LINE;
}

void TestVector()
{
	cout << "Compare STL vector and NEW vector.\nNumber of loop repeats for each method: " << REPEATS << "\nPlease, wait...\n\n";

	std::vector<int> stl_vector;
	Vector<int> new_vector;

	Timer timer;

	for (size_t i = 0; i < REPEATS; i++)
		stl_vector.push_back(i);

	cout << "STL vector push back time: " << timer.GetElapsed_ms() << " ms\n";

	timer.Restart();

	for (size_t i = 0; i < REPEATS; i++)
		new_vector.push_back(i);

	cout << "NEW vector push back time: " << timer.GetElapsed_ms() << " ms\n\n";

	timer.Restart();

	for (size_t i = 0; i < REPEATS; i++)
		stl_vector.pop_back();

	cout << "STL vector pop back time: " << timer.GetElapsed_ms() << " ms\n";

	timer.Restart();

	for (size_t i = 0; i < REPEATS; i++)
		new_vector.pop_back();

	cout << "NEW vector pop back time: " << timer.GetElapsed_ms() << " ms\n\n";

	timer.Restart();

	for (size_t i = 0; i < REPEATS; i++)
		stl_vector.insert(stl_vector.begin() + i, i);

	cout << "STL vector insert time: " << timer.GetElapsed_ms() << " ms\n";

	timer.Restart();

	for (size_t i = 0; i < REPEATS; i++)
		new_vector.insert(i, i);

	cout << "NEW vector insert time: " << timer.GetElapsed_ms() << " ms\n\n";
	cout << LINE;

	std::vector<int> stl_vector_cmp_1;
	std::vector<int> stl_vector_cmp_2;

	Vector<int> new_vector_cmp_1;
	Vector<int> new_vector_cmp_2;

	int repeats_count_1 = Random(2, 10);
	int repeats_count_2 = Random(2, 10);

	for (size_t i = 0; i <= repeats_count_1; i++)
	{
		int number = Random(10, 50);
		stl_vector_cmp_1.push_back(number);
		new_vector_cmp_1.push_back(number);
	}

	for (size_t i = 0; i <= repeats_count_2; i++)
	{
		int number = Random(10, 50);
		stl_vector_cmp_2.push_back(number);
		new_vector_cmp_2.push_back(number);
	}

	cout << "Checking comparison operators.\n\n";

	cout << "Vector 1:\n\n" << new_vector_cmp_1 << "\n";
	cout << "Vector 2:\n\n" << new_vector_cmp_2 << "\n";

	cout << "First bool - STL vector result, second bool - NEW vector result.\n\n";

	cout << "Vector 1 == Vector 2:\t" << BoolToString(stl_vector_cmp_1 == stl_vector_cmp_2) << "\t" << BoolToString(new_vector_cmp_1 == new_vector_cmp_2) << "\n";
	cout << "Vector 1 != Vector 2:\t" << BoolToString(stl_vector_cmp_1 != stl_vector_cmp_2) << "\t" << BoolToString(new_vector_cmp_1 != new_vector_cmp_2) << "\n\n";

	cout << "Vector 1 < Vector 2:\t" << BoolToString(stl_vector_cmp_1 < stl_vector_cmp_2) << "\t" << BoolToString(new_vector_cmp_1 < new_vector_cmp_2) << "\n";
	cout << "Vector 1 > Vector 2:\t" << BoolToString(stl_vector_cmp_1 > stl_vector_cmp_2) << "\t" << BoolToString(new_vector_cmp_1 > new_vector_cmp_2) << "\n\n";

	cout << "Vector 1 <= Vector 2:\t" << BoolToString(stl_vector_cmp_1 <= stl_vector_cmp_2) << "\t" << BoolToString(new_vector_cmp_1 <= new_vector_cmp_2) << "\n";
	cout << "Vector 1 >= Vector 2:\t" << BoolToString(stl_vector_cmp_1 >= stl_vector_cmp_2) << "\t" << BoolToString(new_vector_cmp_1 >= new_vector_cmp_2) << "\n\n";
	cout << LINE;
}

void TestAllContainers()
{
	srand(time(0));
	TestStack();
	TestQueue();
	TestVector();
}