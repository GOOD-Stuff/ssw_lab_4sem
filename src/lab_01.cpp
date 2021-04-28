#include <iostream>
#include <ctime>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include "vector/vector.h"
#include "stack/stack.cpp"
#include "queue/queue.h"
#include "timer.h"

using namespace std;

const string line = "*******************************************";

Vector* my_vector;
vector<int>* std_vector;
void testVector(int);

Stack<int>* my_stack;
stack<int>* std_stack;
void testStack(int);

Queue* my_queue;
queue<int>* std_queue;
void testQueue(int);

int rand(int min, int max) {
	return min + rand() % (max - min);
}

string boolToString(bool val)
{
	return val ? "true" : "false";
}

int main(int argc, char** argv)
{
	cout << endl;
	cout << line << endl;
	cout << "Тест vector" << endl;
	cout << endl;

	testVector(50);

	delete my_vector;
	delete std_vector;

	cout << endl;
	cout << line << endl;
	cout << "Тест stack" << endl;
	cout << endl;

	testStack(50);

	delete my_stack;
	delete std_stack;

	cout << endl;
	cout << line << endl;
	cout << "Тест queue" << endl;
	cout << endl;

	testQueue(50);

	delete my_queue;
	delete std_queue;

	return 0;
}

// TEST QUEUE
void testQueuePush(int);
void testQueuePop();
void testQueueComparisons();
void testQueueJobFunctions();

void testQueue(int size) {
	my_queue = new Queue();
	std_queue = new queue<int>();
	cout << "Добавление " << size << " элементов" << endl;
	testQueuePush(size);

	cout << endl;
	cout << "Выталкивание элемента" << endl;
	testQueuePop();

	cout << endl;
	cout << "Операторы сравнения" << endl;
	testQueueComparisons();

	cout << endl;
	cout << "Функции из задания" << endl;
	testQueueJobFunctions();
}

void testQueuePush(int size) {
	Timer t1;
	int arr[size];

	for(int i = 0; i < size; i++) {
		arr[i] = rand(0, 100);
		my_queue->push(arr[i]);
	}

	cout << "Время добавления элементов в my_queue: " << t1.getTime() << endl;

	Timer t2;

	for(int i = 0; i < size; i++)
		std_queue->push(arr[i]);

	cout << "Время добавления элементов в std_queue: " << t2.getTime() << endl;
	cout << "Итоговый Queue: " << *my_queue << endl;
}

void testQueuePop() {
	cout << "Элемент my_queue до выталкивания: " << my_queue->peek() << endl;
	my_queue->pop();
	cout << "Элемент my_queue после выталкивания: " << my_queue->peek() << endl;
}

void testQueueComparisons() {
	Queue my_queue_2;
	queue<int> std_queue_2;

	for(int i = 0; i < my_queue->count(); i++) {
		int num = rand(0, 100);
		my_queue_2.push(num);
		std_queue_2.push(num);
	}

	cout << "Queue для сравнения: " << my_queue_2 << endl;

	Timer t1;

	cout << "Операторы сравнения my_queue:"
		<< " == " << boolToString((*my_queue) == my_queue_2)
		<< " != " << boolToString((*my_queue) != my_queue_2)
		<< " > " << boolToString((*my_queue) > my_queue_2)
		<< " < " << boolToString((*my_queue) < my_queue_2)
		<< " <= " << boolToString((*my_queue) <= my_queue_2)
		<< " >= " << boolToString((*my_queue) >= my_queue_2) << endl;
	cout << "Время сравнения в my_queue: " << t1.getTime() << endl;

	Timer t2;

	 cout << "Операторы сравнения std_queue:"
		<< " == " << boolToString((*std_queue) == std_queue_2)
		<< " != " << boolToString((*std_queue) != std_queue_2)
		<< " > " << boolToString((*std_queue) > std_queue_2)
		<< " < " << boolToString((*std_queue) < std_queue_2)
		<< " <= " << boolToString((*std_queue) <= std_queue_2)
		<< " >= " << boolToString((*std_queue) >= std_queue_2) << endl;
	cout << "Время сравнения в std_queue: " << t2.getTime() << endl;
}

