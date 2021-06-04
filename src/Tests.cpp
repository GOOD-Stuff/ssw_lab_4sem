#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <stack>
#include <queue>
#include <vector>

using namespace std;

#include "Tests.h"
#include "Stack.h"
#include "Queue.h"
#include "Vector.h"

chrono::steady_clock::time_point CurrentTime()
{
	return chrono::steady_clock::now();
}

long long DeltaTime(const chrono::steady_clock::time_point& point)
{
	return chrono::duration_cast<std::chrono::milliseconds>(CurrentTime() - point).count();
}

string BoolToStr(bool value)
{
	return value ? "true" : "false";
}

int RandInt(int left, int right)
{
	return left + rand() % (right - left);
}

static const int IT_COUNT = 1000000;
static const string UNDERLINE = "--------------------------------------------------------------\n\n";

void RunTests()
{
	cout << "My containers vs STL containers! (" << IT_COUNT << " runs per method)\n\n";

	TestStack();
	TestQueue();
	TestVector();
}

void TestStack()
{
	cout << "My Stack vs STL Stack!\nPlease, wait!\n\n";

	Stack my_stack;
	stack<int> stl_stack;

	/////////////////////////////////////////////////////////////

	auto start = CurrentTime();

	for (int i = 0; i < IT_COUNT; i++)
		my_stack.push(i);

	cout << "My stack push time: " << DeltaTime(start) << " ms\n";

	//////////////////////////

	start = CurrentTime();

	for (int i = 0; i < IT_COUNT; i++)
		stl_stack.push(i);

	cout << "STL stack push time: " << DeltaTime(start) << " ms\n\n";

	/////////////////////////////////////////////////////////////

	start = CurrentTime();

	for (int i = 0; i < IT_COUNT; i++)
		int value = my_stack.peek();

	cout << "My stack peek time: " << DeltaTime(start) << " ms\n";

	//////////////////////////

	start = CurrentTime();

	for (int i = 0; i < IT_COUNT; i++)
		int value = stl_stack.top();

	cout << "STL stack peek time: " << DeltaTime(start) << " ms\n\n";

	/////////////////////////////////////////////////////////////

	start = CurrentTime();

	for (int i = 0; i < IT_COUNT; i++)
		my_stack.pop();

	cout << "My stack pop time: " << DeltaTime(start) << " ms\n";

	//////////////////////////

	start = CurrentTime();

	for (int i = 0; i < IT_COUNT; i++)
		stl_stack.pop();

	cout << "STL stack pop time: " << DeltaTime(start) << " ms\n\n";

	/////////////////////////////////////////////////////////////

	cout << "Testing comparison operators...\n\n";

	Stack my_stack_1;
	Stack my_stack_2;

	stack<int> stl_stack_1;
	stack<int> stl_stack_2;

	int first_cnt = RandInt(3, 8);
	int second_cnt = RandInt(3, 8);

	for (int i = 0; i < first_cnt; i++) {
		int random_value = RandInt(20, 80);
		my_stack_1.push(random_value);
		stl_stack_1.push(random_value);
	}

	for (int i = 0; i < second_cnt; i++) {
		int random_value = RandInt(20, 80);
		my_stack_2.push(random_value);
		stl_stack_2.push(random_value);
	}

	cout << "Stack 1:\n\n" << my_stack_1 << "\n";
	cout << "Stack 2:\n\n" << my_stack_2 << "\n";

	cout << "Left value - my stack result, right value - STL stack result:\n\n";

	cout << "Stack 1 == Stack 2: " << BoolToStr(my_stack_1 == my_stack_2) << " | " << BoolToStr(stl_stack_1 == stl_stack_2) << "\n";
	cout << "Stack 1 != Stack 2: " << BoolToStr(my_stack_1 != my_stack_2) << " | " << BoolToStr(stl_stack_1 != stl_stack_2) << "\n\n";

	cout << "Stack 1 < Stack 2: " << BoolToStr(my_stack_1 < my_stack_2) << " | " << BoolToStr(stl_stack_1 < stl_stack_2) << "\n";
	cout << "Stack 1 <= Stack 2: " << BoolToStr(my_stack_1 <= my_stack_2) << " | " << BoolToStr(stl_stack_1 <= stl_stack_2) << "\n\n";
	
	cout << "Stack 1 > Stack 2: " << BoolToStr(my_stack_1 > my_stack_2) << " | " << BoolToStr(stl_stack_1 > stl_stack_2) << "\n";
	cout << "Stack 1 >= Stack 2: " << BoolToStr(my_stack_1 >= my_stack_2) << " | " << BoolToStr(stl_stack_1 >= stl_stack_2) << "\n\n";

	cout << UNDERLINE;
}

