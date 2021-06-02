#include <stack>
#include <queue>
#include <vector>
#include <iostream>

using std::cout;

#include "stack.h"
#include "queue.h"
#include "vector.h"
#include "timer.h"

int random_int(int first, int second)
{
	return first + rand() % (second - first);
}

static constexpr int TESTS_COUNT = 3000000;
static constexpr const char* DELIMITER = "##############################################\n\n";

int main()
{
	cout << "Test stack...\n\n";
	
	std::stack<int> old_stack;
	stack<int> new_stack;

	timer t;

	for (int i = 0; i < TESTS_COUNT; i++) {
		old_stack.push(i);
	}

	cout << "Old stack push time: " << t.get_elapsed_time() << " ms\n";

	t.reset();

	for (int i = 0; i < TESTS_COUNT; i++) {
		new_stack.push(i);
	}

	cout << "New stack push time: " << t.get_elapsed_time() << " ms\n\n";

	t.reset();

	for (int i = 0; i < TESTS_COUNT; i++) {
		old_stack.pop();
	}

	cout << "Old stack pop time: " << t.get_elapsed_time() << " ms\n";

	t.reset();

	for (int i = 0; i < TESTS_COUNT; i++) {
		new_stack.pop();
	}

	cout << "New stack pop time: " << t.get_elapsed_time() << " ms\n\n";

	cout << DELIMITER;

	cout << "Test queue...\n\n";
	
	std::queue<int> old_queue;
	queue<int> new_queue;

	t.reset();

	for (int i = 0; i < TESTS_COUNT; i++) {
		old_queue.push(i);
	}

	cout << "Old queue push time: " << t.get_elapsed_time() << " ms\n";

	t.reset();

	for (int i = 0; i < TESTS_COUNT; i++) {
		new_queue.push(i);
	}

	cout << "New queue push time: " << t.get_elapsed_time() << " ms\n\n";

	t.reset();

	for (int i = 0; i < TESTS_COUNT; i++) {
		old_queue.pop();
	}

	cout << "Old queue pop time: " << t.get_elapsed_time() << " ms\n";

	t.reset();

	for (int i = 0; i < TESTS_COUNT; i++) {
		new_queue.pop();
	}

	cout << "New queue pop time: " << t.get_elapsed_time() << " ms\n\n";

	cout << DELIMITER;

	std::vector<int> old_vector;
	vector<int> new_vector;

	t.reset();

	for (int i = 0; i < TESTS_COUNT; i++) {
		old_vector.push_back(i);
	}

	cout << "Old vector push time: " << t.get_elapsed_time() << " ms\n";

	t.reset();

	for (int i = 0; i < TESTS_COUNT; i++) {
		new_vector.push(i);
	}

	cout << "New vector push time: " << t.get_elapsed_time() << " ms\n\n";

	t.reset();

	for (int i = 0; i < TESTS_COUNT; i++) {
		old_vector.pop_back();
	}

	cout << "Old vector pop time: " << t.get_elapsed_time() << " ms\n";

	t.reset();

	for (int i = 0; i < TESTS_COUNT; i++) {
		new_vector.pop();
	}

	cout << "New vector pop time: " << t.get_elapsed_time() << " ms\n\n";

	return 0;
}