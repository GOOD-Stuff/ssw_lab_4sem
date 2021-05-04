#include <iostream>
#include <ctime>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include "vector/vector.cpp"
#include "stack/stack.h"
#include "queue/queue.cpp"
#include "timer.h"

using namespace std;

void testVector(int);
void testStack(int);
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
	cout << "\n";
	cout << "*******************************************" << "\n";
	cout << "Тест vector" << "\n";
	cout << "\n";

	testVector(50);

	cout << "\n";
	cout << "*******************************************" << "\n";
	cout << "Тест stack" << "\n";
	cout << "\n";

	testStack(50);

	cout << "\n";
	cout << "*******************************************" << "\n";
	cout << "Тест queue" << "\n";
	cout << "\n";

	testQueue(50);

	return 0;
}

// TEST QUEUE
void testQueuePush(int, Queue&, queue<int>&);
void testQueuePop(Queue&);
void testQueueComparisons(Queue&, queue<int>&);
void testQueueJobFunctions(Queue&);

void testQueue(int size) {
	Queue my_queue;
	queue<int> std_queue;
	cout << "Добавление " << size << " элементов" << "\n";
	testQueuePush(size, my_queue, std_queue);

	cout << "\nВыталкивание элемента\n";
	testQueuePop(my_queue);

	cout << "\nОператоры сравнения\n";
	testQueueComparisons(my_queue, std_queue);

	cout << "\nФункции из задания\n";
	testQueueJobFunctions(my_queue);
}

void testQueuePush(int size, Queue& my_queue, queue<int>& std_queue) {
	Timer t1;

	for(int i = 0; i < size; i++)
		my_queue.push(rand(0, 100));

	cout << "Время добавления элементов в my_queue: " << t1.getTime() << "\n";

	Timer t2;

	for(int i = 0; i < size; i++)
		std_queue.push(rand(0, 100));

	cout << "Время добавления элементов в std_queue: " << t2.getTime() << "\n";
	cout << "Итоговый Queue: " << my_queue << "\n";
}

void testQueuePop(Queue& my_queue) {
	cout << "Элемент my_queue до выталкивания: " << my_queue.peek() << "\n";
	my_queue.pop();
	cout << "Элемент my_queue после выталкивания: " << my_queue.peek() << "\n";
}

void testQueueComparisons(Queue& my_queue, queue<int>& std_queue) {
	Queue my_queue_2;
	queue<int> std_queue_2;

	for(int i = 0; i < my_queue.count(); i++) {
		int num = rand(0, 100);
		my_queue_2.push(num);
		std_queue_2.push(num);
	}

	cout << "Queue для сравнения: " << my_queue_2 << "\n";

	Timer t1;

	cout << "Операторы сравнения my_queue\n"
		<< "  Оператор '==': " << boolToString(my_queue == my_queue_2) << "\n"
		<< "  Оператор '!=': " << boolToString(my_queue != my_queue_2) << "\n"
		<< "  Оператор '>': " << boolToString(my_queue > my_queue_2) << "\n"
		<< "  Оператор '<': " << boolToString(my_queue < my_queue_2) << "\n"
		<< "  Оператор '<=': " << boolToString(my_queue <= my_queue_2) << "\n"
		<< "  Оператор '>=': " << boolToString(my_queue >= my_queue_2) << "\n";
	cout << "Время сравнения в my_queue: " << t1.getTime() << "\n";

	Timer t2;

	 cout << "Операторы сравнения std_queue:\n"
		<< "  Оператор '==': " << boolToString(std_queue == std_queue_2) << "\n"
		<< "  Оператор '!=': " << boolToString(std_queue != std_queue_2) << "\n"
		<< "  Оператор '>': " << boolToString(std_queue > std_queue_2) << "\n"
		<< "  Оператор '<': " << boolToString(std_queue < std_queue_2) << "\n"
		<< "  Оператор '<=': " << boolToString(std_queue <= std_queue_2) << "\n"
		<< "  Оператор '>=': " << boolToString(std_queue >= std_queue_2) << "\n";
	cout << "Время сравнения в std_queue: " << t2.getTime() << "\n";
}

void testQueueJobFunctions(Queue& my_queue) {
	Timer t1;

	cout << "Среднее арифметическое: " << my_queue.get_arithmetic_mean() << "\n";
	cout << "Время выполнения: " << t1.getTime() << "\n";

	Timer t2;

	cout << "Конкатинация: " << my_queue.concat_sort(my_queue) << "\n";
	cout << "Время выполнения: " << t2.getTime() << "\n";
}

