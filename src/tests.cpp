#include <iostream>
#include <chrono>
#include <string>
#include <forward_list>
#include <list>

using std::cout;

#include "tests.h"
#include "forward_list.h"
#include "list.h"

std::chrono::steady_clock::time_point current_time()
{
	return std::chrono::steady_clock::now();
}

long long delta_time(const std::chrono::steady_clock::time_point& point)
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(current_time() - point).count();
}

static const int IT_COUNT = 3000000;
static const std::string UNDERLINE = "--------------------------------------------------------------\n\n";

void run_tests()
{
	cout << "My containers vs STL containers! (" << IT_COUNT << " runs per method)\n\n";

	test_forward_list();
	test_list();
}

void test_forward_list()
{
	cout << "My forward_list vs STL forward_list!\nPlease, wait!\n\n";

	forward_list<int> my_list;
	std::forward_list<int> stl_list;

	/////////////////////////////////////////////////////////////

	auto start = current_time();

	for (int i = 0; i < IT_COUNT; i++)
	{
		my_list.push_front(i);
	}

	cout << "My forward_list push front time: " << delta_time(start) << " ms\n";

	//////////////////////////

	start = current_time();

	for (int i = 0; i < IT_COUNT; i++)
	{
		stl_list.push_front(i);
	}

	cout << "STL forward_list push front time: " << delta_time(start) << " ms\n\n";

	/////////////////////////////////////////////////////////////

	start = current_time();

	for (int i = 0; i < IT_COUNT; i++)
	{
		my_list.insert(++++++my_list.begin(), i);
	}

	cout << "My forward_list insert time: " << delta_time(start) << " ms\n";
	
	//////////////////////////

	start = current_time();

	for (int i = 0; i < IT_COUNT; i++)
	{
		stl_list.insert_after(++++++stl_list.begin(), i);
	}

	cout << "STL forward_list insert_after time: " << delta_time(start) << " ms\n\n";

	/////////////////////////////////////////////////////////////

	start = current_time();

	for (int i = 0; i < IT_COUNT; i++)
	{
		my_list.erase(++++++my_list.begin());
	}

	cout << "My forward_list erase time: " << delta_time(start) << " ms\n";

	//////////////////////////

	start = current_time();

	for (int i = 0; i < IT_COUNT; i++)
	{
		stl_list.erase_after(++++++stl_list.begin());
	}

	cout << "STL forward_list erase_after time: " << delta_time(start) << " ms\n\n";

	/////////////////////////////////////////////////////////////
	
	start = current_time();

	for (int i = 0; i < IT_COUNT; i++)
	{
		my_list.pop_front();
	}

	cout << "My forward_list pop_front time: " << delta_time(start) << " ms\n";

	//////////////////////////

	start = current_time();

	for (int i = 0; i < IT_COUNT; i++)
	{
		stl_list.pop_front();
	}

	cout << "STL forward_list pop_front time: " << delta_time(start) << " ms\n\n";

	/////////////////////////////////////////////////////////////
	
	cout << UNDERLINE;
}

void test_list()
{
	cout << "My list vs STL list!\nPlease, wait!\n\n";

	list<int> my_list;
	std::list<int> stl_list;

	/////////////////////////////////////////////////////////////

	auto start = current_time();

	for (int i = 0; i < IT_COUNT; i++)
	{
		my_list.push_front(i);
	}

	cout << "My list push front time: " << delta_time(start) << " ms\n";

	//////////////////////////

	start = current_time();

	for (int i = 0; i < IT_COUNT; i++)
	{
		stl_list.push_front(i);
	}

	cout << "STL list push front time: " << delta_time(start) << " ms\n\n";

	/////////////////////////////////////////////////////////////

	start = current_time();

	for (int i = 0; i < IT_COUNT; i++)
	{
		my_list.push_back(i);
	}

	cout << "My list push back time: " << delta_time(start) << " ms\n";
	
	//////////////////////////

	start = current_time();

	for (int i = 0; i < IT_COUNT; i++)
	{
		stl_list.push_back(i);
	}

	cout << "STL list push back time: " << delta_time(start) << " ms\n\n";
	
	/////////////////////////////////////////////////////////////
	
	start = current_time();

	for (int i = 0; i < IT_COUNT; i++)
	{
		my_list.insert(++++++my_list.begin(), i);
	}

	cout << "My list insert time: " << delta_time(start) << " ms\n";

	//////////////////////////

	start = current_time();

	for (int i = 0; i < IT_COUNT; i++)
	{
		stl_list.insert(++++++stl_list.begin(), i);
	}

	cout << "STL list insert_after time: " << delta_time(start) << " ms\n\n";

	/////////////////////////////////////////////////////////////

	start = current_time();

	for (int i = 0; i < IT_COUNT; i++)
	{
		my_list.erase(++++++my_list.begin());
	}

	cout << "My list erase time: " << delta_time(start) << " ms\n";

	//////////////////////////

	start = current_time();

	for (int i = 0; i < IT_COUNT; i++)
	{
		stl_list.erase(++++++stl_list.begin());
	}

	cout << "STL list erase_after time: " << delta_time(start) << " ms\n\n";

	/////////////////////////////////////////////////////////////

	start = current_time();

	for (int i = 0; i < IT_COUNT / 2; i++)
	{
		my_list.pop_front();
	}

	cout << "My list pop_front time: " << delta_time(start) << " ms\n";

	//////////////////////////

	start = current_time();

	for (int i = 0; i < IT_COUNT / 2; i++)
	{
		stl_list.pop_front();
	}

	cout << "STL list pop_front time: " << delta_time(start) << " ms\n\n";

	/////////////////////////////////////////////////////////////

	start = current_time();

	for (int i = 0; i < IT_COUNT / 2; i++)
	{
		my_list.pop_back();
	}

	cout << "My list pop_back time: " << delta_time(start) << " ms\n";

	//////////////////////////

	start = current_time();

	for (int i = 0; i < IT_COUNT / 2; i++)
	{
		stl_list.pop_back();
	}

	cout << "My list pop_back time: " << delta_time(start) << " ms\n\n";
	
	/////////////////////////////////////////////////////////////
	
	cout << UNDERLINE;
}