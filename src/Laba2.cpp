// Laba2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "List.h"
#include "Buffer.h"
#include "DoubleList.h"
#include <list>
#include <forward_list>
#include <chrono> 


void test_list() {
    std::cout << "\n\n---------TEST LIST-------------\n\n: ";
    List<int> obj;
    for (int i = 20; i >= 0; i--) {
        obj.push_back(i);
    }
    std::cout << "Elements of list: " << obj;

    List<int>::iterator it = obj.begin();
    it++;

    std::cout << "\n\nInsert 55 after " << *it;
    obj.insert(55, it);
    std::cout << "\n\nList after insert:  " << obj;

    it++;
    std::cout << "\n\nErase element after " << *it;
    obj.erase(it);
    std::cout << "\n\nList after erase:  " << obj;

    std::cout << "\n\nPush back: 123";
    obj.push_back(123);
    std::cout << "\n\nList after push back:  " << obj;

    std::cout << "\n\nPush front: 123";
    obj.push_front(123);
    std::cout << "\n\nList after Push front:  " << obj;

    std::cout << "\n\nPop front";
    obj.pop_front();
    std::cout << "\n\nList after pop front:  " << obj;

    std::cout << "\n\nPop back";
    obj.pop_back();
    std::cout << "\n\nList after pop back:  " << obj;

    std::cout << "\n\nCount of elements:  " << obj.count();

    obj.quick_sort();
    std::cout << "\n\nList after sort:  " << obj;

    List<int> obj1, obj2;

    obj.divide(obj1, obj2, 10);
    std::cout << "\n\nDivide list by 10 |  Source list: " << obj << " | List1: " << obj1  << " | List2: " << obj2;

    obj1.clear();
    obj2.clear();

    std::cout << "\n\nTEST COMPARE  ";

    std::forward_list<int> std_comp1;
    std::forward_list<int> std_comp2;
    obj1.push_front(1);
    obj1.push_front(20);
    obj1.push_front(3);

    std_comp1.push_front(1);
    std_comp1.push_front(20);
    std_comp1.push_front(3);

    obj2.push_front(1);
    obj2.push_front(20);
    obj2.push_front(3);
    obj2.push_front(4);
    obj2.push_front(5);

    std_comp2.push_front(1);
    std_comp2.push_front(20);
    std_comp2.push_front(3);
    std_comp2.push_front(4);
    std_comp2.push_front(5);

    std::cout << "List1: " << obj1 << "List2: " << obj2;
    std::cout << "\nList1 < List2 | " << "my list: " << (obj1 < obj2) << " | STL list: " << (std_comp1 < std_comp2);
    std::cout << "\nList1 > List2 | " << "my list: " << (obj1 > obj2) << " | STL list: " << (std_comp1 > std_comp2);
    std::cout << "\nList1 == List2 | " << "my list: " << (obj1 == obj2) << " | STL list: " << (std_comp1 == std_comp2);
    std::cout << "\nList1 != List2 | " << "my list: " << (obj1 != obj2) << " | STL list: " << (std_comp1 != std_comp2);
    std::cout << "\nList1 >= List2 | " << "my list: " << (obj1 >= obj2) << " | STL list: " << (std_comp1 >= std_comp2);
    std::cout << "\nList1 <= List2 | " << "my list: " << (obj1 <= obj2) << " | STL list: " << (std_comp1 <= std_comp2);

    std::cout << "\n\nTEST SPEED \n\n";

    int repeat = 100000;

    List<int> obj_test;
    std::forward_list<int> std_test;

    auto begin = std::chrono::steady_clock::now();

    for (int i = 0; i < repeat; i++) {
        obj_test.push_front(i);
    }
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "push_front: time with my list " << elapsed_ms.count() << " nanoseconds\n";

    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < repeat; i++) {
        std_test.push_front(i);
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "push_front: time with STL list " << elapsed_ms.count() << " nanoseconds\n";

    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < repeat; i++) {
        obj_test.pop_front();
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "pop_front: time with my list " << elapsed_ms.count() << " nanoseconds\n";

    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < repeat; i++) {
        std_test.pop_front();
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "pop_front: time with STL list " << elapsed_ms.count() << " nanoseconds\n";

    std::cout << "\n\n---------TEST LIST-------------\n\n ";

}