// TEST STACK
void testStackPush(int, Stack<int>&, stack<int>&);
void testStackPop(Stack<int>&);
void testStackComparisons(Stack<int>&, stack<int>&);
void testStackJobFunctions(Stack<int>&);

void testStack(int size) {
	Stack<int> my_stack;
	stack<int> std_stack;
	cout << "Добавление " << size << " элементов\n";
	testStackPush(size, my_stack, std_stack);

	cout << "\nВыталкивание элемента\n";
	testStackPop(my_stack);

	cout << "\nОператоры сравнения\n";
	testStackComparisons(my_stack, std_stack);

	cout << "\nФункции из задания\n";
	testStackJobFunctions(my_stack);
}

void testStackPush(int size, Stack<int>& my_stack, stack<int>& std_stack) {
	Timer t1;

	for(int i = 0; i < size; i++)
		my_stack.push(rand(0, 100));

	cout << "Время добавления элементов в my_stack: " << t1.getTime() << "\n";

	Timer t2;

	for(int i = 0; i < size; i++)
		std_stack.push(rand(0, 100));

	cout << "Время добавления элементов в std_stack: " << t2.getTime() << "\n";
	cout << "Итоговый Stack: " << my_stack << "\n";
}

void testStackPop(Stack<int>& my_stack) {
	cout << "Элемент my_stack до выталкивания: " << my_stack.pop() << "\n";
	cout << "Элемент my_stack после выталкивания: " << my_stack.peek() << "\n";
}

void testStackComparisons(Stack<int>& my_stack, stack<int>& std_stack) {
	Stack<int> my_stack_2;
	stack<int> std_stack_2;

	for(int i = 0; i < my_stack.count(); i++) {
		int num = rand(0, 100);
		my_stack_2.push(num);
		std_stack_2.push(num);
	}

	cout << "Stack для сравнения: " << my_stack_2 << "\n";
	Timer t1;

	cout << "Операторы сравнения my_stack:"
		<< "  Оператор '==': " << boolToString(my_stack == my_stack_2) << "\n"
		<< "  Оператор '!=': " << boolToString(my_stack != my_stack_2) << "\n"
		<< "  Оператор '>': " << boolToString(my_stack > my_stack_2) << "\n"
		<< "  Оператор '<': " << boolToString(my_stack < my_stack_2) << "\n"
		<< "  Оператор '<=': " << boolToString(my_stack <= my_stack_2) << "\n"
		<< "  Оператор '>=': " << boolToString(my_stack >= my_stack_2) << "\n";
	cout << "Время сравнения в my_stack: " << t1.getTime() << "\n";

	Timer t2;

	 cout << "Операторы сравнения std_stack:"
		<< "  Оператор '==': " << boolToString(std_stack == std_stack_2) << "\n"
		<< "  Оператор '!=': " << boolToString(std_stack != std_stack_2) << "\n"
		<< "  Оператор '>': " << boolToString(std_stack > std_stack_2) << "\n"
		<< "  Оператор '<': " << boolToString(std_stack < std_stack_2) << "\n"
		<< "  Оператор '<=': " << boolToString(std_stack <= std_stack_2) << "\n"
		<< "  Оператор '>=': " << boolToString(std_stack >= std_stack_2) << "\n";
	cout << "Время сравнения в std_stack: " << t2.getTime() << "\n";

}

void testStackJobFunctions(Stack<int>& my_stack) {
	Timer t1;

	cout << "Среднее арифметическое: " << my_stack.getAverage() << "\n";
	cout << "Время выполнения: " << t1.getTime() << "\n";

	Timer t2;

	cout << "Конкатинация: " << my_stack.concat(my_stack) << "\n";
	cout << "Время выполнения: " << t2.getTime() << "\n";
}

// TEST VECTOR
void testVectorPush(int, Vector&, vector<int>&);
void testVectorAt(int, Vector& my_vector);
void testVectorPop(Vector& my_vector);
void testVectorComparisons(Vector& my_vector, vector<int>& std_vector);
void testVectorAllPop(Vector& my_vector, vector<int>& std_vector);
void testVectorJobFunctions(Vector& my_vector);

