#include <iostream>
#include "Binary_tree.h"
#include "General_tree.h"

using namespace std;

int main() {
	bin_tree<int> tree1{ 11,22,33,33,43,53 };
	bin_tree<int> tree2{ 11,22,33,22 };
	if (tree1 == tree2) cout << "equally";
	if (tree1 > tree2) cout << "more";
	tree1.Print();
	cout << endl;
	cout << tree1.Height();
	cout << endl;
	auto res = tree1.Path(22);
	cout << get<0>(res);
	cout << endl;

	bin_tree<int> tree3{ 1,2,3 };
	auto split = tree3.split();
	std::cout << "Split:\nFirst: " << *split[0] << endl << "Second: " << *split[1] << endl;

	general_tree<int> tr1{ 1,3,2,4,5 };
	general_tree<int> tr2{ 1,3,2 };
	tr1.Print();
	auto res1 = tr1.Find(2);
	tr1.Push(get<0>(res1), 22);
	tr1.Print();	
	auto res2 = tr1.Path(22);
	cout << endl;
	cout << get<0>(res2);
	cout << endl;
	if (tr2 == tr1) cout << "equally";
	cout << endl;
	if (tr1 > tr2) cout << "more";
	cout << endl;


	general_tree<int> tr3{ 1,3,4 };
	auto split1 = tr3.split();
	std::cout << "Split:\nFirst: " << *split1[0] << endl << "Second: " << *split1[1] << endl;

	return 0;
}