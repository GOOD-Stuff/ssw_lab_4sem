#include <iostream>
#include <ctime>
#include <forward_list>
#include <list>

#include "ContainersTest.h"
#include "ForwardList.h"
#include "List.h"
#include "CBuffer.h"
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

void TestForwardList()
{
	cout << "Compare STL forward list and NEW forward list.\nNumber of loop repeats for each method: " << REPEATS << "\nPlease, wait...\n\n";

	std::forward_list<int> stl_list;
	ForwardList<int> new_list;

	Timer timer;

	for (size_t i = 0; i < REPEATS; i++)
		stl_list.push_front(i);

	cout << "STL forward list push front time: " << timer.GetElapsed_ms() << " ms\n";

	timer.Restart();

	for (size_t i = 0; i < REPEATS; i++)
		new_list.push_front(i);

	cout << "NEW forward list push front time: " << timer.GetElapsed_ms() << " ms\n\n";

	timer.Restart();

	for (size_t i = 0; i < REPEATS - 1; i++)
		stl_list.pop_front();

	cout << "STL forward list pop front time: " << timer.GetElapsed_ms() << " ms\n";

	timer.Restart();

	for (size_t i = 0; i < REPEATS - 1; i++)
		new_list.pop_front();

	cout << "NEW forward list pop front time: " << timer.GetElapsed_ms() << " ms\n\n";

	timer.Restart();

	for (size_t i = 0; i < REPEATS - 1; i++)
		stl_list.insert_after(stl_list.begin(), i);

	cout << "STL forward list insert time: " << timer.GetElapsed_ms() << " ms\n";

	timer.Restart();

	for (size_t i = 0; i < REPEATS - 1; i++)
		new_list.insert(new_list.begin(), i);

	cout << "NEW forward list insert time: " << timer.GetElapsed_ms() << " ms\n\n";

	timer.Restart();

	for (size_t i = 0; i < REPEATS - 1; i++)
		stl_list.erase_after(stl_list.begin());

	cout << "STL forward list erase time: " << timer.GetElapsed_ms() << " ms\n";

	timer.Restart();

	for (size_t i = 0; i < REPEATS - 1; i++)
		new_list.erase(new_list.begin());

	cout << "NEW forward list erase time: " << timer.GetElapsed_ms() << " ms\n\n";

	std::forward_list<int> stl_list_cmp_1;
	std::forward_list<int> stl_list_cmp_2;

	ForwardList<int> new_list_cmp_1;
	ForwardList<int> new_list_cmp_2;

	int repeats_count_1 = Random(2, 10);
	int repeats_count_2 = Random(2, 10);

	for (size_t i = 0; i <= repeats_count_1; i++)
	{
		int number = Random(10, 50);
		stl_list_cmp_1.push_front(number);
		new_list_cmp_1.push_front(number);
	}

	for (size_t i = 0; i <= repeats_count_2; i++)
	{
		int number = Random(10, 50);
		stl_list_cmp_2.push_front(number);
		new_list_cmp_2.push_front(number);
	}

	cout << "Checking comparison operators.\n\n";

	cout << "Forward list 1:\n\n" << new_list_cmp_1 << "\n";
	cout << "Forward list 2:\n\n" << new_list_cmp_2 << "\n";

	cout << "First bool - STL forward list result, second bool - NEW forward list result.\n\n";

	cout << "Forward list 1 == Forward list 2:\t" << BoolToString(stl_list_cmp_1 == stl_list_cmp_2) << "\t" << BoolToString(new_list_cmp_1 == new_list_cmp_2) << "\n";
	cout << "Forward list 1 != Forward list 2:\t" << BoolToString(stl_list_cmp_1 != stl_list_cmp_2) << "\t" << BoolToString(new_list_cmp_1 != new_list_cmp_2) << "\n\n";

	cout << "Forward list 1 < Forward list 2:\t" << BoolToString(stl_list_cmp_1 < stl_list_cmp_2) << "\t" << BoolToString(new_list_cmp_1 < new_list_cmp_2) << "\n";
	cout << "Forward list 1 > Forward list 2:\t" << BoolToString(stl_list_cmp_1 > stl_list_cmp_2) << "\t" << BoolToString(new_list_cmp_1 > new_list_cmp_2) << "\n\n";

	cout << "Forward list 1 <= Forward list 2:\t" << BoolToString(stl_list_cmp_1 <= stl_list_cmp_2) << "\t" << BoolToString(new_list_cmp_1 <= new_list_cmp_2) << "\n";
	cout << "Forward list 1 >= Forward list 2:\t" << BoolToString(stl_list_cmp_1 >= stl_list_cmp_2) << "\t" << BoolToString(new_list_cmp_1 >= new_list_cmp_2) << "\n\n";

	cout << LINE;
}

