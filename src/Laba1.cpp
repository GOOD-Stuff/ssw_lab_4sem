#include "Stack.h"
#include "Queue.h"
#include "Vector.h"
#include <stack> 
#include <queue>
#include <vector>
#include <chrono> 
#include "iostream"
using namespace std;

void test_s() {
    cout << "\n---------------------------------------------\n\nTEST STACK\n";
    // TEST PUSH AND POP

    cout << "\n------------------------\nTEST PUSH AND POP\n\n";
    Stack<int> q_pp;
    for (int i = 0; i < 23; i++) {
        q_pp.push(i);
    }
    cout << "PUSH : " << q_pp;
    for (int i = 0; i < 10; i++) {
        q_pp.pop();
    }
    cout << "POP 10 elem of stack: " << q_pp;
    // TEST SWAP
    cout << "\n------------------------\nTEST SWAP STACK\n\n";
    Stack<int> q_swap;
    for (int i = 0; i < 10; i++) {
        q_swap.push(i);
    }
    Stack<int> q1_swap;
    for (int i = 0; i < 5; i++) {
        q1_swap.push(i);
    }
    cout << "BEFORE SWAP \n";
    cout << "s: " << q_swap << "s1: " << q1_swap;
    q1_swap.swap(q_swap);
    cout << "AFTER SWAP \n";
    cout << "s: " << q_swap << "s1: " << q1_swap;

    // TEST ISMOUNT
    cout << "\n------------------------\nTEST ISMOUNT\n\n";
    Stack<int> q_mount;
    Stack<int> q1_mount;
    q_mount.push(1);
    q_mount.push(2);
    q_mount.push(3);
    q_mount.push(4);
    q_mount.push(3);
    q_mount.push(2);
    for (int i = 0; i < 5; i++) {
        q1_mount.push(i);
    }
    q1_mount.push(1);
    q1_mount.push(3);
    std::cout << std::boolalpha;
    cout << "s: " << q_mount << "s1: " << q1_mount;
    cout << "s: " << q_mount.isMount() << "\ns1: " << q1_mount.isMount();

    // TEST COMPARE

    cout << "\n------------------------\nTEST COMPARE\n\n";
    Stack<int> q_cmp;
    Stack<int> q1_cmp;

    stack<int> Q_cmp;
    stack<int> Q1_cmp;
    q_cmp.push(1);
    q_cmp.push(20);
    q_cmp.push(3);

    Q_cmp.push(1);
    Q_cmp.push(20);
    Q_cmp.push(3);

    q1_cmp.push(1);
    q1_cmp.push(20);
    q1_cmp.push(3);
    q1_cmp.push(4);
    q1_cmp.push(5);

    Q1_cmp.push(1);
    Q1_cmp.push(20);
    Q1_cmp.push(3);
    Q1_cmp.push(4);
    Q1_cmp.push(5);

    cout << "s: " << q_cmp << "s1: " << q1_cmp;
    cout << "\ns < s1 | " << "my stack: " << (q_cmp < q1_cmp) << " | STL stack: " << (Q_cmp < Q1_cmp);
    cout << "\ns > s1 | " << "my stack: " << (q_cmp > q1_cmp) << " | STL stack: " << (Q_cmp > Q1_cmp);
    cout << "\ns == s1 | " << "my stack: " << (q_cmp == q1_cmp) << " | STL stack: " << (Q_cmp == Q1_cmp);
    cout << "\ns != s1 | " << "my stack: " << (q_cmp != q1_cmp) << " | STL stack: " << (Q_cmp != Q1_cmp);
    cout << "\ns >= s1 | " << "my stack: " << (q_cmp >= q1_cmp) << " | STL stack: " << (Q_cmp >= Q1_cmp);
    cout << "\ns <= s1 | " << "my stack: " << (q_cmp <= q1_cmp) << " | STL stack: " << (Q_cmp <= Q1_cmp);

    // TEST SPEED;

    cout << "\n------------------------\nTEST SPEED\n\n";
    Stack<int> st;
    auto begin = std::chrono::steady_clock::now();

    for (int i = 0; i < 100000; i++) {
        st.push(i);
    }
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "push: time with my stack " << elapsed_ms.count() << " nanoseconds\n";
    stack <int> steck;
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 100000; i++) {
        steck.push(i);
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "push: time with STL stack " << elapsed_ms.count() << " nanoseconds\n";


    // TEST COUNT

    begin = std::chrono::steady_clock::now();

    for (int i = 0; i < 100000; i++) {
        st.count();
    }

    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "\n\ncount: time with my stack " << elapsed_ms.count() << " nanoseconds\n";
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 100000; i++) {
        steck.size();
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "size: time with STL stack " << elapsed_ms.count() << " nanoseconds\n";


    // TEST PEEK

    begin = std::chrono::steady_clock::now();

    for (int i = 0; i < 100000; i++) {
        st.peek();
    }

    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "\n\npeek: time with my stack " << elapsed_ms.count() << " nanoseconds\n";
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 100000; i++) {
        steck.top();
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "top: time with STL stack " << elapsed_ms.count() << " nanoseconds\n";

    // TEST  POP

    begin = std::chrono::steady_clock::now();

    for (int i = 0; i < 100000; i++) {
        st.pop();
    }

    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "\n\npop: time with my stack " << elapsed_ms.count() << " nanoseconds\n";
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 100000; i++) {
        steck.pop();
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "pop: time with STL stack " << elapsed_ms.count() << " nanoseconds\n";
}

