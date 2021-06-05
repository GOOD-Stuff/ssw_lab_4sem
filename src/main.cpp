#include <iostream>
#include "Stack.cpp"
#include "DLS.cpp"
# include "RingBuffer.cpp"
# include "common.cpp"
#pragma once;
int main() {

    Stack<int> *StackFirst = NULL;
    Stack<int> *StackSecond = NULL;
    Stack<int> *StackThird = NULL;

    int a;
    int random;
    for(int i=0;i<10;i++){
        random=rand();
        StackFirst->push(&StackFirst,random);
    }
    printf("First stack:  ");
    StackFirst->print(StackFirst);
    common *use = new common;
    use->Sort(&StackFirst);
    printf("Sorted First stack: ");
    StackFirst->print(StackFirst);
    use->Segregation(&StackFirst,&StackSecond,&StackThird,100);
    printf("Second stack:  ");
    StackSecond->print(StackSecond);
    printf("Third stack:  ");
    StackSecond->print(StackThird);

    DLS<int> *DLSFirst = NULL;
    DLS<int> *DLSSecond = NULL;
    DLS<int> *DLSThird = NULL;

    for(int i=0;i<10;i++){
        random=rand();
        DLSFirst->push(&DLSFirst,random);
    }
    printf("First DLS:  ");
    DLSFirst->print(DLSFirst);
    use->Sort(&DLSFirst);
    printf("Sorted First DLS: ");
    DLSFirst->print(DLSFirst);
    use->Segregation(&DLSFirst,&DLSSecond,&DLSThird,100);
    printf("Second DLS:  ");
    DLSSecond->print(DLSSecond);
    printf("Third DLS:  ");
    DLSSecond->print(DLSThird);


   RingBuffer<int> *RingFirst = new RingBuffer<int>;

   RingFirst->Clear();
    for(int i=0;i<16;i++){
        random=rand();
        RingFirst->Push(random);
    }
    printf("First Ring buffer:  ");
    RingFirst->Print();
    *RingFirst=use->Sort(*RingFirst);
    printf("Sorted First Ring buffer: ");
    RingFirst->Print();
    use->Segregation(*RingFirst,10000);
    return 0;
}
