#include <iostream>
#include "doubleList/doubleList.h"
#include "doubleList/boubleListFunctions.h"
#include "list/SLinkedListFunctions.h"
#include "list/SLinkedList.h"
#include "timer.h"

using namespace std;

void testDoubleList(int);
void testList(int);

int rand(int min, int max) {
	return min + rand() % (max - min);
}

string boolToString(bool val) {
	return val ? "true" : "false";
}

int main(int argc, char** argv)
{
    // cout << "\n*******************************************\n";
	// cout << "Тест double_list\n\n";
    // testDoubleList(20);

    cout << "\n*******************************************\n";
	cout << "Тест list\n\n";
    testList(20);
}

// TEST List
void testListPush(int, SLinkedList<int>&);
void testListPop(SLinkedList<int>&);
void testListComparisons(SLinkedList<int>&);
void testListJobFunctions(SLinkedList<int>&);

void testList(int size) {
    SLinkedList<int> list;

    cout << "Добавление " << size << " элементов" << "\n";
    testListPush(size, list);

    cout << "\nВыталкивание элемента\n";
    testListPop(list);

    cout << "\nОператоры сравнения\n";
	testListComparisons(list);

    cout << "\nФункции из задания\n";
	testListJobFunctions(list);
}

void testListPush(int count, SLinkedList<int>& list) {
    int delimiter = count / 2;
    Timer t;

    for(int i = 0; i < delimiter; i++)
        list.push_front(rand(0, 100));

    for(int i = 0; i < count - delimiter; i++)
        list.push_back(rand(0, 100));

    cout << "Время добавления элементов в list: " << t.getTime() << "\n";
    cout << "Итоговый list: " << list << "\n";

    SLinkedList<int>::iterator it = list.begin();
    it++;
    it++;
    it++;
    cout << "Добавление элемента после: " << *it << "\n";
    list.insert(it, rand(0, 100));
    cout << "Итоговый list: " << list << "\n";
}

void testListPop(SLinkedList<int>& list) {
    list.pop_back();
    list.pop_front();
    cout << "Выталкиваем элемент из начала и конца. Итоговый list: " << list << "\n";

    SLinkedList<int>::iterator it = list.begin();
    it++;
    it++;
    it++;

    cout << "Удаляем элемент после: " << *it << "\n";
    list.erase(it);
    cout << "list после удаления элемента: " << list << "\n";
}

void testListComparisons(SLinkedList<int>& list) {
    SLinkedList<int> list_2;

	for(int i = 0; i < list.count(); i++)
		list_2.push_back(rand(0, 100));

	cout << "double_list_2 для сравнения: " << list_2 << "\n";

	Timer t1;

	cout << "Операторы сравнения double_list\n"
		<< "  list == list_2: " << boolToString(list == list_2) << "\n"
		<< "  list != list_2: " << boolToString(list != list_2) << "\n"
		<< "  list <  list_2: " << boolToString(list < list_2) << "\n"
		<< "  list >  list_2: " << boolToString(list > list_2) << "\n"
		<< "  list <= list_2: " << boolToString(list <= list_2) << "\n"
		<< "  list >= list_2: " << boolToString(list >= list_2) << "\n";
	cout << "Время сравнения: " << t1.getTime() << "\n";
}

void testListJobFunctions(SLinkedList<int>& list) {
    cout << "Результат выполнения метода isLoop: " << isLoop(list) << "\n";
    cout << "Создаём зацикленность" << "\n";
    list.tie();
    cout << "Результат выполнения метода isLoop: " << isLoop(list) << "\n";
    list.untie();

    SLinkedList<int>::iterator it = nullptr;
    int num = 0;
    while(it == nullptr) {
        cout << "Ищем число " << num << "\n";
        it = search(list, num++);
    }

    cout << "Число " << num - 1 << " найдено" << "\n";
    cout << "Слелующее за ним число: " << *(++it) << "\n";
}

// TEST Double List
void testDoubleListPush(int, DoubleList<int>&);
void testDoubleListPop(DoubleList<int>&);
void testDoubleListComparisons(DoubleList<int>&);
void testDoubleListJobFunctions(DoubleList<int>&);

void testDoubleList(int size) {
    DoubleList<int> list;
    cout << "Добавление " << size << " элементов" << "\n";
    testDoubleListPush(size, list);

    cout << "\nВыталкивание элемента\n";
    testDoubleListPop(list);

    cout << "\nОператоры сравнения\n";
	testDoubleListComparisons(list);

    cout << "\nФункции из задания\n";
	testDoubleListJobFunctions(list);
}

void testDoubleListPush(int count, DoubleList<int>& list) {
    int delimiter = count / 2;
    Timer t;

    for(int i = 0; i < delimiter; i++)
        list.pushFront(rand(0, 100));

    for(int i = 0; i < count - delimiter; i++)
        list.pushBack(rand(0, 100));

    cout << "Время добавления элементов в double_list: " << t.getTime() << "\n";
    cout << "Итоговый double_list: " << list << "\n";

    int index = count / 2;
    cout << "Добавление элемента по индексу: " << index << "\n";
    list.insert(index, rand(0, 100));
    cout << "Итоговый double_list: " << list << "\n";
}

void testDoubleListPop(DoubleList<int>& list) {
    cout << "Элемент double_list до выталкивания из начала: " << list.popFront() << "\n";
	cout << "Элемент double_list после выталкивания из начала: " << list.popFront() << "\n";
    cout << "Элемент double_list до выталкивания из конца: " << list.popBack() << "\n";
	cout << "Элемент double_list после выталкивания из конца: " << list.popBack() << "\n";

    int index = list.count() / 2;
    cout << "double_list после выталкиваний: " << list << "\n";

    list.erase(index);
    cout << "double_list после удаления элемента с индексом " << index << ": " << list << "\n";
}

void testDoubleListComparisons(DoubleList<int>& list) {
    DoubleList<int> list_2;

	for(int i = 0; i < list.count(); i++)
		list_2.pushBack(rand(0, 100));

	cout << "double_list_2 для сравнения: " << list_2 << "\n";

	Timer t1;

	cout << "Операторы сравнения double_list\n"
		<< "  double_list == double_list_2: " << boolToString(list == list_2) << "\n"
		<< "  double_list != double_list_2: " << boolToString(list != list_2) << "\n"
		<< "  double_list <  double_list_2: " << boolToString(list < list_2) << "\n"
		<< "  double_list >  double_list_2: " << boolToString(list > list_2) << "\n"
		<< "  double_list <= double_list_2: " << boolToString(list <= list_2) << "\n"
		<< "  double_list >= double_list_2: " << boolToString(list >= list_2) << "\n";
	cout << "Время сравнения: " << t1.getTime() << "\n";
}

void testDoubleListJobFunctions(DoubleList<int>& list) {
    cout << "Результат выполнения метода isLoop: " << isLoop(list) << "\n";
    cout << "Создаём зацикленность" << "\n";
    list.tie();
    cout << "Результат выполнения метода isLoop: " << isLoop(list) << "\n";
    list.untie();

    Iterator<int> it = nullptr;
    int num = 0;
    while(it == nullptr) {
        cout << "Ищем число " << num << "\n";
        it = search(list, num++);
    }

    cout << "Число " << num - 1 << " найдено" << "\n";
    cout << "Слелующее за ним число: " << *(++it) << "\n";
}
