#include <forward_list>
#include <list>
#include <iostream>

using std::cout;

#include "single_linked_list.h"
#include "double_linked_list.h"
#include "circular_buffer.h"
#include "timer.h"

static constexpr int TESTS_COUNT = 3000000;
static constexpr const char* DELIMITER = "##############################################\n\n";


int main()
{
	cout << "Test single linked list...\n\n";

	std::forward_list<int> old_slist;
	single_linked_list<int> new_slist;

	timer t;

	for (int i = 0; i < TESTS_COUNT; i++) {
		old_slist.push_front(i);
	}

	cout << "Old single linked list push front time: " << t.get_elapsed_time() << " ms\n";

	t.reset();

	for (int i = 0; i < TESTS_COUNT; i++) {
		new_slist.push_front(i);
	}

	cout << "New single linked list push front time: " << t.get_elapsed_time() << " ms\n\n";

	t.reset();

	for (int i = 0; i < TESTS_COUNT; i++) {
		old_slist.insert_after(old_slist.begin(), i);
	}

	cout << "Old single linked list insert time: " << t.get_elapsed_time() << " ms\n";

	t.reset();

	for (int i = 0; i < TESTS_COUNT; i++) {
		new_slist.insert(new_slist.begin(), i);
	}

	cout << "New single linked list insert time: " << t.get_elapsed_time() << " ms\n\n";

	t.reset();

	for (int i = 0; i < TESTS_COUNT; i++) {
		old_slist.erase_after(old_slist.begin());
	}

	cout << "Old single linked list erase time: " << t.get_elapsed_time() << " ms\n";

	t.reset();

	for (int i = 0; i < TESTS_COUNT; i++) {
		new_slist.erase(new_slist.begin());
	}

	cout << "New single linked list erase time: " << t.get_elapsed_time() << " ms\n\n";

	t.reset();

	for (int i = 0; i < TESTS_COUNT; i++) {
		old_slist.pop_front();
	}

	cout << "Old single linked list pop front time: " << t.get_elapsed_time() << " ms\n";

	t.reset();

	for (int i = 0; i < TESTS_COUNT; i++) {
		new_slist.pop_front();
	}

	cout << "New single linked list pop front time: " << t.get_elapsed_time() << " ms\n\n";

	cout << DELIMITER;
	
	cout << "Test double linked list...\n\n";

	std::list<int> old_dlist;
	double_linked_list<int> new_dlist;

	t.reset();

	for (int i = 0; i < TESTS_COUNT; i++) {
		old_dlist.push_front(i);
	}

	cout << "Old double linked list push front time: " << t.get_elapsed_time() << " ms\n";

	t.reset();

	for (int i = 0; i < TESTS_COUNT; i++) {
		new_dlist.push_front(i);
	}

	cout << "New double linked list push front time: " << t.get_elapsed_time() << " ms\n\n";

	t.reset();

	for (int i = 0; i < TESTS_COUNT; i++) {
		old_dlist.insert(old_dlist.begin(), i);
	}

	cout << "Old double linked list insert time: " << t.get_elapsed_time() << " ms\n";

	t.reset();

	for (int i = 0; i < TESTS_COUNT; i++) {
		new_dlist.insert(new_dlist.begin(), i);
	}

	cout << "New double linked list insert time: " << t.get_elapsed_time() << " ms\n\n";

	t.reset();

	for (int i = 0; i < TESTS_COUNT; i++) {
		old_dlist.erase(old_dlist.begin());
	}

	cout << "Old double linked list erase time: " << t.get_elapsed_time() << " ms\n";

	t.reset();

	for (int i = 0; i < TESTS_COUNT; i++) {
		new_dlist.erase(new_dlist.begin());
	}

	cout << "New double linked list erase time: " << t.get_elapsed_time() << " ms\n\n";

	t.reset();

	for (int i = 0; i < TESTS_COUNT / 2; i++) {
		old_dlist.pop_front();
	}

	cout << "Old double linked list pop front time: " << t.get_elapsed_time() << " ms\n";

	t.reset();

	for (int i = 0; i < TESTS_COUNT / 2; i++) {
		new_dlist.pop_front();
	}

	cout << "New double linked list pop front time: " << t.get_elapsed_time() << " ms\n\n";

	t.reset();

	for (int i = 0; i < TESTS_COUNT / 2; i++) {
		old_dlist.pop_back();
	}

	cout << "Old double linked list pop back time: " << t.get_elapsed_time() << " ms\n";

	t.reset();

	for (int i = 0; i < TESTS_COUNT / 2; i++) {
		new_dlist.pop_back();
	}

	cout << "New double linked list pop back time: " << t.get_elapsed_time() << " ms\n\n";

	cout << DELIMITER;

	cout << "Test circular buffer...\n\n";

	circular_buffer<int> buff(TESTS_COUNT / 2);

	t.reset();

	for (int i = 0; i < TESTS_COUNT; i++) {
		buff.push(i);
	}

	cout << "Circular buffer push time: " << t.get_elapsed_time() << " ms\n";

	t.reset();

	for (int i = 0; i < TESTS_COUNT / 2; i++) {
		buff.pop();
	}

	cout << "Circular buffer pop time: " << t.get_elapsed_time() << " ms\n\n";

	t.reset();

	for (int i = 0; i < TESTS_COUNT; i++) {
		buff.insert(buff.begin() + 5, i);
	}

	cout << "Circular buffer insert time: " << t.get_elapsed_time() << " ms\n";

	t.reset();

	for (int i = 0; i < TESTS_COUNT / 3; i++) {
		buff.erase(buff.begin() + 2);
	}

	cout << "Circular buffer erase time: " << t.get_elapsed_time() << " ms\n\n";
	
	cout << DELIMITER;
	return 0;
}