void testQueueJobFunctions() {
	Timer t1;

	cout << "Среднее арифметическое: " << my_queue->get_arithmetic_mean() << endl;
	cout << "Время выполнения: " << t1.getTime() << endl;

	Timer t2;

	cout << "Конкатинация: " << my_queue->concat_sort(*my_queue) << endl;
	cout << "Время выполнения: " << t2.getTime() << endl;
}

// TEST STACK
void testStackPush(int);
void testStackPop();
void testStackComparisons();
void testStackJobFunctions();

void testStack(int size) {
	my_stack = new Stack<int>();
	std_stack = new stack<int>();
	cout << "Добавление " << size << " элементов" << endl;
	testStackPush(size);

	cout << endl;
	cout << "Выталкивание элемента" << endl;
	testStackPop();

	cout << endl;
	cout << "Операторы сравнения" << endl;
	testStackComparisons();

	cout << endl;
	cout << "Функции из задания" << endl;
	testStackJobFunctions();
}

void testStackPush(int size) {
	Timer t1;
	int arr[size];

	for(int i = 0; i < size; i++) {
		arr[i] = rand(0, 100);
		my_stack->push(arr[i]);
	}

	cout << "Время добавления элементов в my_stack: " << t1.getTime() << endl;

	Timer t2;

	for(int i = 0; i < size; i++)
		std_stack->push(arr[i]);

	cout << "Время добавления элементов в std_stack: " << t2.getTime() << endl;
	cout << "Итоговый Stack: " << *my_stack << endl;
}

void testStackPop() {
	cout << "Элемент my_stack до выталкивания: " << my_stack->pop() << endl;
	cout << "Элемент my_stack после выталкивания: " << my_stack->peek() << endl;
}

void testStackComparisons() {
	Stack<int> my_stack_2;
	stack<int> std_stack_2;

	for(int i = 0; i < my_stack->count(); i++) {
		int num = rand(0, 100);
		my_stack_2.push(num);
		std_stack_2.push(num);
	}

	cout << "Stack для сравнения: " << my_stack_2 << endl;
	Timer t1;

	cout << "Операторы сравнения my_stack:"
		<< " == " << boolToString((*my_stack) == my_stack_2)
		<< " != " << boolToString((*my_stack) != my_stack_2)
		<< " > " << boolToString((*my_stack) > my_stack_2)
		<< " < " << boolToString((*my_stack) < my_stack_2)
		<< " <= " << boolToString((*my_stack) <= my_stack_2)
		<< " >= " << boolToString((*my_stack) >= my_stack_2) << endl;
	cout << "Время сравнения в my_stack: " << t1.getTime() << endl;

	Timer t2;

	 cout << "Операторы сравнения std_stack:"
		<< " == " << boolToString((*std_stack) == std_stack_2)
		<< " != " << boolToString((*std_stack) != std_stack_2)
		<< " > " << boolToString((*std_stack) > std_stack_2)
		<< " < " << boolToString((*std_stack) < std_stack_2)
		<< " <= " << boolToString((*std_stack) <= std_stack_2)
		<< " >= " << boolToString((*std_stack) >= std_stack_2) << endl;
	cout << "Время сравнения в std_stack: " << t2.getTime() << endl;

}

void testStackJobFunctions() {
	Timer t1;

	cout << "Среднее арифметическое: " << my_stack->getAverage() << endl;
	cout << "Время выполнения: " << t1.getTime() << endl;

	Timer t2;

	cout << "Конкатинация: " << my_stack->concat(*my_stack) << endl;
	cout << "Время выполнения: " << t2.getTime() << endl;
}

// TEST VECTOR
void testVectorPush(int);
void testVectorAt(int);
void testVectorPop();
void testVectorComparisons();
void testVectorAllPop();
void testVectorJobFunctions();