void test_q() {
    cout << "\n---------------------------------------------\n\nTEST QUEUE\n";
    // TEST PUSH AND POP

    cout << "\n------------------------\nTEST PUSH AND POP\n\n";
    Queue<int> q_pp;
    for (int i = 0; i < 23; i++) {
        q_pp.push(i);
    }
    cout << "PUSH : " << q_pp;
    for (int i = 0; i < 10; i++) {
        q_pp.pop();
    }
    cout << "POP 10 elem of q: " << q_pp;
    // TEST SWAP
    cout << "\n------------------------\nTEST SWAP QUEUE\n\n";
    Queue<int> q_swap;
    for (int i = 0; i < 10; i++) {
        q_swap.push(i);
    }
    Queue<int> q1_swap;
    for (int i = 0; i < 5; i++) {
        q1_swap.push(i);
    }
    cout << "BEFORE SWAP \n";
    cout << "q: " << q_swap << "q1: " << q1_swap;
    q1_swap.swap(q_swap);
    cout << "AFTER SWAP \n";
    cout << "q: " << q_swap << "q1: " << q1_swap;

    // TEST ISMOUNT
    cout << "\n------------------------\nTEST ISMOUNT\n\n";
    Queue<int> q_mount;
    Queue<int> q1_mount;
    q_mount.push(1);
    q_mount.push(2);
    q_mount.push(3);
    q_mount.push(4);
    q_mount.push(3);
    q_mount.push(2);
    for (int i = 0; i < 5; i++) {
        q1_mount.push(i);
    }
    q1_mount.push(1);
    q1_mount.push(3);
    std::cout << std::boolalpha;
    cout << "q: " << q_mount << "q1: " << q1_mount;
    cout << "q: " << q_mount.isMount() << "\nq1: " << q1_mount.isMount();

    // TEST COMPARE

    cout << "\n------------------------\nTEST COMPARE\n\n";
    Queue<int> q_cmp;
    Queue<int> q1_cmp;

    queue<int> Q_cmp;
    queue<int> Q1_cmp;

    q_cmp.push(1);
    q_cmp.push(20);
    q_cmp.push(3);

    Q_cmp.push(1);
    Q_cmp.push(20);
    Q_cmp.push(3);

    q1_cmp.push(1);
    q1_cmp.push(20);
    q1_cmp.push(3);
    q1_cmp.push(4);
    q1_cmp.push(5);

    Q1_cmp.push(1);
    Q1_cmp.push(20);
    Q1_cmp.push(3);
    Q1_cmp.push(4);
    cout << "q: " << q_cmp << "q1: " << q1_cmp;
    cout << "\nq < q1 | " << "my queue: " << (q_cmp < q1_cmp) << " | STL queue: " << (Q_cmp < Q1_cmp);
    cout << "\nq > q1 | " << "my queue: " << (q_cmp > q1_cmp) << " | STL queue: " << (Q_cmp > Q1_cmp) ;
    cout << "\nq == q1 | " << "my queue: " << (q_cmp == q1_cmp) << " | STL queue: " << (Q_cmp == Q1_cmp);
    cout << "\nq != q1 | " << "my queue: " << (q_cmp != q1_cmp) << " | STL queue: " << (Q_cmp != Q1_cmp);
    cout << "\nq >= q1 | " << "my queue: " << (q_cmp >= q1_cmp) << " | STL queue: " << (Q_cmp >= Q1_cmp);
    cout << "\nq <= q1 | " << "my queue: " << (q_cmp <= q1_cmp) << " | STL queue: " << (Q_cmp <= Q1_cmp);

    // TEST SPEED;

    cout << "\n------------------------\nTEST SPEED\n";
    Queue<int> q;
    auto begin = std::chrono::steady_clock::now();

    for (int i = 0; i < 100000; i++) {
        q.push(i);
    }
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "push: time with my queue " << elapsed_ms.count() << " nanoseconds\n";
    queue<int> Q;
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 100000; i++) {
        Q.push(i);
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "push: time with STL queue " << elapsed_ms.count() << " nanoseconds\n";


    // TEST COUNT

    begin = std::chrono::steady_clock::now();

    for (int i = 0; i < 100000; i++) {
        q.count();
    }

    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "\n\ncount: time with my queue " << elapsed_ms.count() << " nanoseconds\n";
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 100000; i++) {
        Q.size();
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "size: time with STL queue " << elapsed_ms.count() << " nanoseconds\n";


    // TEST PEEK

    begin = std::chrono::steady_clock::now();

    for (int i = 0; i < 100000; i++) {
        q.peek();
    }

    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "\n\npeek: time with my queue " << elapsed_ms.count() << " nanoseconds\n";
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 100000; i++) {
        Q.front();
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "front: time with STL queue " << elapsed_ms.count() << " nanoseconds\n";

    // TEST POP

    begin = std::chrono::steady_clock::now();

    for (int i = 0; i < 100000; i++) {
        q.pop();
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "\n\npop: time with my queue " << elapsed_ms.count() << " nanoseconds\n";
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 100000; i++) {
        Q.pop();
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "pop: time with STL queue " << elapsed_ms.count() << " nanoseconds\n";

    // END TEST QUEUE
    cout << "\n------------------------\n";
}

void test_v() {
    cout << "\n---------------------------------------------\n\nTEST VECTOR\n\n";
    // TEST PUSH AND POP

    cout << "\n------------------------\nTEST PUSH AND POP\n\n";
    Vector<int> q_pp;
    for (int i = 0; i < 23; i++) {
        q_pp.push(i);
    }
    cout << "PUSH : " << q_pp;
    for (int i = 0; i < 10; i++) {
        q_pp.pop();
    }
    cout << "POP 10 elem of q: " << q_pp;
    // TEST SWAP
    cout << "\n------------------------\nTEST SWAP VECTOR\n\n";
    Vector<int> q_swap;
    for (int i = 0; i < 10; i++) {
        q_swap.push(i);
    }
    Vector<int> q1_swap;
    for (int i = 0; i < 5; i++) {
        q1_swap.push(i);
    }
    cout << "BEFORE SWAP \n";
    cout << "v: " << q_swap << "v1: " << q1_swap;
    q1_swap.swap(q_swap);
    cout << "AFTER SWAP \n";
    cout << "v: " << q_swap << "v1: " << q1_swap;

    // TEST ISMOUNT
    cout << "\n------------------------\nTEST ISMOUNT\n\n";
    Vector<int> q_mount;
    Vector<int> q1_mount;


    q_mount.push(1);
    q_mount.push(2);
    q_mount.push(3);
    q_mount.push(4);
    q_mount.push(3);
    q_mount.push(2);
    for (int i = 0; i < 5; i++) {
        q1_mount.push(i);
    }
    q1_mount.push(1);
    q1_mount.push(3);
    std::cout << std::boolalpha;
    cout << "v: " << q_mount << "v1: " << q1_mount;
    cout << "v: " << q_mount.isMount() << "\nv1: " << q1_mount.isMount();

    // TEST COMPARE

    cout << "\n------------------------\nTEST COMPARE\n\n";
    Vector<int> q_cmp;
    Vector<int> q1_cmp;

    vector<int> Q_cmp;
    vector<int> Q1_cmp;

    q_cmp.push(1);
    q_cmp.push(20);
    q_cmp.push(3);

    Q_cmp.push_back(1);
    Q_cmp.push_back(20);
    Q_cmp.push_back(3);

    q1_cmp.push(1);
    q1_cmp.push(20);
    q1_cmp.push(3);
    q1_cmp.push(4);
    q1_cmp.push(5);

    Q1_cmp.push_back(1);
    Q1_cmp.push_back(20);
    Q1_cmp.push_back(3);
    Q1_cmp.push_back(4);
    cout << "v: " << q_cmp << "v1: " << q1_cmp;
    cout << "\nv < v1 | " << "my vector: " << (q_cmp < q1_cmp) << " | STL vector: " << (Q_cmp < Q1_cmp);
    cout << "\nv > v1 | " << "my vector: " << (q_cmp > q1_cmp) << " | STL vector: " << (Q_cmp > Q1_cmp);
    cout << "\nv == v1 | " << "my vector: " << (q_cmp == q1_cmp) << " | STL vector: " << (Q_cmp == Q1_cmp);
    cout << "\nv != v1 | " << "my vector: " << (q_cmp != q1_cmp) << " | STL vector: " << (Q_cmp != Q1_cmp);
    cout << "\nv >= v1 | " << "my vector: " << (q_cmp >= q1_cmp) << " | STL vector: " << (Q_cmp >= Q1_cmp);
    cout << "\nv <= v1 | " << "my vector: " << (q_cmp <= q1_cmp) << " | STL vector: " << (Q_cmp <= Q1_cmp);

    // TEST SPEED

    cout << "\n------------------------\nTEST SPEED\n\n";

    cout << "\n\nTEST VECTOR\n\n" << endl;
    Vector<int> v;
    auto begin = std::chrono::steady_clock::now();

    for (int i = 0; i < 100000; i++) {
        v.push(i);
    }
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "push: time with my Vector " << elapsed_ms.count() << " nanoseconds\n";
    vector<int> V;
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 100000; i++) {
        V.push_back(i);
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "push_back: time with STL Vector " << elapsed_ms.count() << " nanoseconds\n";


    // TEST COUNT

    begin = std::chrono::steady_clock::now();

    for (int i = 0; i < 100000; i++) {
        v.count();
    }

    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "\n\ncount: time with my Vector " << elapsed_ms.count() << " nanoseconds\n";
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 100000; i++) {
        V.size();
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "size: time with STL Vector " << elapsed_ms.count() << " nanoseconds\n";


    // TEST PEEK

    begin = std::chrono::steady_clock::now();

    for (int i = 0; i < 100000; i++) {
        v.peek();
    }

    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "\n\npeek: time with my Vector " << elapsed_ms.count() << " nanoseconds\n";
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 100000; i++) {
        V.back();
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "back: time with STL Vector " << elapsed_ms.count() << " nanoseconds\n";

    // TEST AT
    begin = std::chrono::steady_clock::now();

    for (int i = 0; i < 100000; i++) {
        v.at(i);
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "\n\nat: time with my Vector " << elapsed_ms.count() << " nanoseconds\n";
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 100000; i++) {
        V.at(i);
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "at: time with STL Vector " << elapsed_ms.count() << " nanoseconds\n";

    // TEST POP

    begin = std::chrono::steady_clock::now();

    for (int i = 0; i < 100000; i++) {
        v.pop();
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "\n\npop: time with my Vector " << elapsed_ms.count() << " nanoseconds\n";
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 100000; i++) {
        V.pop_back();
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "pop_back: time with STL Vector " << elapsed_ms.count() << " nanoseconds\n";
}

int main()
{
    test_s();
    test_q();
    test_v();
  
    cin.get();
    return 0;

}