void testVector(int size) {
	Vector my_vector;
	vector<int> std_vector;
	cout << "Добавление " << size << " элементов\n";
	testVectorPush(size, my_vector, std_vector);

	cout << "\nДоступ к " << size / 2 << " элементу\n";
	testVectorAt(size / 2, my_vector);

	cout << "\nВыталкивание элемента\n";
	testVectorPop(my_vector);

	cout << "\nОператоры сравнения\n";
	testVectorComparisons(my_vector, std_vector);

	cout << "\nФункции из задания\n";
	testVectorJobFunctions(my_vector);

	cout << "\nВыталкивание всех элементов\n";
	testVectorAllPop(my_vector, std_vector);
}

void testVectorPush(int size, Vector& my_vector, vector<int>& std_vector) {
	Timer t1;

	for(int i = 0; i < size; i++)
		my_vector.push_back(rand(0, 100));

	cout << "Время добавления элементов в my_vector: " << t1.getTime() << "\n";

	Timer t2;

	for(int i = 0; i < size; i++)
		std_vector.push_back(my_vector.at(i));

	cout << "Время добавления элементов в std_vector: " << t2.getTime() << "\n";
	cout << "Итоговый вектор: " << my_vector << "\n";
}

void testVectorAt(int index, Vector& my_vector) {
	cout << "Элемент my_vector: " << my_vector.at(index) << "\n";
}

void testVectorPop(Vector& my_vector) {
	cout << "Элемент my_vector до выталкивания: " << my_vector.at(my_vector.count() - 1) << "\n";
	my_vector.pop_back();
	cout << "Элемент my_vector после выталкивания: " << my_vector.at(my_vector.count() - 1) << "\n";
}

void testVectorComparisons(Vector& my_vector, vector<int>& std_vector) {
	Vector my_vector_2;
	vector<int> std_vector_2;

	for(int i = 0; i < my_vector.count(); i++) {
		int num = rand(0, 100);
		my_vector_2.push_back(num);
		std_vector_2.push_back(num);
	}

	cout << "Вектор для сравнения: " << my_vector_2 << "\n";

	Timer t1;

	cout << "Операторы сравнения my_vector:"
		<< "  Оператор '==': " << boolToString(my_vector == my_vector_2) << "\n"
		<< "  Оператор '!=': " << boolToString(my_vector != my_vector_2) << "\n"
		<< "  Оператор '>': " << boolToString(my_vector > my_vector_2) << "\n"
		<< "  Оператор '<': " << boolToString(my_vector < my_vector_2) << "\n"
		<< "  Оператор '<=': " << boolToString(my_vector <= my_vector_2) << "\n"
		<< "  Оператор '>=': " << boolToString(my_vector >= my_vector_2) << "\n";
	cout << "Время сравнения в my_vector: " << t1.getTime() << "\n";

	Timer t2;

	 cout << "Операторы сравнения std_vector:"
		<< "  Оператор '==': " << boolToString(std_vector == std_vector_2) << "\n"
		<< "  Оператор '!=': " << boolToString(std_vector != std_vector_2) << "\n"
		<< "  Оператор '>': " << boolToString(std_vector > std_vector_2) << "\n"
		<< "  Оператор '<': " << boolToString(std_vector < std_vector_2) << "\n"
		<< "  Оператор '<=': " << boolToString(std_vector <= std_vector_2) << "\n"
		<< "  Оператор '>=': " << boolToString(std_vector >= std_vector_2) << "\n";
	cout << "Время сравнения в std_vector: " << t2.getTime() << "\n";

}

void testVectorAllPop(Vector& my_vector, vector<int>& std_vector) {
	Timer t1;

	int size = my_vector.count();
	for(int i = 0; i < size; i++)
		my_vector.pop_back();

	cout << "Время выталкивания всех элементов в my_vector: " << t1.getTime() << "\n";

	Timer t2;

	for(int i = 0; i < size; i++)
		std_vector.pop_back();

	cout << "Время выталкивания всех элементов в std_vector: " << t2.getTime() << "\n";
}

void testVectorJobFunctions(Vector& my_vector) {
	Timer t1;

	cout << "Среднее арифметическое: " << my_vector.get_arithmetic_mean() << "\n";
	cout << "Время выполнения: " << t1.getTime() << "\n";

	Timer t2;

	cout << "Конкатинация: " << my_vector.concat_sort(my_vector) << "\n";
	cout << "Время выполнения: " << t2.getTime() << "\n";
}