void TestQueue()
{
	cout << "My Queue vs STL Queue!\nPlease, wait!\n\n";

	Queue my_queue;
	queue<int> stl_queue;

	/////////////////////////////////////////////////////////////

	auto start = CurrentTime();

	for (int i = 0; i < IT_COUNT; i++)
		my_queue.push(i);

	cout << "My queue push time: " << DeltaTime(start) << " ms\n";

	//////////////////////////

	start = CurrentTime();

	for (int i = 0; i < IT_COUNT; i++)
		stl_queue.push(i);

	cout << "STL queue push time: " << DeltaTime(start) << " ms\n\n";

	/////////////////////////////////////////////////////////////

	start = CurrentTime();

	for (int i = 0; i < IT_COUNT; i++)
		int value = my_queue.peek();

	cout << "My queue peek time: " << DeltaTime(start) << " ms\n";

	//////////////////////////

	start = CurrentTime();

	for (int i = 0; i < IT_COUNT; i++)
		int value = stl_queue.back();

	cout << "STL queue peek time: " << DeltaTime(start) << " ms\n\n";

	/////////////////////////////////////////////////////////////

	start = CurrentTime();

	for (int i = 0; i < IT_COUNT; i++)
		my_queue.pop();

	cout << "My queue pop time: " << DeltaTime(start) << " ms\n";

	//////////////////////////

	start = CurrentTime();

	for (int i = 0; i < IT_COUNT; i++)
		stl_queue.pop();

	cout << "STL queue pop time: " << DeltaTime(start) << " ms\n\n";

	/////////////////////////////////////////////////////////////

	cout << "Testing comparison operators...\n\n";

	Queue my_queue_1;
	Queue my_queue_2;

	queue<int> stl_queue_1;
	queue<int> stl_queue_2;

	int first_cnt = RandInt(3, 8);
	int second_cnt = RandInt(3, 8);

	for (int i = 0; i < first_cnt; i++) {
		int random_value = RandInt(20, 80);
		my_queue_1.push(random_value);
		stl_queue_1.push(random_value);
	}

	for (int i = 0; i < second_cnt; i++) {
		int random_value = RandInt(20, 80);
		my_queue_2.push(random_value);
		stl_queue_2.push(random_value);
	}

	cout << "Queue 1:\n\n" << my_queue_1 << "\n";
	cout << "Queue 2:\n\n" << my_queue_2 << "\n";

	cout << "Left value - my queue result, right value - STL queue result:\n\n";

	cout << "Queue 1 == Queue 2: " << BoolToStr(my_queue_1 == my_queue_2) << " | " << BoolToStr(stl_queue_1 == stl_queue_2) << "\n";
	cout << "Queue 1 != Queue 2: " << BoolToStr(my_queue_1 != my_queue_2) << " | " << BoolToStr(stl_queue_1 != stl_queue_2) << "\n\n";

	cout << "Queue 1 < Queue 2: " << BoolToStr(my_queue_1 < my_queue_2) << " | " << BoolToStr(stl_queue_1 < stl_queue_2) << "\n";
	cout << "Queue 1 <= Queue 2: " << BoolToStr(my_queue_1 <= my_queue_2) << " | " << BoolToStr(stl_queue_1 <= stl_queue_2) << "\n\n";

	cout << "Queue 1 > Queue 2: " << BoolToStr(my_queue_1 > my_queue_2) << " | " << BoolToStr(stl_queue_1 > stl_queue_2) << "\n";
	cout << "Queue 1 >= Queue 2: " << BoolToStr(my_queue_1 >= my_queue_2) << " | " << BoolToStr(stl_queue_1 >= stl_queue_2) << "\n\n";

	cout << UNDERLINE;
}