void test_buffer() {
    std::cout << "\n\n---------TEST BUFFER-------------\n\n ";
    Buffer<int> obj(21);
    for (int i = 20; i >= 0; i--) {
        obj.push(i);
    }
    std::cout << "Elements of buffer: " << obj;
    std::cout << "\n\n Push 10 elements";

    for (int i = 10; i >= 0; i--) {
        obj.push(i);
    }
    std::cout << "\n\nElements of buffer: " << obj;

    Buffer<int>::iterator it = obj.begin();
    it++;
    it++;

    std::cout << "\n\nInsert 55  ";
    obj.insert(55, it);
    std::cout << "\n\nbuffer after insert:  " << obj;

    it++;
    it++;
    std::cout << "\n\nErase element  " << *it;
    obj.erase(it);
    std::cout << "\n\nLbuffer after erase:  " << obj;

    std::cout << "\n\nCount of elements:  " << obj.count();

    obj.quick_sort();
    std::cout << "\n\nbuffer after sort:  " << obj;

    Buffer<int> obj1(20), obj2(20);

    obj.divide(obj1, obj2, 10);
    std::cout << "\n\nDivide buffer by 10 |  Source buffer: " << obj << " | buffer1: " << obj1 << " | buffer2: " << obj2;

    obj1.clear();
    obj2.clear();

    std::cout << "\n\nTEST COMPARE  ";


    obj1.push(1);
    obj1.push(20);
    obj1.push(3);


    obj2.push(1);
    obj2.push(20);
    obj2.push(3);
    obj2.push(4);
    obj2.push(5);


    std::cout << "buffer1: " << obj1 << "buffer2: " << obj2;
    std::cout << "\nbuffer1 < buffer2 | " << "my buffer: " << (obj1 < obj2);
    std::cout << "\nbuffer1 > buffer2 | " << "my buffer: " << (obj1 > obj2);
    std::cout << "\nbuffer1 == buffer2 | " << "my buffer: " << (obj1 == obj2);
    std::cout << "\nbuffer1 != buffer2 | " << "my buffer: " << (obj1 != obj2);
    std::cout << "\nbuffer1 >= buffer2 | " << "my buffer: " << (obj1 >= obj2);
    std::cout << "\nbuffer1 <= buffer2 | " << "my buffer: " << (obj1 <= obj2);

    std::cout << "\n\nTEST SPEED \n\n";

    int repeat = 100000;

    Buffer<int> obj_test(repeat);
    auto begin = std::chrono::steady_clock::now();

    for (int i = 0; i < repeat; i++) {
        obj_test.push(i);
    }
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "push: time with my buffer " << elapsed_ms.count() << " nanoseconds\n";

    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < repeat; i++) {
        obj_test.pop();
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "pop: time with my buffer " << elapsed_ms.count() << " nanoseconds\n";

    std::cout << "\n\n---------TEST BUFFER-------------\n\n ";

}

void test_double_list() {
    std::cout << "\n\n---------TEST DOUBLE LIST-------------\n\n: ";
    DoubleList<int> obj;
    for (int i = 20; i >= 0; i--) {
        obj.push_back(i);
    }
    std::cout << "Elements of list: " << obj;

    DoubleList<int>::iterator it = obj.begin();
    it++;

    std::cout << "\n\nInsert 55  " << *it;
    obj.insert(it, 55);
    std::cout << "\n\nList after insert:  " << obj;

    it++;
    std::cout << "\n\nErase element " << *it;
    obj.erase(it);
    std::cout << "\n\nList after erase:  " << obj;

    std::cout << "\n\nPush back: 123";
    obj.push_back(123);
    std::cout << "\n\nList after push back:  " << obj;

    std::cout << "\n\nPush front: 123";
    obj.push_front(123);
    std::cout << "\n\nList after Push front:  " << obj;

    std::cout << "\n\nPop front";
    obj.pop_front();
    std::cout << "\n\nList after pop front:  " << obj;

    std::cout << "\n\nPop back";
    obj.pop_back();
    std::cout << "\n\nList after pop back:  " << obj;

    std::cout << "\n\nCount of elements:  " << obj.count();

    obj.quick_sort();
    std::cout << "\n\nList after sort:  " << obj;

    DoubleList<int> obj1, obj2;

    obj.divide(obj1, obj2, 10);
    std::cout << "\n\nDivide list by 10 |  Source list: " << obj << " | List1: " << obj1 << " | List2: " << obj2;

    obj1.clear();
    obj2.clear();

    std::cout << "\n\nTEST COMPARE  ";

    std::list<int> std_comp1;
    std::list<int> std_comp2;
    obj1.push_back(1);
    obj1.push_back(20);
    obj1.push_back(3);

    std_comp1.push_back(1);
    std_comp1.push_back(20);
    std_comp1.push_back(3);

    obj2.push_back(1);
    obj2.push_back(20);
    obj2.push_back(3);
    obj2.push_back(4);
    obj2.push_back(5);

    std_comp2.push_back(1);
    std_comp2.push_back(20);
    std_comp2.push_back(3);
    std_comp2.push_back(4);
    std_comp2.push_back(5);

    std::cout << "List1: " << obj1 << "List2: " << obj2;
    std::cout << "\nList1 < List2 | " << "my list: " << (obj1 < obj2) << " | STL list: " << (std_comp1 < std_comp2);
    std::cout << "\nList1 > List2 | " << "my list: " << (obj1 > obj2) << " | STL list: " << (std_comp1 > std_comp2);
    std::cout << "\nList1 == List2 | " << "my list: " << (obj1 == obj2) << " | STL list: " << (std_comp1 == std_comp2);
    std::cout << "\nList1 != List2 | " << "my list: " << (obj1 != obj2) << " | STL list: " << (std_comp1 != std_comp2);
    std::cout << "\nList1 >= List2 | " << "my list: " << (obj1 >= obj2) << " | STL list: " << (std_comp1 >= std_comp2);
    std::cout << "\nList1 <= List2 | " << "my list: " << (obj1 <= obj2) << " | STL list: " << (std_comp1 <= std_comp2);

    std::cout << "\n\nTEST SPEED \n\n";

    int repeat = 100000;

    DoubleList<int> obj_test;
    std::list<int> std_test;

    auto begin = std::chrono::steady_clock::now();

    for (int i = 0; i < repeat; i++) {
        obj_test.push_front(i);
    }
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "push_front: time with my list " << elapsed_ms.count() << " nanoseconds\n";

    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < repeat; i++) {
        std_test.push_front(i);
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "push_front: time with STL list " << elapsed_ms.count() << " nanoseconds\n";

    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < repeat; i++) {
        obj_test.pop_front();
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "pop_front: time with my list " << elapsed_ms.count() << " nanoseconds\n";

    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < repeat; i++) {
        std_test.pop_front();
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "pop_front: time with STL list " << elapsed_ms.count() << " nanoseconds\n";

    std::cout << "\n\n---------TEST LIST-------------\n\n ";

}

int main()
{
    
    test_list();
    test_buffer();
    test_double_list();

    std::cin.get();

    return 0;
}


