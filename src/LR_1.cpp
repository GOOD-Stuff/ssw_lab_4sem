// LR_1.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include"stack.h"
#include"queue.h"
#include"vector.h"
using namespace std;

int main()
{
	stack <int> stack_int;
	stack <float> stack_float;
	queue <int> queue_int;
	queue <float> queue_float;
	vector <int> vector_int;
	vector <float> vector_float;

	stack_int.push(1);
	stack_int.push(3);
	stack_int.push(10);
	stack_int.push(5);
	stack_int.push(7);

	stack_float.push(1.5);
	stack_float.push(2);
	stack_float.push(3.6);
	stack_float.push(7.4);
	stack_float.push(3);

	queue_int.push(1);
	queue_int.push(3);
	queue_int.push(10);
	queue_int.push(5);
	queue_int.push(7);

	queue_float.push(1.5);
	queue_float.push(2);
	queue_float.push(3.6);
	queue_float.push(7.4);
	queue_float.push(3);

	vector_int.push(1);
	vector_int.push(3);
	vector_int.push(10);
	vector_int.push(5);
	vector_int.push(7);

	vector_float.push(1.5);
	vector_float.push(2);
	vector_float.push(3.6);
	vector_float.push(7.4);
	vector_float.push(3);

	cout << "Construction 1";
	stack_int.display();
	queue_int.display();
	vector_int.display();

	cout << "\n\nConstruction 2";
	stack_float.display();
	queue_float.display();
	vector_float.display();

	cout << "\n\nPop";
	cout << "\nConstruction 1";
	stack_int.pop();
	stack_int.display();
	queue_int.pop();
	queue_int.display();
	vector_int.pop();
	vector_int.display();

	cout << "\n\nConstruction 2";
	stack_float.pop();
	stack_float.display();
	queue_float.pop();
	queue_float.display();
	vector_float.pop();
	vector_float.display();

	cout << "\n\nPeek";
	cout << "\nConstruction 1\n";
	cout << stack_int.peek() << endl;
	cout << queue_int.peek() << endl;
	cout << vector_int.peek() << endl;

	cout << "\nConstruction 2\n";
	cout << stack_float.peek() << endl;
	cout << queue_float.peek() << endl;
	cout << vector_float.peek() << endl;

	cout << "\nCount";
	cout << "\nConstruction 1\n";
	cout << stack_int.count() << endl;
	cout << queue_int.count() << endl;
	cout << vector_int.count() << endl;

	cout << "\nConstruction 2\n";
	cout << stack_float.count() << endl;
	cout << queue_float.count() << endl;
	cout << vector_float.count() << endl;

	cout << "\nAt (2 el, only vector)";
	cout << "\nConstruction 1\n";
	cout << vector_int.at(2) << endl;
	cout << "\nConstruction 2\n";
	cout << vector_float.at(2) << endl;

	cout << "\nSum";
	cout << "\nConstruction 1\n";
	cout << stack_int.sum() << endl;
	cout << queue_int.sum() << endl;
	cout << vector_int.sum() << endl;

	cout << "\nConstruction 2\n";
	cout << stack_float.sum() << endl;
	cout << queue_float.sum() << endl;
	cout << vector_float.sum() << endl;

	cout << "\nConcatenation (not implemented for structure - stack)";
	cout << "\nConstruction 1\n";
	cout << queue_int.conc() << endl;
	cout << vector_int.conc() << endl;

	cout << "\nConstruction 2\n";
	cout << queue_float.conc() << endl;
	cout << vector_float.conc() << endl;
    return 0;
}

