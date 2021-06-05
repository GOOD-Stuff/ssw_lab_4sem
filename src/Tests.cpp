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
	cout << "testing (" << IT_COUNT << " runs per method)\n\n";
	TestStack();
	TestQueue();
	TestVector();
}
void TestStack()
{
	cout << "testing stack\n\n";

	Stack my_stack;
	stack<int> stl_stack;
	auto start = CurrentTime();
	for (int i = 0; i < IT_COUNT; i++)
		my_stack.push(i);
	cout << "My push time: " << DeltaTime(start) << " \n";
	start = CurrentTime();
	for (int i = 0; i < IT_COUNT; i++)
		stl_stack.push(i);
	cout << "STL push time: " << DeltaTime(start) << " \n\n";
	start = CurrentTime();
	for (int i = 0; i < IT_COUNT; i++)
		int value = my_stack.peek();
	cout << "My peek time: " << DeltaTime(start) << " \n";
	start = CurrentTime();
	for (int i = 0; i < IT_COUNT; i++)
		int value = stl_stack.top();
	cout << "STL peek time: " << DeltaTime(start) << " \n\n";
	start = CurrentTime();
	for (int i = 0; i < IT_COUNT; i++)
		my_stack.pop();
	cout << "My pop time: " << DeltaTime(start) << " \n";
	start = CurrentTime();
	for (int i = 0; i < IT_COUNT; i++)
		stl_stack.pop();
	cout << "STL pop time: " << DeltaTime(start) << " \n\n";
	cout << "testing operators\n\n";
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
	cout << "Left - my stack, right - STL stack:\n\n";
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
	cout << "testing queue!\n\n";
	Queue my_queue;
	queue<int> stl_queue;
	auto start = CurrentTime();
	for (int i = 0; i < IT_COUNT; i++)
		my_queue.push(i);
	cout << "My push time: " << DeltaTime(start) << "\n";
	start = CurrentTime();
	for (int i = 0; i < IT_COUNT; i++)
		stl_queue.push(i);
	cout << "STL push time: " << DeltaTime(start) << "\n\n";
	start = CurrentTime();
	for (int i = 0; i < IT_COUNT; i++)
		int value = my_queue.peek();
	cout << "My peek time: " << DeltaTime(start) << "\n";
	start = CurrentTime();
	for (int i = 0; i < IT_COUNT; i++)
		int value = stl_queue.back();
	cout << "STL peek time: " << DeltaTime(start) << "\n\n";
	start = CurrentTime();
	for (int i = 0; i < IT_COUNT; i++)
		my_queue.pop();
	cout << "My pop time: " << DeltaTime(start) << "\n";
	start = CurrentTime();
	for (int i = 0; i < IT_COUNT; i++)
		stl_queue.pop();
	cout << "STL pop time: " << DeltaTime(start) << "\n\n";
	cout << "testing operators\n\n";
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
	cout << "Left - my queue, right - STL queue:\n\n";
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
	cout << "testing vector!\n\n";

	Vector my_vector;
	vector<int> stl_vector;
	auto start = CurrentTime();
	for (int i = 0; i < IT_COUNT; i++)
		my_vector.push(i);
	cout << "My push time: " << DeltaTime(start) << "\n";
	start = CurrentTime();
	for (int i = 0; i < IT_COUNT; i++)
		stl_vector.push_back(i);
	cout << "STL vector push time: " << DeltaTime(start) << "\n\n";
	start = CurrentTime();
	for (int i = 0; i < IT_COUNT; i++)
		int value = my_vector.at(i);
	cout << "My at time: " << DeltaTime(start) << "\n";
	start = CurrentTime();
	for (int i = 0; i < IT_COUNT; i++)
		int value = stl_vector.at(i);
	cout << "STL at time: " << DeltaTime(start) << "\n\n";
	start = CurrentTime();
	for (int i = 0; i < IT_COUNT; i++)
		my_vector.pop();
	cout << "My pop time: " << DeltaTime(start) << "\n";
	start = CurrentTime();
	for (int i = 0; i < IT_COUNT; i++)
		stl_vector.pop_back();
	cout << "STL pop time: " << DeltaTime(start) << "\n\n";
	cout << "testing operators\n\n";
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
	Vector my_vector_3;
	for (int i = 10; i > 0; i--)
		my_vector_3.push(i);

	cout << "Vector 1:\n\n" << my_vector_1 << "\n";
	cout << "Vector 2:\n\n" << my_vector_2 << "\n";
	cout << "Left - my vector, right - STL vector :\n\n";
	cout << "Vector 1 == Vector 2: " << BoolToStr(my_vector_1 == my_vector_2) << " | " << BoolToStr(stl_vector_1 == stl_vector_2) << "\n";
	cout << "Vector 1 != Vector 2: " << BoolToStr(my_vector_1 != my_vector_2) << " | " << BoolToStr(stl_vector_1 != stl_vector_2) << "\n\n";
	cout << "Vector 1 < Vector 2: " << BoolToStr(my_vector_1 < my_vector_2) << " | " << BoolToStr(stl_vector_1 < stl_vector_2) << "\n";
	cout << "Vector 1 <= Vector 2: " << BoolToStr(my_vector_1 <= my_vector_2) << " | " << BoolToStr(stl_vector_1 <= stl_vector_2) << "\n\n";
	cout << "Vector 1 > Vector 2: " << BoolToStr(my_vector_1 > my_vector_2) << " | " << BoolToStr(stl_vector_1 > stl_vector_2) << "\n";
	cout << "Vector 1 >= Vector 2: " << BoolToStr(my_vector_1 >= my_vector_2) << " | " << BoolToStr(stl_vector_1 >= stl_vector_2) << "\n\n";
	cout << UNDERLINE;
}