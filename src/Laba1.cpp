#include "Stack.cpp"
#include "Queue.cpp"
#include "Vector.cpp"
#include <stack> 
#include <queue>
#include <vector>
#include <chrono> 
#include <stdlib.h>

#ifdef _DEBUG
#define new new( _NORMAL_BLOCK, __FILE__, __LINE__)
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#endif
using namespace std;


int main()
{
    // TEST STACK
    cout << "TEST STACK\n\n";
    Stack<int> st;
    auto begin = std::chrono::steady_clock::now();

    for (int i = 0; i < 2222222; i++) {
        st.push(i);
    }
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "push: time with my stack " << elapsed_ms.count() <<  " microseconds\n";
    stack <int> steck;
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 2222222; i++) {
        steck.push(i);
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "push: time with STL stack " << elapsed_ms.count() << " microseconds\n";


    // TEST COUNT

    begin = std::chrono::steady_clock::now();

    for (int i = 0; i < 2222222; i++) {
        st.count();
    }

    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "\n\ncount: time with my stack " << elapsed_ms.count() << " microseconds\n";
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 2222222; i++) {
        steck.size();
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "size: time with STL stack " << elapsed_ms.count() << " microseconds\n";


    // TEST PEEK

    begin = std::chrono::steady_clock::now();

    for (int i = 0; i < 2222222; i++) {
        st.peek();
    }

    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "\n\npeek: time with my stack " << elapsed_ms.count() << " microseconds\n";
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 2222222; i++) {
        steck.top();
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "top: time with STL stack " << elapsed_ms.count() << " microseconds\n";

    // TEST  POP

    begin = std::chrono::steady_clock::now();

    for (int i = 0; i < 2222222; i++) {
        st.pop();
    }

    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "\n\npop: time with my stack " << elapsed_ms.count() << " microseconds\n";
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 2222222; i++) {
        steck.pop();
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "pop: time with STL stack " << elapsed_ms.count() << " microseconds\n";
    // TEST STACK END

    // TEST QUEUE 
    cout << "\n\nTEST QUEUE\n\n" << endl;
    Queue<int> q;
    begin = std::chrono::steady_clock::now();

    for (int i = 0; i < 2222222; i++) {
        q.push(i);
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "push: time with my stack " << elapsed_ms.count() << " microseconds\n";
    queue<int> Q;
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 2222222; i++) {
        Q.push(i);
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "push: time with STL stack " << elapsed_ms.count() << " microseconds\n";


    // TEST COUNT

    begin = std::chrono::steady_clock::now();

    for (int i = 0; i < 2222222; i++) {
        q.count();
    }

    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "\n\ncount: time with my stack " << elapsed_ms.count() << " microseconds\n";
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 2222222; i++) {
        Q.size();
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "size: time with STL stack " << elapsed_ms.count() << " microseconds\n";


    // TEST PEEK

    begin = std::chrono::steady_clock::now();

    for (int i = 0; i < 2222222; i++) {
        q.peek();
    }

    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "\n\npeek: time with my stack " << elapsed_ms.count() << " microseconds\n";
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 2222222; i++) {
        Q.front();
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "front: time with STL stack " << elapsed_ms.count() << " microseconds\n";

    // TEST STACK POP

    begin = std::chrono::steady_clock::now();

    for (int i = 0; i < 2222222; i++) {
        q.pop();
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "\n\npop: time with my stack " << elapsed_ms.count() << " microseconds\n";
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 2222222; i++) {
        Q.pop();
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "pop: time with STL stack " << elapsed_ms.count() << " microseconds\n";

    // END TEST QUEUE


    // TEST VECTOR 
    cout << "\n\nTEST VECTOR\n\n" << endl;
   Vector<int> v;
    begin = std::chrono::steady_clock::now();

    for (int i = 0; i < 2222222; i++) {
        v.push(i);
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "push: time with my Vector " << elapsed_ms.count() << " microseconds\n";
    vector<int> V;
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 2222222; i++) {
        V.push_back(i);
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "push_back: time with STL Vector " << elapsed_ms.count() << " microseconds\n";


    // TEST COUNT

    begin = std::chrono::steady_clock::now();

    for (int i = 0; i < 2222222; i++) {
        v.count();
    }

    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "\n\ncount: time with my Vector " << elapsed_ms.count() << " microseconds\n";
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 2222222; i++) {
        V.size();
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "size: time with STL Vector " << elapsed_ms.count() << " microseconds\n";


    // TEST PEEK

    begin = std::chrono::steady_clock::now();

    for (int i = 0; i < 2222222; i++) {
        v.peek();
    }

    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "\n\npeek: time with my Vector " << elapsed_ms.count() << " microseconds\n";
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 2222222; i++) {
        V.back();
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "back: time with STL Vector " << elapsed_ms.count() << " microseconds\n";

    // TEST AT
    begin = std::chrono::steady_clock::now();

    for (int i = 0; i < 2222222; i++) {
        v.at(i);
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "\n\nat: time with my Vector " << elapsed_ms.count() << " microseconds\n";
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 2222222; i++) {
        V.at(i);
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "at: time with STL Vector " << elapsed_ms.count() << " microseconds\n";

    // TEST POP

    begin = std::chrono::steady_clock::now();

    for (int i = 0; i < 2222222; i++) {
        v.pop();
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "\n\npop_back: time with my Vector " << elapsed_ms.count() << " microseconds\n";
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 2222222; i++) {
        V.pop_back();
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "pop: time with STL Vector " << elapsed_ms.count() << " microseconds\n";

  
    // END TEST QUEUE

    cin.get();

}