void TestVector()
{
	cout << "My Vector vs STL Vector!\nPlease, wait!\n\n";

	Vector my_vector;
	vector<int> stl_vector;

	/////////////////////////////////////////////////////////////

	auto start = CurrentTime();

	for (int i = 0; i < IT_COUNT; i++)
		my_vector.push(i);

	cout << "My vector push time: " << DeltaTime(start) << " ms\n";

	//////////////////////////

	start = CurrentTime();

	for (int i = 0; i < IT_COUNT; i++)
		stl_vector.push_back(i);

	cout << "STL vector push time: " << DeltaTime(start) << " ms\n\n";

	/////////////////////////////////////////////////////////////

	start = CurrentTime();

	for (int i = 0; i < IT_COUNT; i++)
		int value = my_vector.at(i);

	cout << "My vector at time: " << DeltaTime(start) << " ms\n";

	//////////////////////////

	start = CurrentTime();

	for (int i = 0; i < IT_COUNT; i++)
		int value = stl_vector.at(i);

	cout << "STL vector at time: " << DeltaTime(start) << " ms\n\n";

	/////////////////////////////////////////////////////////////

	start = CurrentTime();

	for (int i = 0; i < IT_COUNT; i++)
		my_vector.pop();

	cout << "My vector pop time: " << DeltaTime(start) << " ms\n";

	//////////////////////////

	start = CurrentTime();

	for (int i = 0; i < IT_COUNT; i++)
		stl_vector.pop_back();

	cout << "STL vector pop time: " << DeltaTime(start) << " ms\n\n";

	/////////////////////////////////////////////////////////////

	cout << "Testing comparison operators...\n\n";

	Vector my_vector_1;
	Vector my_vector_2;

	vector<int> stl_vector_1;
	vector<int> stl_vector_2;

	int first_cnt = RandInt(3, 8);
	int second_cnt = RandInt(3, 8);

	for (int i = 0; i < first_cnt; i++) {
		int random_value = RandInt(20, 80);
		my_vector_1.push(random_value);
		stl_vector_1.push_back(random_value);
	}

	for (int i = 0; i < second_cnt; i++) {
		int random_value = RandInt(20, 80);
		my_vector_2.push(random_value);
		stl_vector_2.push_back(random_value);
	}

	cout << "Vector 1:\n\n" << my_vector_1 << "\n";
	cout << "Vector 2:\n\n" << my_vector_2 << "\n";

	cout << "Left value - my vector result, right value - STL vector result:\n\n";

	cout << "Vector 1 == Vector 2: " << BoolToStr(my_vector_1 == my_vector_2) << " | " << BoolToStr(stl_vector_1 == stl_vector_2) << "\n";
	cout << "Vector 1 != Vector 2: " << BoolToStr(my_vector_1 != my_vector_2) << " | " << BoolToStr(stl_vector_1 != stl_vector_2) << "\n\n";

	cout << "Vector 1 < Vector 2: " << BoolToStr(my_vector_1 < my_vector_2) << " | " << BoolToStr(stl_vector_1 < stl_vector_2) << "\n";
	cout << "Vector 1 <= Vector 2: " << BoolToStr(my_vector_1 <= my_vector_2) << " | " << BoolToStr(stl_vector_1 <= stl_vector_2) << "\n\n";

	cout << "Vector 1 > Vector 2: " << BoolToStr(my_vector_1 > my_vector_2) << " | " << BoolToStr(stl_vector_1 > stl_vector_2) << "\n";
	cout << "Vector 1 >= Vector 2: " << BoolToStr(my_vector_1 >= my_vector_2) << " | " << BoolToStr(stl_vector_1 >= stl_vector_2) << "\n\n";

	cout << UNDERLINE;
}