void testVector(int size) {
	my_vector = new Vector();
	std_vector = new vector<int>();
	cout << "Добавление " << size << " элементов" << endl;
	testVectorPush(size);

	cout << endl;
	cout << "Доступ к " << size / 2 << " элементу" << endl;
	testVectorAt(size / 2);

	cout << endl;
	cout << "Выталкивание элемента" << endl;
	testVectorPop();

	cout << endl;
	cout << "Операторы сравнения" << endl;
	testVectorComparisons();

	cout << endl;
	cout << "Функции из задания" << endl;
	testVectorJobFunctions();

	cout << endl;
	cout << "Выталкивание всех элементов" << endl;
	testVectorAllPop();
}

void testVectorPush(int size) {
	Timer t1;

	for(int i = 0; i < size; i++)
		my_vector->push_back(rand(0, 100));

	cout << "Время добавления элементов в my_vector: " << t1.getTime() << endl;

	Timer t2;

	for(int i = 0; i < size; i++)
		std_vector->push_back(my_vector->at(i));

	cout << "Время добавления элементов в std_vector: " << t2.getTime() << endl;
	cout << "Итоговый вектор: " << *my_vector << endl;
}

void testVectorAt(int index) {
	cout << "Элемент my_vector: " << my_vector->at(index) << endl;
}

void testVectorPop() {
	cout << "Элемент my_vector до выталкивания: " << my_vector->at(my_vector->count() - 1) << endl;
	my_vector->pop_back();
	cout << "Элемент my_vector после выталкивания: " << my_vector->at(my_vector->count() - 1) << endl;
}

void testVectorComparisons() {
	Vector my_vector_2;
	vector<int> std_vector_2;

	for(int i = 0; i < my_vector->count(); i++) {
		int num = rand(0, 100);
		my_vector_2.push_back(num);
		std_vector_2.push_back(num);
	}

	cout << "Вектор для сравнения: " << my_vector_2 << endl;

	Timer t1;

	cout << "Операторы сравнения my_vector:"
		<< " == " << boolToString((*my_vector) == my_vector_2)
		<< " != " << boolToString((*my_vector) != my_vector_2)
		<< " > " << boolToString((*my_vector) > my_vector_2)
		<< " < " << boolToString((*my_vector) < my_vector_2)
		<< " <= " << boolToString((*my_vector) <= my_vector_2)
		<< " >= " << boolToString((*my_vector) >= my_vector_2) << endl;
	cout << "Время сравнения в my_vector: " << t1.getTime() << endl;

	Timer t2;

	 cout << "Операторы сравнения std_vector:"
		<< " == " << boolToString((*std_vector) == std_vector_2)
		<< " != " << boolToString((*std_vector) != std_vector_2)
		<< " > " << boolToString((*std_vector) > std_vector_2)
		<< " < " << boolToString((*std_vector) < std_vector_2)
		<< " <= " << boolToString((*std_vector) <= std_vector_2)
		<< " >= " << boolToString((*std_vector) >= std_vector_2) << endl;
	cout << "Время сравнения в std_vector: " << t2.getTime() << endl;

}

void testVectorAllPop() {
	Timer t1;

	int size = my_vector->count();
	for(int i = 0; i < size; i++)
		my_vector->pop_back();

	cout << "Время выталкивания всех элементов в my_vector: " << t1.getTime() << endl;

	Timer t2;

	for(int i = 0; i < size; i++)
		std_vector->pop_back();

	cout << "Время выталкивания всех элементов в std_vector: " << t2.getTime() << endl;
}

void testVectorJobFunctions() {
	Timer t1;

	cout << "Среднее арифметическое: " << my_vector->get_arithmetic_mean() << endl;
	cout << "Время выполнения: " << t1.getTime() << endl;

	Timer t2;

	cout << "Конкатинация: " << my_vector->concat_sort(*my_vector) << endl;
	cout << "Время выполнения: " << t2.getTime() << endl;
}
