#include <iostream>
#include <cstdlib>
#include <ctime>

using std::cout;

#include "Timer.h"
#include "BSTree.h"

void run_test_binary_search_tree()
{
	std::srand(time(0));
	cout << "Binary search tree tests.\nPlease, wait...\n\n";

	BSTree<int> tree { 3, 4, 5, 6, 7, 8 };

	cout << "Current tree state:\n\n" << tree << "\n";
	tree.balance();
	cout << "After tree balance state:\n\n" << tree << "\n";
	
	for (int i = 0; i < 10000; i++)
		tree.push(std::rand() % 10001);

	Timer timer;

	cout << "Push 10 000 elements time: " << timer.GetElapsed_ms() << " ms\n";
	timer.Restart();

	tree.push(100000);
	tree.push(250012);
	tree.push(200000);

	tree.balance();
	cout << "Balance time: " << timer.GetElapsed_ms() << " ms\n\n";
	
	cout << "Current size: " << tree.count() << " elements\n";
	cout << "Current height: " << tree.height() << "\n\n";

	timer.Restart();
	tree.find(100000);
	tree.find(250012);
	tree.find(200000);
	
	cout << "Find 3 existing values time: " << timer.GetElapsed_ms() << " ms\n";
}