#include <iostream>
#include "LinkedList.h"
#include "DoubleLinkedList.h"

int main()
{
	//LinkedList<int> list1{ 4, 3, 1, 8, 7 };
	DoubleLinkedList<int> list1{ 252, 2, 5, 8, 12 };
	std::cout << "output" << std::endl;
	std::cout << list1;
    
	std::cout << "Merge_sort: " << std::endl;
	list1.merge_sort();
	std::cout << list1;

	std::cout << "pop (front/back)" << std::endl;
	list1.pop_front();
	list1.pop_back();
	std::cout << list1;

	std::cout << "push (front/back)" << std::endl;
	list1.push_front(1);
	list1.push_back(11);
	std::cout << list1;

	std::cout << "delete by index (3)" << std::endl;
	list1.erase(3);
	std::cout << list1;

	std::cout << "amount of elements: " << list1.count() << std::endl;

	

	return 0;
}