void TestList()
{
	cout << "Compare STL list and NEW list.\nNumber of loop repeats for each method: " << REPEATS << "\nPlease, wait...\n\n";

	std::list<int> stl_list;
	List<int> new_list;

	Timer timer;

	for (size_t i = 0; i < REPEATS; i++)
		stl_list.push_front(i);

	cout << "STL list push front time: " << timer.GetElapsed_ms() << " ms\n";

	timer.Restart();

	for (size_t i = 0; i < REPEATS; i++)
		new_list.push_front(i);

	cout << "NEW list push front time: " << timer.GetElapsed_ms() << " ms\n\n";

	timer.Restart();

	for (size_t i = 0; i < REPEATS; i++)
		stl_list.push_back(i);

	cout << "STL list push back time: " << timer.GetElapsed_ms() << " ms\n";

	timer.Restart();

	for (size_t i = 0; i < REPEATS; i++)
		new_list.push_back(i);

	cout << "NEW list push back time: " << timer.GetElapsed_ms() << " ms\n\n";

	timer.Restart();

	for (size_t i = 0; i < REPEATS - 1; i++)
		stl_list.pop_front();

	cout << "STL list pop front time: " << timer.GetElapsed_ms() << " ms\n";

	timer.Restart();

	for (size_t i = 0; i < REPEATS - 1; i++)
		new_list.pop_front();

	cout << "NEW list pop front time: " << timer.GetElapsed_ms() << " ms\n\n";

	timer.Restart();

	for (size_t i = 0; i < REPEATS - 1; i++)
		stl_list.insert(stl_list.begin(), i);

	cout << "STL list insert time: " << timer.GetElapsed_ms() << " ms\n";

	timer.Restart();

	for (size_t i = 0; i < REPEATS - 1; i++)
		new_list.insert(new_list.begin(), i);

	cout << "NEW list insert time: " << timer.GetElapsed_ms() << " ms\n\n";

	timer.Restart();

	for (size_t i = 0; i < REPEATS - 1; i++)
		stl_list.erase(stl_list.begin());

	cout << "STL list erase time: " << timer.GetElapsed_ms() << " ms\n";

	timer.Restart();

	for (size_t i = 0; i < REPEATS - 1; i++)
		new_list.erase(new_list.begin());

	cout << "NEW list erase time: " << timer.GetElapsed_ms() << " ms\n\n";

	std::list<int> stl_list_cmp_1;
	std::list<int> stl_list_cmp_2;

	List<int> new_list_cmp_1;
	List<int> new_list_cmp_2;

	int repeats_count_1 = Random(2, 10);
	int repeats_count_2 = Random(2, 10);

	for (size_t i = 0; i <= repeats_count_1; i++)
	{
		int number = Random(10, 50);
		stl_list_cmp_1.push_front(number);
		new_list_cmp_1.push_front(number);
	}

	for (size_t i = 0; i <= repeats_count_2; i++)
	{
		int number = Random(10, 50);
		stl_list_cmp_2.push_front(number);
		new_list_cmp_2.push_front(number);
	}

	cout << "Checking comparison operators.\n\n";

	cout << "List 1:\n\n" << new_list_cmp_1 << "\n";
	cout << "List 2:\n\n" << new_list_cmp_2 << "\n";

	cout << "First bool - STL list result, second bool - NEW list result.\n\n";

	cout << "List 1 == List 2:\t" << BoolToString(stl_list_cmp_1 == stl_list_cmp_2) << "\t" << BoolToString(new_list_cmp_1 == new_list_cmp_2) << "\n";
	cout << "List 1 != List 2:\t" << BoolToString(stl_list_cmp_1 != stl_list_cmp_2) << "\t" << BoolToString(new_list_cmp_1 != new_list_cmp_2) << "\n\n";

	cout << "List 1 < List 2:\t" << BoolToString(stl_list_cmp_1 < stl_list_cmp_2) << "\t" << BoolToString(new_list_cmp_1 < new_list_cmp_2) << "\n";
	cout << "List 1 > List 2:\t" << BoolToString(stl_list_cmp_1 > stl_list_cmp_2) << "\t" << BoolToString(new_list_cmp_1 > new_list_cmp_2) << "\n\n";

	cout << "List 1 <= List 2:\t" << BoolToString(stl_list_cmp_1 <= stl_list_cmp_2) << "\t" << BoolToString(new_list_cmp_1 <= new_list_cmp_2) << "\n";
	cout << "List 1 >= List 2:\t" << BoolToString(stl_list_cmp_1 >= stl_list_cmp_2) << "\t" << BoolToString(new_list_cmp_1 >= new_list_cmp_2) << "\n\n";

	cout << LINE;
}

void TestAllContainers()
{
	TestForwardList();
	TestList();
}